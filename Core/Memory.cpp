#include "Memory.h"
#include "Sys.h"
#include "log.h"
#include "nsLib/Str.h"

#define	MEM_ID	0xAFAF

	struct memblock_t
	{
		uword		id;
		uint		real_size;	//real size with header
		uint		alloc_size; //user size, when call malloc/realloc
		
		nsString	file;
		int			line;

		memblock_t *next, *prev;
	};


static memblock_t*	g_memList = 0;
static uint			g_nHeapSize = 0;
static uint			g_nUserSize = 0;

//---------------------------------------------------------
// mem_free: 
//---------------------------------------------------------
void mem_free( void *data )
{
	if ( !data ) return;

	//LogPrintf( PRN_ALL, "free block: %x\n", data );
	memblock_t	*block = ((memblock_t*)data) - 1;
	if ( !g_memList || block->id != MEM_ID )
	{
		LogPrintf( PRN_DEV, "WARNING: free invalid allocated block\n" );
		return;
	}

	if ( block == g_memList )
		g_memList = block->next;
	else
	{
		memblock_t	*prev = block->prev;
		memblock_t	*next = block->next;
		//LogPrintf( PRN_ALL, "free OK\n" );
		if ( prev ) prev->next = next;
		if ( next ) next->prev = prev;
	}

	g_nHeapSize -= block->real_size;
	g_nUserSize -= block->alloc_size;
	free( block );
}

//---------------------------------------------------------
// mem_malloc: 
//---------------------------------------------------------
void* mem_malloc( uint size, char *file, int line )
{
	uint		real_size = size + sizeof(memblock_t);
	void		*data = malloc( real_size );
	memblock_t	*block = (memblock_t*)data;
	if ( !block )
	{
		Sys_FatalError( "ERROR: Allocate memory block! (file: [%s], line: [%i])", file, line );
		return 0;
	}
	memset( block, 0, real_size );
	
	//fill header
	block->id = MEM_ID;
	block->file = file;
	block->line = line;
	block->real_size = _msize( data );
	block->alloc_size = size;
	g_nHeapSize += block->real_size;
	g_nUserSize += block->alloc_size;
	
	//past to queue
	block->next = g_memList;
	if ( g_memList ) g_memList->prev = block;
	g_memList = block;

	return (block + 1);
}

//---------------------------------------------------------
// mem_realloc: 
//---------------------------------------------------------
void* mem_realloc( void *data, uint size, char *file, int line )
{
	memblock_t	*old_block = ((memblock_t*)data) - 1;
	uint		real_size = size + sizeof(memblock_t);
	memblock_t	*block = (memblock_t*)::malloc( real_size );
	if ( !block )
	{
		Sys_FatalError( "ERROR: Allocate memory block! (file: [%s], line: [%i])", file, line );
		return 0;
	}
	memset( block, 0, real_size );
	
	//fill header
	block->id = MEM_ID;
	block->file = file;
	block->line = line;
	block->real_size = _msize( block );
	block->alloc_size = size;
	g_nHeapSize += block->real_size;
	g_nUserSize += block->alloc_size;
	
	//past to queue
	block->next = g_memList;
	if ( g_memList ) g_memList->prev = block;
	g_memList = block;

	//copy data
	int	copy_size = size > old_block->alloc_size ? old_block->alloc_size : size;
	memcpy( block + 1, old_block + 1, copy_size );
	mem_free( old_block + 1 ); //free old block 

	return (block + 1);
}

//-----------------------------------------------------
// mem_report:
//-----------------------------------------------------
void mem_report( uint &userAlloc, uint &heapAlloc )
{
	userAlloc = g_nUserSize;
	heapAlloc = g_nHeapSize;
}

//---------------------------------------------------------
// my_strdup: 
//---------------------------------------------------------
char* mem_strdup( const char *str, char *file, int line )
{
	if ( !str )
	{
		assert( !"Invalid param!");
		return 0;
	}

	char *res = (char*)mem_malloc( strlen( str ) + 1, file, line );
	strcpy( res, str );
	return res;
}

//---------------------------------------------------------
// nsAutoMem: 
//---------------------------------------------------------
class nsAutoMem
{
public:
	~nsAutoMem()
	{
		if ( g_memList )
		{
			FILE	*fp = fopen( "mem_leaks.txt", "w" );
			if ( fp )
			{
				fprintf( fp, "memory allocated: %i\n", g_nHeapSize );
				memblock_t	*block = g_memList;
				bool		found = block != 0;
				while ( block )
				{
					fprintf( fp, "file: [%s], line: [%i], size: %i (%i)\n", block->file.AsChar(), block->line, block->alloc_size, block->real_size );
					block = block->next;
				}

				fclose( fp );
			}

			Sys_Message( "Memory leaks detected!" );
		}
	}
};

nsAutoMem g_autoMem;



