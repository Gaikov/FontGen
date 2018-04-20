// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Str.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Str.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsString::operator += : 
//---------------------------------------------------------
void nsString::operator += ( const char* str )
{
	strcat( m_str, str );
}

//---------------------------------------------------------
// nsString::Format:
//---------------------------------------------------------
void __cdecl nsString::Format( const char *fmt, ... )
{
	va_list	list;
	va_start( list, fmt );
	vsprintf( m_str, fmt, list );
	va_end( list );
}

//---------------------------------------------------------
// nsString::CopyFrom:
//---------------------------------------------------------
void nsString::CopyFrom( const char* str, uint length )
{
	if ( !str ) return;
	if ( !length ) length = strlen( str );
	length = length > MAX_SIZE - 1 ? MAX_SIZE - 1 : length;
	strncpy( m_str, str, length );
	m_str[length] = 0;
}

//---------------------------------------------------------
// nsString::Append:
//---------------------------------------------------------
void nsString::Append( char ch )
{
	int	len = strlen( m_str );
	if ( len < MAX_SIZE - 1 )
	{
		m_str[len] = ch;
		m_str[len + 1] = 0;
	}
}

//---------------------------------------------------------
// nsString::Length: 
//---------------------------------------------------------
int	nsString::Length()
{
	return strlen( m_str );
}

//---------------------------------------------------------
// nsString::ToLower: 
//---------------------------------------------------------
void nsString::ToLower()
{
	strlwr( m_str );
}

//---------------------------------------------------------
// nsString::ConvFileName: 
//---------------------------------------------------------
void nsString::ConvFileName()
{
	int len = strlen( m_str );
	for ( int i = 0; i < len; ++i )
	{
		if ( m_str[i] == '\\' )
			m_str[i] = '/';
	}

	ToLower();
}

//---------------------------------------------------------
// nsString::ReplaceFileExt:
//---------------------------------------------------------
void nsString::ReplaceFileExt( const char *newExt )
{
	if ( !StrCheck( newExt ) ) return;

	char *dot = (char*)strchr( m_str, '.' );
	if ( dot )
		strcpy( dot, newExt );
	else
		strcat( m_str, newExt );
}

//---------------------------------------------------------
// operator +: 
//---------------------------------------------------------
nsString operator + ( const nsString &s1, const char *s2 )
{
	nsString	res = s1;
	res += s2;
	return res;
}