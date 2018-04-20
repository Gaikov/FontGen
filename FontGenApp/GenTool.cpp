// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GenTool.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "GenTool.h"
#include "nsLib/StrTools.h"
#include "Core/log.h"
#include "Core/ScriptSaver.h"


//---------------------------------------------------------
// nsGenTool::nsGenTool:
//---------------------------------------------------------
nsGenTool::nsGenTool() :
	m_fill( 0 )
{

}

//---------------------------------------------------------
// nsGenTool::~nsGenTool:
//---------------------------------------------------------
nsGenTool::~nsGenTool()
{
	if ( m_fill ) delete [] m_fill;
}

//---------------------------------------------------------
// nsGenTool::Generate:
//---------------------------------------------------------
bool nsGenTool::Generate( const char *ttfFileName, uint texSize, uint fontWidth, uint fontHeight,  IProgressCallbak *cb )
{
	if ( !m_fontLoader.BindFont( ttfFileName ) ) return false;

	m_fontLoader.SetSize( fontWidth, fontHeight );

	m_bitMap = new nsBitmapSaver( texSize, texSize );
	if ( m_fill ) delete [] m_fill;
	m_fill = new byte[ texSize * texSize ];
	memset( m_fill, 0, texSize * texSize );

	memset( m_glyphs, 0, sizeof(glyphPos_t) * 256 );

	for ( int ch = 0; ch < 256; ++ch )
	{
		const glyphDesc_t	*g = m_fontLoader.GetGlyphDesc( ch );
		if ( g )
		{
			int	pos[2];
			if ( !FindFreePos( g->width + 1, g->height + 1, pos ) )
			{
				LogPrintf( PRN_ALL, "WARNING: texture too small!\n" );
				break;
			}

			m_bitMap->CopyMonoBitmap( pos[0] + 1, pos[1] + 1, g->width, g->height, g->data );

			MarkPos( pos[0], pos[1], g->width + 1, g->height + 1, 1 );

			if ( cb )
				cb->SetPercent( int(ch /255.0f * 100.0f) );

			m_glyphs[ch].posX = pos[0] + 1;
			m_glyphs[ch].posY = pos[1] + 1;
			m_glyphs[ch].g = *g;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsGenTool::Save:
//---------------------------------------------------------
bool nsGenTool::Save( const char *fileName )
{
	nsString	texFile = fileName;
	texFile.ReplaceFileExt( ".png" );
	texFile.ConvFileName();
	if ( !m_bitMap->Save( texFile ) ) return false;

	nsString	scriptFile = texFile;
	scriptFile.ReplaceFileExt( ".txt" );

	nsScriptSaver	saver( scriptFile );

	saver.Printf( "//Generate by FontGen" );
	saver.Printf( "//Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.\n" );
	saver.Printf( "$version 1.5\n" );
	
	saver.BlockBegin( "$textures" );
	nsString	texName;
	char *slash = (char*)strrchr( texFile, '/' );
	if ( slash )
		texName = slash + 1;
	else
		texName = texFile;

	saver.Printf( "$tex \"%s\"", texName.AsChar() );
	saver.BlockEnd();

	saver.BlockBegin( "$chars_data" );

	for ( int i = 0; i < 256; ++i )
	{
		saver.BlockBegin( "$char" );

		saver.Printf( "$code %i // %c", i, (char)i );
		saver.Printf( "$tex_id 0" );
		saver.Printf( "$coord %i %i", m_glyphs[i].posX, m_glyphs[i].posY );
		saver.Printf( "$size %i %i", m_glyphs[i].g.width, m_glyphs[i].g.height );
		saver.Printf( "$offs %i %i", m_glyphs[i].g.offsX, m_glyphs[i].g.offsY );
		saver.Printf( "$step %i", m_glyphs[i].g.step );

		saver.BlockEnd();
	}

	saver.BlockEnd();

	return true;
}

//---------------------------------------------------------
// nsGenTool::FindFreePos:
//---------------------------------------------------------
bool nsGenTool::FindFreePos( int width, int height, int pos[2] )
{
	for ( uint y = 0; y < m_bitMap->GetHeight(); ++y )
		for ( uint x = 0; x < m_bitMap->GetWidth(); ++x )
		{
			if ( IsFreePos( width, height, x, y ) )
			{
				pos[0] = x;
				pos[1] = y;
				return true;
			}
		}
	return false;
}

//---------------------------------------------------------
// nsGenTool::IsFreePos:
//---------------------------------------------------------
bool nsGenTool::IsFreePos( int width, int height, int posX, int posY )
{
	for ( int y = posY; y < posY + height; ++y )
		for ( int x = posX; x < posX + width; ++x )
		{
			if ( GetFilled( x, y ) )
				return false;
		}

	return true;
}

//---------------------------------------------------------
// nsGenTool::MarkPos:
//---------------------------------------------------------
void nsGenTool::MarkPos( int posX, int posY, int width, int height, byte val )
{
	for ( int y = posY; y < posY + height; ++y )
		for ( int x = posX; x < posX + width; ++x )
			SetFilled( x, y, val );
}