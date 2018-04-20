#include "StrTools.h"
#include "Utils.h"

//---------------------------------------------------------
// StrPrintf:
//---------------------------------------------------------
const char* StrPrintf( const char* fmt, ... )
{
	static char str[1024];

	va_list	list;
	va_start( list, fmt );
	vsprintf( str, fmt, list );
	va_end( list );

	return str;
}

//---------------------------------------------------------
// StrEqual:
//---------------------------------------------------------
bool StrEqual( const char* s1, const char *s2 )
{
	while ( *s1 && *s2 )
	{
		if ( *s1 != *s2 ) return false;

		s1 ++;
		s2 ++;
	}
	return *s1 == *s2;
}

//---------------------------------------------------------
// StrHash:
//---------------------------------------------------------
byte StrHash( const char* str )
{
	uint	hash = 0;
	while ( *str )
	{
		hash += *str;
		str++;
	}
	return byte(hash % 255);
}

//---------------------------------------------------------
// StrTabs:
//---------------------------------------------------------
const char* StrTabs( int tabCount )
{
	static char	res[256];
    if ( tabCount >= 256 ) tabCount = 255;
    memset( res, '\t', tabCount );
    res[tabCount] = 0;
    return res;
}

//---------------------------------------------------------
// StrReplace:
//---------------------------------------------------------
void StrReplace( char *str, char chFind, char chReplace )
{
	while ( *str )
    {
    	if ( *str == chFind )
        	*str = chReplace;
    	str++;
    }
}

//---------------------------------------------------------
// StrCopy: 
//---------------------------------------------------------
void StrCopy( char *str, const char *from, int maxSize )
{
	if ( !str || !from ) return;

	int	len = strlen( from );
	if ( maxSize > 0 )
		len = len > maxSize - 1 ? maxSize - 1 : len;

	strncpy( str, from, len );
	str[len] = 0;
}

//---------------------------------------------------------
// StrToken:
//---------------------------------------------------------
char *StrToken( const char *strToken, const char *strDelimit, int &resLength )
{
	static	const char	*end = 0;

	if ( !strToken ) strToken = end;
	if ( !strToken ) return 0;

	const char	*begin = strpbrk( strToken, strDelimit );
	while ( begin && begin == strToken )
	{
		strToken ++;
		if ( !*strToken )
		{
			end = 0;
			return 0;
		}
		begin = strpbrk( strToken, strDelimit );
	}
	
	if ( begin )
	{
		resLength = begin - strToken;
		end = begin;
		return (char*)strToken;
	}

    resLength = strlen( strToken );
	end = 0;
	return (char*)strToken;
}

//---------------------------------------------------------
// StrLineCount:
//---------------------------------------------------------
int StrLineCount( const char* str, int len )
{
	int	count = 0;
	for ( int i = 0; i < len; i++, str++)
		if ( *str == '\n' )	count ++;

	return count;
}

//---------------------------------------------------------
// StrSkipChars:
//---------------------------------------------------------
const char* StrSkipChars( const char* str, const char* charSet )
{
	while ( *str )
	{
		if ( !strchr( charSet, *str ) )
			break;
		str ++;
	}
	return str;
}

//---------------------------------------------------------
// StrCheck: 
//---------------------------------------------------------
bool StrCheck( const char* str )
{
	return str && strlen( str );
}

//---------------------------------------------------------
// StrCharReplace: 
//---------------------------------------------------------
void StrCharReplace( char *str, char oldCh, char newCh )
{
	while ( *str )
	{
		if ( *str == oldCh )
			*str = newCh;
		str ++;
	}
}

//---------------------------------------------------------
// StrNumber: 
//---------------------------------------------------------
const char*	StrNumber( int num, int digitCount )
{
	static nsString	out;
	nsString		fmt;
	fmt.Format( "%%0%ii", digitCount );
	out.Format( fmt, num );

	return out;	
}
