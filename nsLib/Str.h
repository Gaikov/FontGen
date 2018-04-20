// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Str.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Str_H_
#define	_Str_H_

#include "comm_types.h"
#include "headers.h"

//---------------------------------------------------------
// nsString:
//---------------------------------------------------------
class nsString
{
public:
	enum { MAX_SIZE = 256 };

public:
	inline nsString();
	inline nsString( const char *str );

	inline operator const char* () const;
	inline nsString& operator = ( const char* str );
	inline bool operator == ( const char* str );
	inline bool operator != ( const char* str );
	inline char& operator [] ( const int idx );

	void				operator += ( const char* str );

	void __cdecl		Format( const char *fmt, ... );
	inline char*		AsChar() { return m_str; }
	void				CopyFrom( const char* str, uint length = 0 );	//безопасное копирование
	void				Append( char ch );
	int					Length();
	void				ToLower();
	void				ConvFileName();
	void				ReplaceFileExt( const char *newExt );

	friend nsString operator + ( const nsString &s1, const char *s2 );

protected:
	char	m_str[MAX_SIZE];
};

//---------------------------------------------------------
// nsString::nsString:
//---------------------------------------------------------
nsString::nsString()
{
	m_str[0] = 0;
}

//---------------------------------------------------------
// nsString::nsString:
//---------------------------------------------------------
nsString::nsString( const char *str )
{
	*this = str;
}

//---------------------------------------------------------
// nsString::operator const char*:
//---------------------------------------------------------
nsString::operator const char* () const
{
	return m_str;
}

//---------------------------------------------------------
// nsString::operator = :
//---------------------------------------------------------
nsString& nsString::operator = ( const char* str )
{
	if ( str )
	{
		strncpy( m_str, str, MAX_SIZE - 1 );
		m_str[MAX_SIZE - 1] = 0;
	}
	else
		memset( m_str, 0, MAX_SIZE );

	return *this;
}

//---------------------------------------------------------
// nsString::operator ==:
//---------------------------------------------------------
bool nsString::operator == ( const char* str )
{
	if ( !str ) return false;

	const char*	s1 = m_str;
	const char*	s2 = str;
	while ( *s1 && *s2 )
	{
		if ( *s1 != *s2 ) return false;
		s1++;
		s2++;
	}

	return *s1 == *s2;
}

//---------------------------------------------------------
// nsString::operator != : 
//---------------------------------------------------------
bool nsString::operator != ( const char* str )
{
	return !(*this == str);
}

//---------------------------------------------------------
// nsString::operator []: 
//---------------------------------------------------------
char& nsString::operator [] ( const int idx )
{
	return m_str[idx];
}

#endif	//_Str_H_