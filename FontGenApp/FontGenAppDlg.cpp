// FontGenAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontGenApp.h"
#include "FontGenAppDlg.h"
#include "Core/Config.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFontGenAppDlg dialog




CFontGenAppDlg::CFontGenAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontGenAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontGenAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_WORK, m_progBar);
	DDX_Control(pDX, IDC_TEXSIZE_EDIT, m_texSizeEdit);
	DDX_Control(pDX, IDC_WIDTH_EDIT, m_charWidthEdit);
	DDX_Control(pDX, IDC_HEIGHT_EDIT, m_charHeightEdit);
	DDX_Control(pDX, IDC_COUNT_EDIT, m_countEdit);
	DDX_Control(pDX, IDC_CHARS_EDIT, m_charsEdit);
}

//---------------------------------------------------------
// CFontGenAppDlg::SetPercent:
//---------------------------------------------------------
void CFontGenAppDlg::SetPercent( uint val )
{
	m_progBar.SetPos( (int)val );
}

BEGIN_MESSAGE_MAP(CFontGenAppDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FONT_BUTTON, &CFontGenAppDlg::OnBnClickedFontButton)
	ON_BN_CLICKED(IDC_GEN_BUTTON, &CFontGenAppDlg::OnBnClickedGenButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CFontGenAppDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_ALL_RADIO, &CFontGenAppDlg::OnBnClickedAllRadio)
	ON_BN_CLICKED(IDC_MAX_RADIO, &CFontGenAppDlg::OnBnClickedMaxRadio)
	ON_BN_CLICKED(IDC_SELECTED_RADIO, &CFontGenAppDlg::OnBnClickedSelectedRadio)
END_MESSAGE_MAP()


// CFontGenAppDlg message handlers

nsVar	*texSize = 0;
nsVar	*fontWidth = 0;
nsVar	*fontHeight = 0;

BOOL CFontGenAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	texSize = g_cfg->RegVar( "texSize", "256", GVF_SAVABLE );
	fontWidth = g_cfg->RegVar( "fontWidth", "20", GVF_SAVABLE );
	fontHeight = g_cfg->RegVar( "fontHeight", "20", GVF_SAVABLE );

	SetInt( m_texSizeEdit, int(fabsf(texSize->Value())) );
	SetInt( m_charWidthEdit, int(fabsf(fontWidth->Value())) );
	SetInt( m_charHeightEdit, int(fabsf(fontHeight->Value())) );

	CheckDlgButton( IDC_ALL_RADIO, BST_CHECKED );
	m_countEdit.EnableWindow( FALSE );
	m_charsEdit.EnableWindow( FALSE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFontGenAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFontGenAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFontGenAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFontGenAppDlg::OnBnClickedFontButton()
{
	CFileDialog	dlg( TRUE, 0, 0, OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, "TrueType fonts|*.ttf||", 0, 0 );
	if ( dlg.DoModal() == IDOK )
	{
		SetDlgItemText( IDC_FILENAME_STATIC, dlg.GetPathName() );

		CWnd *but = GetDlgItem( IDC_GEN_BUTTON );
		if ( but ) but->EnableWindow();

		m_ttfFileName = dlg.GetPathName();
	}
}

//---------------------------------------------------------
// CFontGenAppDlg::GetInt:
//---------------------------------------------------------
int CFontGenAppDlg::GetInt( CEdit &edit )
{
	CString	str;
	edit.GetWindowText( str );
	return atoi( str );
}

//---------------------------------------------------------
// CFontGenAppDlg::SetInt:
//---------------------------------------------------------
void CFontGenAppDlg::SetInt( CEdit &edit, int val )
{
	CString	str;
	str.Format( "%i", val );
	edit.SetWindowText( str );
}

//---------------------------------------------------------
// CFontGenAppDlg::OnBnClickedGenButton:
//---------------------------------------------------------
void CFontGenAppDlg::OnBnClickedGenButton()
{
	int texSize = GetInt( m_texSizeEdit );
	if ( !texSize )
	{
		MessageBox( "Invalid texture size!" );
		return;
	}

	int	fontWidth = GetInt( m_charWidthEdit );
	if ( !fontWidth )
	{
		MessageBox( "Invalid char width!" );
		return;
	}

	int fontHeight = GetInt( m_charHeightEdit );
	if ( !fontHeight )
	{
		MessageBox( "Invalid char height!" );
		return;
	}

	std::vector<char>	chars;
	if ( IsDlgButtonChecked( IDC_ALL_RADIO ) == BST_CHECKED )
	{
		for ( int i = 0; i < 256; ++i )
			chars.push_back( (char)i );
	}
	else if ( IsDlgButtonChecked( IDC_MAX_RADIO ) )
	{
		CString	str;
		m_countEdit.GetWindowText( str );
		int max = atoi( str );
		if ( max < 0 || max > 256 ) max = 256;
		
		for ( int i = 0; i < max; ++i )
			chars.push_back( (char)i );
	}
	else if ( IsDlgButtonChecked( IDC_SELECTED_RADIO ) )
	{
		CString	str;
		m_charsEdit.GetWindowText( str );
		for ( int i = 0; i < str.GetLength(); ++i )
			chars.push_back( str[i] );
	}

	CWnd	*but = GetDlgItem( IDC_SAVE_BUTTON );
	if ( !m_genTool.Generate( m_ttfFileName, texSize, fontWidth, fontHeight, &chars[0], (int)chars.size(), this ) )
	{
		if ( but ) but->EnableWindow( FALSE );
	}
	else
	{
		if ( but ) but->EnableWindow( TRUE );
	}
}

//---------------------------------------------------------
// CFontGenAppDlg::OnBnClickedSaveButton:
//---------------------------------------------------------
void CFontGenAppDlg::OnBnClickedSaveButton()
{
	CFileDialog	dlg( FALSE, 0, 0, OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, "Script *.txt|*.txt||", 0, 0 );
	if ( dlg.DoModal() == IDOK )
	{
		m_genTool.Save( dlg.GetPathName() );
	}
}

//---------------------------------------------------------
// CFontGenAppDlg::OnBnClickedAllRadio:
//---------------------------------------------------------
void CFontGenAppDlg::OnBnClickedAllRadio()
{
	m_countEdit.EnableWindow( FALSE );
	m_charsEdit.EnableWindow( FALSE );
}

//---------------------------------------------------------
// CFontGenAppDlg::OnBnClickedMaxRadio:
//---------------------------------------------------------
void CFontGenAppDlg::OnBnClickedMaxRadio()
{
	m_charsEdit.EnableWindow( FALSE );
	m_countEdit.EnableWindow( TRUE );
}

//---------------------------------------------------------
// CFontGenAppDlg::OnBnClickedSelectedRadio:
//---------------------------------------------------------
void CFontGenAppDlg::OnBnClickedSelectedRadio()
{
	m_charsEdit.EnableWindow( TRUE );
	m_countEdit.EnableWindow( FALSE );
}
