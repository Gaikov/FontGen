// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Package.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Package_H_
#define	_Package_H_

#include "packarch.h"
#include "nsLib/StrTools.h"

//---------------------------------------------------------
// nsFile: 
//---------------------------------------------------------
class nsFile
{
friend class nsPackage;
public:
	const char*		GetFileName() { return m_fileName; }
	uint			GetSize() { return m_size; }
	uchar*			GetData() { return m_data; }

	uint			offset;	//HACK: нужно для отслеживание позиции трека

private:
	nsString		m_fileName;
	uint			m_size;
	uchar			*m_data;
};

//---------------------------------------------------------
// CPackage: 
//---------------------------------------------------------
class nsPackage
{
public:
	//initialize
	bool			Init();
	void			Release();
	bool			AddPack( const char *fileName );

	nsFile*			LoadFile( const char *fileName );
	void			ReleaseFile( nsFile *file );
	
	//file manipulation
	bool			IsExists( const char *fileName );
	//bool			FileWrite( const char *fileName, const void *data, int size, bool overwrite = false );
	
	int				EnumDirFiles( const char *dir, const char *type, nsString **list, bool withPacks = false );

private:
	typedef struct
	{
		nsString		packName;
		packFileDesc_t	*files;
		int				count;
	}
	packDesc_t;

	static packDesc_t	*m_packs;
	static int			m_packCount;

private:
	int				InitPack( const char *filename, packFileDesc_t **files );
	packFileDesc_t*	FindPackFile( const char *fileName, int pack );
	nsFile*			LoadPackFile( const char *fileName );
	nsFile*			LoadDiskFile( const char *fileName );
	void			DecodeFile( nsFile *file );
};

extern	nsPackage	g_pack;

#endif //_Package_H_
