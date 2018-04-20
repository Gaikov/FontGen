// FontGenApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FontGenApp.h"
#include "FontGenAppDlg.h"
#include "Core/Core.h"
#include "Core/AppInfo.h"
#include "Core/log.h"
#include "Core/Config.h"

//---------------------------------------------------------
// nsGenAppInfo:
//---------------------------------------------------------
class nsGenAppInfo : public IAppInfo
{
	virtual const char*		GetAppName() { return "FontGen"; }
	virtual const char*		GetDefCfgPath() { return 0; }
	virtual IDataReader*	GetCfgReader() { return 0; }
	virtual IDataWriter*	GetCfgWriter() { return 0; }
};

nsGenAppInfo	g_app;

//---------------------------------------------------------
// App_GetInfo:
//---------------------------------------------------------
IAppInfo* App_GetInfo()
{
	return &g_app;
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFontGenAppApp

BEGIN_MESSAGE_MAP(CFontGenAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFontGenAppApp construction

CFontGenAppApp::CFontGenAppApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CFontGenAppApp object

CFontGenAppApp theApp;


// CFontGenAppApp initialization

BOOL CFontGenAppApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	if ( !nsCore::Init() ) return FALSE;

	LogPrintf( PRN_ALL, "... IL init\n" );
	ilInit();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CFontGenAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

//---------------------------------------------------------
// CFontGenAppApp::ExitInstance:
//---------------------------------------------------------
int CFontGenAppApp::ExitInstance()
{
	LogPrintf( PRN_ALL, "... IL shutdown\n" );
	ilShutDown();
	g_cfg->SaveConfig();
	nsCore::Release();
	return CWinApp::ExitInstance();
}
