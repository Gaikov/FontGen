#include "Package.h"
#include "Memory.h"
#include "log.h"
#include "StructUt.h"
#include "nsLib/StrTools.h"

nsPackage::packDesc_t	*nsPackage::m_packs = 0;
int						nsPackage::m_packCount = 0;

nsPackage				g_pack;

//---------------------------------------------------------
// nsPackage::Init: 
//---------------------------------------------------------
bool nsPackage::Init()
{	
	nsString	*list = 0;
	LogPrintf( PRN_ALL, "...enum packs\n" );
	int	count = EnumDirFiles( "", "pak", &list );
	if ( !count )
		LogPrintf( PRN_ALL, "WARNING: packs not found!\n" );
	else
	{
		for ( int i = 0; i < count; i++ )
			AddPack( list[i] );
		my_free( list );
	}
	return true;
}

//---------------------------------------------------------
// nsPackage::Release: 
//---------------------------------------------------------
void nsPackage::Release()
{
	if ( m_packs )
	{
		LogPrintf( PRN_ALL, "...release packs\n" );
		for ( int i = 0; i < m_packCount; i++ )
		{
			if ( m_packs[i].files )
				my_free( m_packs[i].files );
		}
		my_free( m_packs );
	}
}

//---------------------------------------------------------
// nsPackage::AddPack: 
//---------------------------------------------------------
bool nsPackage::AddPack( const char *fileName )
{
	if ( !fileName || !strlen( fileName ) ) return true;

	packFileDesc_t	*files = 0;
	int fcount = InitPack( fileName, &files );
	if ( fcount )
	{
		packDesc_t	pd;
		pd.packName = fileName;
		pd.count = fcount;
		pd.files = files;
		AddToArray( &m_packs, m_packCount, pd );

		return true;
	}

	return false;
}

//---------------------------------------------------------
// nsPackage::LoadFile: 
//---------------------------------------------------------
nsFile*	nsPackage::LoadFile( const char *fileName )
{
	if ( !fileName || !strlen( fileName ) ) return 0;

	nsFile	*file = LoadDiskFile( fileName );
	if ( !file )
		file = LoadPackFile( fileName );

	return file;

}

//---------------------------------------------------------
// nsPackage::ReleaseFile: 
//---------------------------------------------------------
void nsPackage::ReleaseFile( nsFile *file )
{
	if ( file )
	{
		if ( file->m_data )
		{
			my_free( file->m_data );
			file->m_data = 0;
		}
		my_free( file );
		file = 0;
	}
}

//---------------------------------------------------------
// nsPackage::IsExists: 
//---------------------------------------------------------
bool nsPackage::IsExists( const char* fileName )
{
	if ( !fileName || !strlen( fileName ) ) return false;
	
	FILE	*fp = fopen( fileName, "r" );
	if ( fp )
	{
		fclose( fp );
		return true;
	}
	else
	{
		for ( int i = m_packCount - 1; i >= 0; i-- )
			if ( FindPackFile( fileName, i ) ) return true;
	}

	return false;
}

//---------------------------------------------------------
// nsPackage::FileWrite: 
//---------------------------------------------------------
/*bool nsPackage::FileWrite( const char *fileName, const void *data, int size, bool overwrite )
{
	FILE	*fp;
	char	*mode = overwrite ? "wb" : "ab";
	if ( !(fp = fopen( fileName, mode )) ) return false;

	fwrite( data, size, 1, fp );
	if ( ferror( fp ) )
	{
		fclose( fp );
		return false;
	}

	fclose( fp );
	return true;
}//*/

//---------------------------------------------------------
// nsPackage::EnumDirFiles: 
//---------------------------------------------------------
bool StrInList( nsString *list, int count, const char *str )
{
	for ( int i = 0; i < count; i++ )
		if ( list[i] == str ) return true;
	return false;
}
//---------------------------------------------------------
int FileCmp( const void *elem1, const void *elem2 )
{
	const nsString	*s1 = (const nsString*)elem1;
	const nsString	*s2 = (const nsString*)elem2;
	return strcmp( *s1, *s2 );
}
//---------------------------------------------------------
int nsPackage::EnumDirFiles( const char *dir, const char *type, nsString **list, bool withPacks )
{
	nsString	pattern = StrPrintf( "%s*.%s", dir, type );
	
	*list = 0;
	int	count = 0;

	_finddata_t	fd;
	int	handle;
	if ( (handle = _findfirst( pattern, &fd )) >= 0 )
	{
		do
		{
			if ( !(fd.attrib & _A_SUBDIR) )
				AddToArray( &*list, count, nsString(fd.name) );
		}
		while ( _findnext( handle, &fd ) >= 0 );
		_findclose( handle );
	}

	if ( withPacks )
	{
		for ( int p = m_packCount - 1; p >= 0; p-- )
		{
			char	cdir[256];
			strcpy( cdir, dir );
			_strlwr( cdir );

			for ( int i = 0; i < m_packs[p].count; i++ )
			{
				if ( strncmp( cdir, m_packs[p].files[i].filename, strlen( cdir ) ) == 0 && 
					!strchr( m_packs[p].files[i].filename + strlen( cdir ), '/' ) &&
					strstr( m_packs[p].files[i].filename, StrPrintf( ".%s", type ) ) )
				{
					nsString	name = m_packs[p].files[i].filename + strlen( cdir );
					if ( !StrInList( *list, count, name ) )
						AddToArray( &*list, count, name );
				}
			}
		}
	}

	if ( count )
		qsort( *list, count, sizeof(nsString), FileCmp );

	return count;
}

//---------------------------------------------------------
// nsPackage::InitPack: 
//---------------------------------------------------------
int nsPackage::InitPack( const char *filename, packFileDesc_t **files )
{
	LogPrintf( PRN_ALL, "checking '%s'... ", filename );
	FILE	*file;
	*files = 0;
	int count = 0;
	if ( !(file = fopen( filename, "rb" )) )
	{
		LogPrintf( PRN_ALL, "WARNING: pack not found\n" );
		return 0;
	}
	
	packHeader_t	ph;
	if ( fread( &ph, sizeof(packHeader_t), 1, file ) != 1 )
	{
		LogPrintf( PRN_ALL, "WARNING: read pack header!\n" );
		fclose( file );
		return 0;
	}

	if ( ph.id[0] != 'P' || ph.id[1] != 'A' || ph.id[2] != 'C' || ph.id[3] != 'K' )
	{
		fclose( file );
		LogPrintf( PRN_ALL, "WARNING: invalid pack file!\n" );
		return 0;
	}

	if ( ph.version != PACK_VERSION )
	{
		fclose( file );
		LogPrintf( PRN_ALL, "WARNING: wrong pack version!\n" );
		return 0;
	}

	if ( !(*files = (packFileDesc_t*)my_malloc( ph.dir_size )) )
	{
		fclose( file );
		LogPrintf( PRN_ALL, "ERROR: allocate pack dir!\n" );
		return 0;
	}

	if ( fread( *files, ph.dir_size, 1, file ) != 1 )
	{
		fclose( file );
		my_free( *files );	*files = 0;
		LogPrintf( PRN_ALL, "WARNING: read pack dir!\n" );
		return 0;
	}

	count = ph.dir_size / sizeof(packFileDesc_t);
	LogPrintf( PRN_ALL, "OK! (%i - files)\n", count );
	fclose( file );
	return count;
}

//---------------------------------------------------------
// nsPackage::FindPackFile: 
//---------------------------------------------------------
packFileDesc_t* nsPackage::FindPackFile( const char *fileName, int pack )
{
	if ( !fileName && !strlen( fileName ) ) return 0;
	LogPrintf( PRN_DEV, "searching file desc '%s'\n", fileName );

	nsString	lowerName = fileName;
	_strlwr( lowerName.AsChar() );
	for ( int i = 0; i < m_packs[pack].count; i++ )
		if ( lowerName == m_packs[pack].files[i].filename )
			return &m_packs[pack].files[i];

	return 0;

}

//---------------------------------------------------------
// nsPackage::LoadPackFile: 
//---------------------------------------------------------
nsFile* nsPackage::LoadPackFile( const char *fileName )
{
	nsFile	*file = 0;
	packFileDesc_t	*fd = 0;
	int	pack = 0;
	
	for ( int i = m_packCount - 1; i >= 0; i-- )
		if ( fd = FindPackFile( fileName, i ) )
		{
			pack = i;
			break;
		}

	if ( !fd )
	{
		LogPrintf( PRN_DEV, "WARNING: file desc not found!\n" );
		return 0;
	}


	FILE *f;
	if ( !(f = fopen( m_packs[pack].packName, "rb" )) )
	{
		LogPrintf( PRN_DEV, "WARNING: open pack file\n" );
		return 0;
	}

	if ( !(file = (nsFile*)my_malloc( sizeof(nsFile) )) )
	{
		fclose( f );
		return 0;
	}

	file->m_fileName = fileName;
	file->m_size = fd->size;
	if ( !(file->m_data = (unsigned char*)my_malloc( fd->size + 1 )) )
	{
		my_free( file );
		fclose( f );
		return 0;
	}

	fseek( f, fd->offset, SEEK_SET );
	if ( fread( file->m_data, file->m_size, 1, f ) != 1 )
	{
		LogPrintf( PRN_DEV, "WARNING: read pack data '%s'\n", fileName );
		my_free( file->m_data );
		my_free( file );
		fclose( f );
		return 0;
	}

	fclose( f );

	if ( strstr( fileName, ".txt" ) )
		DecodeFile( file );

	return file;
}

//---------------------------------------------------------
// nsPackage::LoadDiskFile: 
//---------------------------------------------------------
nsFile* nsPackage::LoadDiskFile( const char *fileName )
{
	FILE	*file = 0;
	int		nSize;
	
	LogPrintf( PRN_DEV, "reading file '%s'\n", fileName );

	if ( !(file = fopen( fileName, "rb" )) )
	{
		LogPrintf( PRN_DEV, "WARNING: open file: '%s'\n", fileName );
		return 0;
	}

	nsFile	*pFile = (nsFile*)my_malloc( sizeof(nsFile) );
	if ( !pFile )
	{
		fclose( file );
		return 0;
	}

	fseek( file, 0, SEEK_END );
	nSize = ftell( file );
	fseek( file, 0, SEEK_SET );
	if ( !nSize )
	{
		LogPrintf( PRN_DEV, "WARNING: file size if zero\n" );
		my_free( pFile );
		fclose( file );
		return 0;
	}
	
	pFile->m_fileName = fileName;
	pFile->m_size = nSize;

	if ( !(pFile->m_data = (unsigned char*)my_malloc( nSize + 1 )) )	// + 1 for file parsed as string
	{
		fclose( file );
		my_free( pFile );
		return 0;
	}
	pFile->m_data[nSize] = 0;	//for file as string

	if ( fread( pFile->m_data, nSize, 1, file ) != 1 )
	{
		LogPrintf( PRN_DEV, "WARNING: read file data: %s\n", fileName );
		fclose( file );
		my_free( pFile->m_data );
		my_free( pFile );
		return 0;
	}
	
	fclose( file );
	return pFile;
}

//---------------------------------------------------------
// nsPackage::DecodeFile: 
//---------------------------------------------------------
void nsPackage::DecodeFile( nsFile *file )
{
	if ( !file || !file->m_data )
		return;

	uchar	*data = file->m_data;
	uchar	lo, hi;
	for ( uint i = 0; i < file->m_size; i++, data++ )
	{
		lo = (*data) & 0x0F;
		hi = (*data) & 0xF0;
		*data = (lo << 4) | (hi >> 4);
	}
}
