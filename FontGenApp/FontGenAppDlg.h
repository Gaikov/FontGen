// FontGenAppDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "GenTool.h"
#include "afxwin.h"

// CFontGenAppDlg dialog
class CFontGenAppDlg : public CDialog, public IProgressCallbak
{
// Construction
public:
	CFontGenAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FONTGENAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	virtual void	SetPercent( uint val );
	int				GetInt( CEdit &edit );
	void			SetInt( CEdit &edit, int val );


// Implementation
protected:
	HICON		m_hIcon;
	nsGenTool	m_genTool;
	CString		m_ttfFileName;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFontButton();
	CProgressCtrl m_progBar;
	CEdit m_texSizeEdit;
	CEdit m_charWidthEdit;
	CEdit m_charHeightEdit;
	afx_msg void OnBnClickedGenButton();
	afx_msg void OnBnClickedSaveButton();
};
