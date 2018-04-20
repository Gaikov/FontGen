// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FreeTypeFont.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FreeTypeFont_H_
#define	_FreeTypeFont_H_

#include "Core/SmartPtr.h"

//---------------------------------------------------------
// glyphDesc_t:
//---------------------------------------------------------
struct glyphDesc_t
{
	int		width, height;	//������� �������� ����� (�������)
	int		step;			//��� �� ���������� �������
	int		offsX;			//�������� �� ������� ������ �� ����������� ��� ������ �������
	int		offsY;			//�������� �� ������� ����� �� ������� ������� �������
	byte	*data;
};

//---------------------------------------------------------
// nsFreeTypeFont:
//---------------------------------------------------------
class nsFreeTypeFont
{
public:
	typedef nsSmartPtr<nsFreeTypeFont>	sp_t;

public:
	nsFreeTypeFont();
	~nsFreeTypeFont();

	bool				BindFont( const char *fileName );
	void				SetSize( uint width, uint height );
	const glyphDesc_t*	GetGlyphDesc( char ch );
	
private:
	FT_Library			m_ftLib;
	FT_Face				m_font;
	glyphDesc_t			m_glyphDesc;
};

#endif	//_FreeTypeFont_H_