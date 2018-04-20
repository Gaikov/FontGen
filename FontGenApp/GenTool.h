// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GenTool.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_GenTool_H_
#define	_GenTool_H_

#include "BitmapSaver.h"
#include "FreeTypeFont.h"

class IProgressCallbak
{
public:
	virtual void SetPercent( uint val ) = 0;
};

class nsGenTool
{
public:
	nsGenTool();
	virtual ~nsGenTool();

	bool					Generate( const char *ttfFileName, uint texSize, uint fontWidth, uint fontHeight, IProgressCallbak *cb = 0 );
	
	bool					Save( const char *fileName );
	HBITMAP					GetTexture();

private:
	struct glyphPos_t
	{
		glyphDesc_t	g;
		int			posX, posY;
	};

private:
	nsBitmapSaver::sp_t		m_bitMap;
	glyphPos_t				m_glyphs[256];
	byte					*m_fill;
	nsFreeTypeFont			m_fontLoader;

private:
	bool					FindFreePos( int width, int height, int pos[2] );
	bool					IsFreePos( int widht, int height, int posX, int posY );
	void					MarkPos( int posX, int posY, int width, int height, byte val );

	inline byte				GetFilled( int x, int y );
	inline void				SetFilled( int x, int y, byte val );
};

//---------------------------------------------------------
// nsGenTool::GetFilled:
//---------------------------------------------------------
inline byte	nsGenTool::GetFilled( int x, int y )
{
	if ( !m_fill ) return 1;
	if ( x < 0 || x >= (int)m_bitMap->GetWidth() ) return 1;
	if ( y < 0 || y >= (int)m_bitMap->GetHeight() ) return 1;
	return m_fill[y * m_bitMap->GetWidth() + x];
}

//---------------------------------------------------------
// nsGenTool::SetFilled:
//---------------------------------------------------------
inline void	nsGenTool::SetFilled( int x, int y, byte val )
{
	if ( !m_fill ) return;
	if ( x < 0 || x >= (int)m_bitMap->GetWidth() ) return;
	if ( y < 0 || y >= (int)m_bitMap->GetHeight() ) return;
	m_fill[y * m_bitMap->GetWidth() + x] = val;
}

#endif	//_GenTool_H_