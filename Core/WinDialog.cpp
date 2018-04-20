// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file WinDialog.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "WinDialog.h"

//---------------------------------------------------------
// nsWinDialog::nsWinDialog: 
//---------------------------------------------------------
nsWinDialog::nsWinDialog()
{
	
}

//---------------------------------------------------------
// nsWinDialog::~nsWinDialog: 
//---------------------------------------------------------
nsWinDialog::~nsWinDialog()
{

}

//---------------------------------------------------------
// nsWinDialog::DoModal: 
//---------------------------------------------------------
int nsWinDialog::DoModal( HINSTANCE hinst, HWND hParent, char *tpl )
{
	if ( !tpl ) 
	{
		return 0;
	}

	return DialogBoxParam( hinst, tpl, hParent, DlgProc, (long)this );
}

//---------------------------------------------------------
// nsWinDialog::DlgProc: 
//---------------------------------------------------------
BOOL CALLBACK nsWinDialog::DlgProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	nsWinDialog	*pdlg;
	if ( uiMsg == WM_INITDIALOG )
	{
		SetWindowLong( hDlg, GWL_USERDATA, lParam );
		pdlg = (nsWinDialog*)lParam;
		pdlg->m_hDlg = hDlg;
	}
	else
		pdlg = (nsWinDialog*)GetWindowLong( hDlg, GWL_USERDATA );

	if ( !pdlg ) return 0;
	
	switch ( uiMsg )
	{
	case WM_INITDIALOG:
		if ( !pdlg->OnInitDialog() )
			return pdlg->OnCancel();
		else
			return 0;
	case WM_SYSCOMMAND:
		if ( wParam == SC_CLOSE ) return pdlg->OnCancel();
		break;
	case WM_COMMAND:
		return pdlg->OnCommand( LOWORD(wParam), HIWORD(wParam) );
	default:
		return pdlg->CallBackProc( uiMsg, wParam, lParam );
	}
	return 0;
}

//---------------------------------------------------------
// nsWinDialog::cbox_AddString: 
//---------------------------------------------------------
void nsWinDialog::cbox_AddString( UINT id, const char *string )
{
	SendMessage( GetDlgItem( m_hDlg, id ), CB_ADDSTRING, 0, (long)string );
}

//---------------------------------------------------------
// nsWinDialog::cbox_SetSelected: 
//---------------------------------------------------------
void nsWinDialog::cbox_SetSelected(UINT id, int index)
{
	SendMessage( GetDlgItem( m_hDlg, id ), CB_SETCURSEL, index, 0 );
}

//---------------------------------------------------------
// nsWinDialog::cbox_SetSelected: 
//---------------------------------------------------------
void nsWinDialog::cbox_SetSelected( UINT id, const char* str )
{
	int idx = SendMessage( GetDlgItem( m_hDlg, id ), CB_FINDSTRING, 0, (LPARAM)str );
	if ( idx == LB_ERR ) return;
	SendMessage( GetDlgItem( m_hDlg, id ), CB_SETCURSEL, idx, 0 );
}

//---------------------------------------------------------
// nsWinDialog::cbox_GetSelected: 
//---------------------------------------------------------
int nsWinDialog::cbox_GetSelected(UINT id)
{
	return SendMessage( GetDlgItem( m_hDlg, id ), CB_GETCURSEL, 0, 0 );
}

//---------------------------------------------------------
// nsWinDialog::ctrl_SetText: 
//---------------------------------------------------------
void nsWinDialog::ctrl_SetText( UINT id, const char *text )
{
	if ( !text || !strlen( text ) ) return;
	HWND wnd = GetDlgItem( m_hDlg, id );
	if ( wnd ) SetWindowText( wnd, text );
}

//---------------------------------------------------------
// nsWinDialog::ctrl_SetPlace: 
//---------------------------------------------------------
void nsWinDialog::ctrl_SetPlace( UINT id, int x, int y, int width, int height )
{
	HWND wnd = GetDlgItem( m_hDlg, id );
	if ( !wnd ) return;

	RECT	rect;
	GetWindowRect( wnd, &rect );

	ScreenToClient( m_hDlg, (POINT*)&rect.left );
	ScreenToClient( m_hDlg, (POINT*)&rect.right );

	if ( !x ) x = rect.left;
	if ( !y ) y = rect.top;
	if ( !width ) width = rect.right - rect.left;
	if ( !height ) height = rect.bottom - rect.top;

	MoveWindow( wnd, x, y, width, height, TRUE );
}

//---------------------------------------------------------
// nsWinDialog::ctrl_SetWisible: 
//---------------------------------------------------------
void nsWinDialog::ctrl_SetVisible( UINT id, bool vis )
{
	HWND wnd = GetDlgItem( m_hDlg, id );
	if ( !wnd ) return;

	ShowWindow( wnd, vis ? SW_SHOW : SW_HIDE );
}

//---------------------------------------------------------
// nsWinDialog::cbox_Clear: 
//---------------------------------------------------------
void nsWinDialog::cbox_Clear(UINT id)
{
	SendMessage( GetDlgItem( m_hDlg, id ), CB_RESETCONTENT, 0, 0 );
}

//---------------------------------------------------------
// nsWinDialog::check_GetChecked: 
//---------------------------------------------------------
int nsWinDialog::check_GetChecked(UINT id)
{
	return IsDlgButtonChecked( m_hDlg, id ) == BST_CHECKED;
}

//---------------------------------------------------------
// nsWinDialog::check_SetChecked: 
//---------------------------------------------------------
void nsWinDialog::check_SetChecked(UINT id, int checked)
{
	CheckDlgButton( m_hDlg, id, checked ? BST_CHECKED : BST_UNCHECKED );
}

//---------------------------------------------------------
// nsWinDialog::ctrl_Enable: 
//---------------------------------------------------------
void nsWinDialog::ctrl_Enable(UINT id, int enable)
{
	EnableWindow( GetDlgItem( m_hDlg, id ), enable );
}
