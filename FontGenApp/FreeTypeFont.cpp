// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FreeTypeFont.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "FreeTypeFont.h"
#include "Core/log.h"
#include "core/Package.h"

//---------------------------------------------------------
// nsFreeTypeFont::nsFreeTypeFont:
//---------------------------------------------------------
nsFreeTypeFont::nsFreeTypeFont() :
	m_font( 0 )
{
	m_glyphDesc.data = 0;
	FT_Init_FreeType( &m_ftLib );
}

//---------------------------------------------------------
// nsFreeTypeFont::~nsFreeTypeFont:
//---------------------------------------------------------
nsFreeTypeFont::~nsFreeTypeFont()
{
	if ( m_glyphDesc.data )	delete [] m_glyphDesc.data;
	FT_Done_FreeType( m_ftLib );
}

//---------------------------------------------------------
// nsFreeTypeFont::BindFont:
//---------------------------------------------------------
bool nsFreeTypeFont::BindFont( const char *fileName )
{
	if ( !StrCheck( fileName ) ) return false;

	LogPrintf( PRN_ALL, "... loading font '%s'\n", fileName );
	if ( m_font ) FT_Done_Face( m_font );

	int	err;
	err = FT_New_Face( m_ftLib, fileName, 0, &m_font );
	if ( err )
	{
		LogPrintf( PRN_ALL, "WARNING: Can't create TrueType face!\n" );
		return false;
	}

	for(int i=0;i<m_font->num_charmaps;i++)
	{
		if(m_font->charmaps[i]->platform_id == TT_PLATFORM_MICROSOFT &&
			m_font->charmaps[i]->encoding_id == TT_MS_ID_UNICODE_CS)
		{
			FT_Set_Charmap(m_font, m_font->charmaps[i]);
			break;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsFreeTypeFont::SetSize:
//---------------------------------------------------------
void nsFreeTypeFont::SetSize( uint width, uint height )
{
	if ( !m_font ) return;
	FT_Set_Pixel_Sizes( m_font, width, height );
}

//---------------------------------------------------------
// nsFreeTypeFont::GetGlyphDesc:
//---------------------------------------------------------
const glyphDesc_t*	nsFreeTypeFont::GetGlyphDesc( char ch )
{
	if ( !m_font ) return 0;

	FT_UInt	idx = FT_Get_Char_Index( m_font, (FT_ULong)ch );
	int err = FT_Load_Glyph( m_font, idx, 0 );
	if ( err )
	{
		LogPrintf( PRN_ALL, "WARNING: can't load glyph!\n" );
		return 0;
	}

	if ( m_font->glyph->format != FT_GLYPH_FORMAT_BITMAP )
	{
		err = FT_Render_Glyph( m_font->glyph, FT_RENDER_MODE_NORMAL );
		if ( err )
		{
			LogPrintf( PRN_ALL, "WARNING: can't render glyph!\n" );
			return 0;
		}
	}

	if ( m_glyphDesc.data ) delete [] m_glyphDesc.data;

	FT_Bitmap			&bit = m_font->glyph->bitmap;
	FT_Glyph_Metrics	&met = m_font->glyph->metrics;

	m_glyphDesc.data = new byte[ bit.width * bit.rows ];
	m_glyphDesc.width = bit.width;
	m_glyphDesc.height = bit.rows;

	m_glyphDesc.offsX = met.horiBearingX >> 6;
	m_glyphDesc.offsY = met.horiBearingY >> 6;
	m_glyphDesc.step = met.horiAdvance >> 6;

	byte	*dst = m_glyphDesc.data;
	byte	*src = bit.buffer;

	for ( int y = 0; y < bit.rows; ++y, dst += bit.width, src += bit.pitch )
		memcpy( dst, src, bit.width );

	return &m_glyphDesc;
}
