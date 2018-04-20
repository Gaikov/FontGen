// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file BitmapSaver.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_BitmapSaver_H_
#define	_BitmapSaver_H_

#include "nsLib/comm_types.h"
#include "Core/SmartPtr.h"

class nsBitmapSaver
{
public:
	typedef nsSmartPtr<nsBitmapSaver>	sp_t;

public:
	nsBitmapSaver( uint width, uint height );
	virtual ~nsBitmapSaver();

	bool	CopyMonoBitmap( int posX, int posY, int width, int height, const byte *data );
	bool	Save( const char *fileName );

	uint	GetWidth() const { return m_width; }
	uint	GetHeight() const { return m_height; }

private:
	struct pixel_t
	{
		byte	r, g, b, a;
	};
	
private:
	uint	m_width, m_height;
	pixel_t	*m_pixels;
	ILuint	m_ilImage;

private:
	inline void	SetPixel( int x, int y, const pixel_t &p );
};

//---------------------------------------------------------
// nsBitmapSaver::SetPixel:
//---------------------------------------------------------
void nsBitmapSaver::SetPixel( int x, int y, const pixel_t &p )
{
	y = m_height - y - 1;
	m_pixels[m_width * y + x] = p;
}

#endif	//_BitmapSaver_H_