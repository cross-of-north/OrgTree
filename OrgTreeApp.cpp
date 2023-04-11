// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// OrgTree.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "OrgTreeApp.h"
#include "MainFrm.h"

#include "OrgTreeDoc.h"
#include "OrgTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// OrgTreeApp

BEGIN_MESSAGE_MAP(OrgTreeApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &OrgTreeApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// OrgTreeApp construction

OrgTreeApp::OrgTreeApp() noexcept
	: m_data( std::make_shared< COrgCtrlData >() ) 
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("OrgTree.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	COrgCtrlDataItem::ptr_t pRoot = std::make_shared< COrgCtrlDataItem >();
	pRoot->GetRect() = { 50, 50, 70, 60 };
	COrgCtrlDataItem::ptr_t node1 = std::make_shared< COrgCtrlDataItem >();
	node1->GetRect() = { 80, 10, 100, 20 };
	COrgCtrlDataItem::ptr_t node2 = std::make_shared< COrgCtrlDataItem >();
	node2->GetRect() = { 80, 40, 100, 50 };
	COrgCtrlDataItem::ptr_t node3 = std::make_shared< COrgCtrlDataItem >();
	node3->GetRect() = { 80, 70, 100, 80 };
	COrgCtrlDataItem::ptr_t node4 = std::make_shared< COrgCtrlDataItem >();
	node4->GetRect() = { 110, 60, 130, 70 };
	COrgCtrlDataItem::ptr_t node5 = std::make_shared< COrgCtrlDataItem >();
	node5->GetRect() = { 110, 90, 130, 100 };
	pRoot->AddChild( node1 );
	pRoot->AddChild( node2 );
	node2->AddChild( node4 );
	node2->AddChild( node5 );
	pRoot->AddChild( node3 );

	m_data->GetRoot().AddChild( pRoot );
}

// The one and only OrgTreeApp object

OrgTreeApp theApp;


// OrgTreeApp initialization

BOOL OrgTreeApp::InitInstance()
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

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(OrgTreeDoc),
		RUNTIME_CLASS(MainFrame),       // main SDI frame window
		RUNTIME_CLASS(OrgTreeView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	OrgTreeView * view = dynamic_cast < OrgTreeView * > ( ( ( CFrameWnd * )m_pMainWnd )->GetActiveView() );
	if ( view == NULL ) {
		ASSERT( FALSE );
	} else {
		COrgCtrl & orgCtrl = view->GetOrgCtrl();
		orgCtrl.SetData( m_data );
	}

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int OrgTreeApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// OrgTreeApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void OrgTreeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// OrgTreeApp customization load/save methods

void OrgTreeApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void OrgTreeApp::LoadCustomState()
{
}

void OrgTreeApp::SaveCustomState()
{
}

// OrgTreeApp message handlers



