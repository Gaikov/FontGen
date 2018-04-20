// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Var.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Var_H_
#define	_Var_H_

#include "nsLib/comm_types.h"

#define	GVF_SAVABLE		1	//сохраняется в config.cfg, если cfg_savevars 1 - сохраняются все короме GVF_INTERNAL
#define GVF_READONLY	2	//переменная не устанавливается с консоли
#define GVF_INTERNAL	4	//переменная для внутреннего использования (для привязки к клавишам, например...)

//-----------------------------------------------------
//  class nsVar:  
//-----------------------------------------------------
class nsVar
{
friend class nsConfig;

public:
	inline const char*	String() { return m_currValue; }
	inline float		Value() { return m_value; }
	
	void				SetValue( float val );
	void				SetString( const char* str );

	float				GetDefaultValue();
	const char*			GetDefaultString();
	void				SetDefault();

	const char*			GetName() { return m_name; }

	void				Inc() { m_value += 1.0f; }
	void				Dec() { m_value -= 1.0f; }

private:
	char				*m_name;
	uint				m_flags;
	
	float				m_value;
	char				*m_defValue;
	char				*m_currValue;

	nsVar				*m_next;

private:
	nsVar( const char* name, const char* defValue, uint flags );
	virtual ~nsVar();
};

#endif //_Var_H_