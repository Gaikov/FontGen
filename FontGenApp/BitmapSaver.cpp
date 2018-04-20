// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file BitmapSaver.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BitmapSaver.h"
#include "nsLib/StrTools.h"
#include "Core/log.h"

//---------------------------------------------------------
// nsBitmapSaver::nsBitmapSaver:
//---------------------------------------------------------
nsBitmapSaver::nsBitmapSaver( uint width, uint height ) :
	m_ilImage( 0 )
{
	m_width = width;
	m_height = height;
	m_pixels = new pixel_t[m_height * m_width];

	pixel_t	p = { 255, 255, 255, 0 };
	for ( uint y = 0; y < m_height; ++y )
		for ( uint x = 0; x < m_width; ++x )
			SetPixel( x, y, p );

	ilGenImages( 1, &m_ilImage );
	if ( ilGetError() != IL_NO_ERROR )
	{
		LogPrintf( PRN_ALL, "ilGenImage - error!\n" );
		m_ilImage = 0;
	}

	ilEnable( IL_FILE_OVERWRITE );
}

//---------------------------------------------------------
// nsBitmapSaver::~nsBitmapSaver:
//---------------------------------------------------------
nsBitmapSaver::~nsBitmapSaver()
{
	ilDeleteImages( 1, &m_ilImage );
	delete [] m_pixels;
}

//---------------------------------------------------------
// nsBitmapSaver::CopyMonoBitmap:
//---------------------------------------------------------
bool nsBitmapSaver::CopyMonoBitmap( int posX, int posY, int width, int height, const byte *data )
{
	for ( int y = 0; y < height; ++y )
		for ( int x = 0; x < width; ++x )
		{
			pixel_t	p;
			byte	b = data[y * width + x];
			
			p.a = b;
			if ( b )
				p.r = p.g = p.b = 255;
			else
				p.r = p.g = p.b = 0;
			
			SetPixel( posX + x, posY + y, p );
		}

	return true;
}

//---------------------------------------------------------
// nsBitmapSaver::Save:
//---------------------------------------------------------
bool nsBitmapSaver::Save( const char *fileName )
{
	if ( !StrCheck( fileName ) ) return false;

	LogPrintf( PRN_ALL, "... writing image '%s'\n", fileName );

	if ( !m_ilImage )
	{
		LogPrintf( PRN_ALL, "WARNING: il image not created!\n" );
		return false;
	}

	ilBindImage( m_ilImage );
	if ( ilGetError() != IL_NO_ERROR )
	{
		LogPrintf( PRN_ALL, "WARNING: can't bind image!\n" );
		return false;
	}

	ilTexImage( m_width, m_height, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, m_pixels );
	if ( ilGetError() != IL_NO_ERROR )
	{
		LogPrintf( PRN_ALL, "WARNING: can't set pixels!\n" );
		return false;
	}

	nsString	str = fileName;
	if ( !ilSave( IL_PNG, str.AsChar() ) )
	{
		LogPrintf( PRN_ALL, "WARNING: IL can't save image!\n" );
		ILenum err = ilGetError();
		return false;
	}

	return true;
}

