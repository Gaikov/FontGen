#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "nsLib/comm_types.h"
#include <assert.h>
#include <malloc.h>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
//	ѕам€ть не должна выдел€тьс€/освобождатьс€ 
//  в конструкторах/деструкторах глобальных классов
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 

/*void*	mem_malloc( uint size, char *file, int line );
void*	mem_realloc( void *data, uint size, char *file, int line );
void	mem_free( void *data );
void	mem_report( uint &userAlloc, uint &heapAlloc );
char*	mem_strdup( const char *str, char *file, int line );//*/

/*#define my_malloc( size ) mem_malloc( size, __FILE__, __LINE__ )
#define my_realloc( data, size ) mem_realloc( data, size, __FILE__, __LINE__ )
#define my_free( data ) mem_free( data )
#define my_strdup( str ) mem_strdup( str, __FILE__, __LINE__ )//*/

#define my_malloc( size ) malloc( size )
#define my_realloc( data, size ) realloc( data, size )
#define my_free( data ) free( data )
#define my_strdup( str ) strdup( str )

template <class T>
inline void MemZero( T &mem )
{
	memset( &mem, 0, sizeof(T) );
}

/*inline void* operator new ( size_t size )
{
	return mem_malloc( size, "unknown file", 0 );
}

inline void* operator new[] ( size_t size )
{
	return mem_malloc( size, "unknown file", 0 );
}

/*inline void* operator new ( size_t size, const char* file, int line )
{
	return mem_malloc( size, (char*)file, line );
}

inline void* operator new[] ( size_t size, const char* file, int line )
{
	return mem_malloc( size, (char*)file, line );
}//*/

/*inline void operator delete( void* p )
{
	mem_free( p );
}

inline void operator delete [] ( void* p )
{
	mem_free( p );
}//*/

//#define new new( __FILE__, __LINE__ )

#pragma warning( disable : 4291 )
#endif
