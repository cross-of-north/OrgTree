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

// OrgTreeView.h : interface of the OrgTreeView class
//

#pragma once

#include "COrgCtrl.h"
#include "OrgTreeDoc.h"

class OrgTreeView : public CFormView
{
protected: // create from serialization only
	OrgTreeView() noexcept;
	DECLARE_DYNCREATE(OrgTreeView)

	COrgCtrl m_orgCtrl;
public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TREEVIEW_FORM };
#endif

// Attributes
public:
	OrgTreeDoc* GetDocument() const;
	COrgCtrl & GetOrgCtrl() { return m_orgCtrl; }

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~OrgTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	BOOL Create
	( LPCTSTR lpszClassName
		, LPCTSTR lpszWindowName
		, DWORD dwRequestedStyle
		, const RECT & rect
		, CWnd * pParentWnd
		, UINT nID
		, CCreateContext * pContext
	);

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize( UINT nType, int cx, int cy );
};

#ifndef _DEBUG  // debug version in OrgTreeView.cpp
inline OrgTreeDoc* OrgTreeView::GetDocument() const
   { return reinterpret_cast<OrgTreeDoc*>(m_pDocument); }
#endif

