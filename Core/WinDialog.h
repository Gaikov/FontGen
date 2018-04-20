// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file WinDialog.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_WinDialog_H_
#define	_WinDialog_H_

#include "headers.h"

class nsWinDialog
{
public:
	void ctrl_Enable( UINT id, int enable );
	int DoModal( HINSTANCE hinst, HWND hParent, char *tpl );
	nsWinDialog();
	virtual ~nsWinDialog();

	static BOOL CALLBACK DlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );
	HWND	m_hDlg;

	virtual int OnInitDialog() = 0;
	virtual	BOOL CallBackProc( UINT uiMsg, WPARAM wParam, LPARAM lParam ) = 0;

protected:
	/*--------------------------------------------
	control members
	--------------------------------------------*/
	void	check_SetChecked( UINT id, int checked );
	int		check_GetChecked( UINT id );

	void	cbox_Clear( UINT id );
	void	cbox_AddString( UINT id, const char *string );
	void	cbox_SetSelected( UINT id, int index );
	void	cbox_SetSelected( UINT id, const char* str );
	int		cbox_GetSelected( UINT id );

	void	ctrl_SetText( UINT id, const char *text );
	void	ctrl_SetPlace( UINT id, int x, int y, int width, int height );
	void	ctrl_SetVisible( UINT id, bool vis );
	
	
	/*--------------------------------------------
	--------------------------------------------*/
	virtual int OnCommand( int control, int notify ) = 0;
	virtual int OnCancel() = 0;
	virtual int OnOK() = 0;
};

#endif //_WinDialog_H_
