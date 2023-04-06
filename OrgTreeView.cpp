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

// OrgTreeView.cpp : implementation of the OrgTreeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OrgTreeApp.h"
#endif

#include "OrgTreeDoc.h"
#include "OrgTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// OrgTreeView

IMPLEMENT_DYNCREATE(OrgTreeView, CFormView)

BEGIN_MESSAGE_MAP(OrgTreeView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &OrgTreeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// OrgTreeView construction/destruction

OrgTreeView::OrgTreeView() noexcept
	: CFormView(IDD_TREEVIEW_FORM)
{
	// TODO: add construction code here

}

OrgTreeView::~OrgTreeView()
{
}

void OrgTreeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL OrgTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void OrgTreeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// OrgTreeView printing


void OrgTreeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL OrgTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void OrgTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void OrgTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void OrgTreeView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void OrgTreeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void OrgTreeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// OrgTreeView diagnostics

#ifdef _DEBUG
void OrgTreeView::AssertValid() const
{
	CFormView::AssertValid();
}

void OrgTreeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

OrgTreeDoc* OrgTreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(OrgTreeDoc)));
	return (OrgTreeDoc*)m_pDocument;
}
#endif //_DEBUG

BOOL OrgTreeView::Create
( LPCTSTR lpszClassName
    , LPCTSTR lpszWindowName
    , DWORD dwRequestedStyle
    , const RECT & rect
    , CWnd * pParentWnd
    , UINT nID
    , CCreateContext * pContext
)
{
    BOOL bResult = CFormView::Create(lpszClassName, lpszWindowName, dwRequestedStyle, rect, pParentWnd, nID, pContext);
	m_orgCtrl.Create( 0, CRect( 0, 0, 100, 100 ), this, 10000 );
	return bResult;
}

// OrgTreeView message handlers


void OrgTreeView::OnSize( UINT nType, int cx, int cy ) {
	CFormView::OnSize( nType, cx, cy );
	if ( m_orgCtrl.GetSafeHwnd() != NULL ) {
		CRect rect;
		GetWindowRect( &rect );
		m_orgCtrl.SetWindowPos( &m_orgCtrl, 0, 0, rect.right, rect.bottom, SWP_NOZORDER | SWP_SHOWWINDOW );
	}
}
