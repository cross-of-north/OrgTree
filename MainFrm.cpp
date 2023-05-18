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

// MainFrm.cpp : implementation of the MainFrame class
//

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "OrgTreeApp.h"
#include "OrgTreeView.h"
#include "OrgTreeDoc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_PRINT, &MainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &MainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &MainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &MainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND( ID_LEFTTORIGHT_TREEVIEW_BUTTON, &MainFrame::OnLeftToRightOrgTreeViewButton )
	ON_COMMAND( ID_UPWARD_ANCESTOR_TREEVIEW_BUTTON, &MainFrame::OnUpwardAncestorOrgTreeViewButton )
	ON_COMMAND( ID_DOWNWARD_DESCENDANT_TREEVIEW_BUTTON, &MainFrame::OnDownwardDescendantOrgTreeViewButton )
	ON_COMMAND( ID_OUTLOOK_TREEVIEW_BUTTON, &MainFrame::OnOutlookOrgTreeViewButton )
	ON_COMMAND( ID_GALLERY_TREEVIEW_BUTTON, &MainFrame::OnGalleryOrgTreeViewButton )
	ON_COMMAND( ID_CREATEROOT_BUTTON, &MainFrame::OnCreateRootButton )
  ON_COMMAND( ID_CREATEDESCENDANT_BUTTON, &MainFrame::OnCreateDescendantButton )
	ON_COMMAND( ID_CREATESIBLING_BUTTON, &MainFrame::OnCreateSiblingButton )
	ON_COMMAND( ID_DELETE_BUTTON, &MainFrame::OnDeleteButton )
	ON_COMMAND( ID_MYFAMILY_COMBO, &MainFrame::OnMyFamilyCombo )
	ON_COMMAND( ID_RELATION_COMBO, &MainFrame::OnRelationCombo )
	ON_COMMAND( ID_RELATIONGENDER_COMBO, &MainFrame::OnRelationGenderCombo )
	ON_COMMAND( ID_GRANDPARENT_COMBO, &MainFrame::OnGrandParentCombo )
	ON_COMMAND( ID_GREATGRANDPARENTGENDER_COMBO, &MainFrame::OnGreatGrandParentGenderCombo )
	ON_COMMAND( ID_GREATGRANDPARENT_COMBO, &MainFrame::OnGreatGrandParentCombo )
	ON_COMMAND( ID_CONTEXTSEARCH_BUTTON, &MainFrame::OnContextSearchButton )
END_MESSAGE_MAP()

// MainFrame construction/destruction

MainFrame::MainFrame() noexcept
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005 );
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL MainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void MainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// MainFrame message handlers

void MainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void MainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void MainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void MainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void MainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

COrgCtrl * MainFrame::GetOrgCtrl() const {
	COrgCtrl * ctrl = NULL;
	OrgTreeView * view = dynamic_cast < OrgTreeView * > ( GetActiveView() );
	if ( view != NULL ) {
		ctrl = &view->GetOrgCtrl();
	}
	return ctrl;
}

void MainFrame::SetOrgCtrlMode( const COrgCtrlView::Mode mode ) {
	COrgCtrl * ctrl = GetOrgCtrl();
	if ( ctrl != NULL ) {
		ctrl->GetView().SetMode( mode );
		ctrl->Invalidate();
	}
}

void MainFrame::OnLeftToRightOrgTreeViewButton()
{
	SetOrgCtrlMode( COrgCtrlView::Mode::LeftToRight );
}


void MainFrame::OnDownwardDescendantOrgTreeViewButton()
{
	SetOrgCtrlMode( COrgCtrlView::Mode::UpsideDownTree );
}

void MainFrame::OnUpwardAncestorOrgTreeViewButton()
{
	SetOrgCtrlMode( COrgCtrlView::Mode::Tree );
}

void MainFrame::OnOutlookOrgTreeViewButton() {
	SetOrgCtrlMode( COrgCtrlView::Mode::Outlook );
}

void MainFrame::OnGalleryOrgTreeViewButton()
{
	SetOrgCtrlMode( COrgCtrlView::Mode::Gallery );
}

OrgTreeDoc * MainFrame::GetDocument() {
	return dynamic_cast < OrgTreeDoc * > ( GetActiveDocument() );
}

void MainFrame::OnCreateRootButton()
{
	if ( OrgTreeDoc * doc = GetDocument() )	{
		doc->CreateContextNode( CString(), CString(), 0, 0, 0 );
	}
}

void MainFrame::OnCreateDescendantButton()
{
	if ( OrgTreeDoc * doc = GetDocument() ) {
		doc->CreateDescendantNode();
	}
}

void MainFrame::OnCreateSiblingButton()
{
	if ( OrgTreeDoc * doc = GetDocument() ) {
		doc->CreateSiblingNode();
	}
}

void MainFrame::OnDeleteButton()
{
	if ( OrgTreeDoc * doc = GetDocument() ) {
		doc->DeleteNode();
	}
}

void MainFrame::OnMyFamilyCombo()
{}

void MainFrame::OnRelationCombo()
{}

void MainFrame::OnRelationGenderCombo()
{}

void MainFrame::OnGrandParentCombo()
{}

void MainFrame::OnGreatGrandParentGenderCombo()
{}

void MainFrame::OnGreatGrandParentCombo()
{}

void MainFrame::OnContextSearchButton()
{}

	// CreateMainFrameContextNodeGridRow( const CString& uniqueAggregateNodeId, const CString& productionRuleString, DWORD parentCxNodeObjId, DWORD cxNodeObjId, DWORD cxNodeThreadId )
	// uniqueAggregateNodeId = L"Boy@c0:627e:7f00:d5:d430:ef2d:23bd:26f0#57895#23", productionRuleString = L"( Wife? & Parents & Children* ) | CDATA )", parentCxNodeObjId = 0, cxNodeObjId = 1193322685, cxNodeThreadId = 75716
	// uniqueAggregateNodeId = L"Parents@c0:627e:7f00:37:c216:396:1e89:d374#58768#23", productionRuleString = L"CDATA", parentCxNodeObjId = 1193322685, cxNodeObjId = 371259990, cxNodeThreadId = 74612
	// uniqueAggregateNodeId = L"Children@c0:627e:7f00:e1:7cbf:f6cc:110a:d94e#60760#23", productionRuleString = L"CDATA", parentCxNodeObjId = 1193322685, cxNodeObjId = 700228782, cxNodeThreadId = 116612
	// (see 'boy dtd grid.png' for how it looked in the prototype)
  // (see 'Boy.dtd' which is the DTD that generated the above data)
