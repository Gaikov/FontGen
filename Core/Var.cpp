// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Var.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "Var.h"
#include "headers.h"
#include "Memory.h"
#include "nsLib/StrTools.h"

//-----------------------------------------------------
//  nsVar::nsVar:  
//-----------------------------------------------------
nsVar::nsVar( const char* name, const char* defValue, uint flags ) :
	m_next( 0 )
{
	assert( name != 0 && defValue != 0 );
	m_name = my_strdup( name );
	m_defValue = my_strdup( defValue );
	m_currValue = my_strdup( defValue );
	m_value = (float)atof( m_currValue );
	m_flags = flags;
}

//-----------------------------------------------------
//  nsVar::~nsVar:  
//-----------------------------------------------------
nsVar::~nsVar()
{
	if ( m_name ) my_free( m_name );
	if ( m_defValue ) my_free( m_defValue );
	if ( m_currValue ) my_free( m_currValue );
}

//-----------------------------------------------------
//  nsVar::SetValue:  
//-----------------------------------------------------
void nsVar::SetValue( float val )
{
	if ( val == (int)val )
		SetString( StrPrintf( "%i", (int)val) );
	else
		SetString( StrPrintf( "%f", val ) );
}

//-----------------------------------------------------
//  nsVar::SetString:  
//-----------------------------------------------------
void nsVar::SetString( const char* str )
{
	if ( !str ) str = "";
	my_free( m_currValue );
	m_currValue = my_strdup( str );
	m_value = (float)atof( m_currValue );
}

//-----------------------------------------------------
//  nsVar::GetDefaultValue:  
//-----------------------------------------------------
float nsVar::GetDefaultValue()
{
	return (float)atof( m_defValue );
}

//-----------------------------------------------------
//  nsVar::GetDefaultString:  
//-----------------------------------------------------
const char* nsVar::GetDefaultString()
{
	return m_defValue;
}

//---------------------------------------------------------
// nsVar::SetDefault: 
//---------------------------------------------------------
void nsVar::SetDefault()
{
	SetString( m_defValue );
}