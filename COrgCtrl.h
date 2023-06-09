#pragma once

#include "IOrgTreeDoc.h"
#include "COrgCtrlView.h"

#define ORGCTRLWNDCLASS _T("OrgCtrl")

class COrgCtrl: public CWnd
{
// Construction
public:
	COrgCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrgCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COrgCtrl();

	BOOL Create( DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID );

	// Generated message map functions
protected:
	//{{AFX_MSG(COrgCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL RegisterWndClass();

	CPoint m_ptPrevDragPoint;
	CPoint m_ptMouseDownPoint;
	BOOL m_bDragging{ FALSE };
	UINT_PTR m_nTimerID{ 0 };
	BOOL m_bInvalidate{ FALSE };
	const IOrgTreeDoc * m_document{ nullptr };
	COrgCtrlView m_view;

	float GetZoomRatio() const;
	void SetZoomRatio( float fZoomRatio, const CPoint & ptCenter = {} );

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnTimer( UINT_PTR nIDEvent );
	afx_msg BOOL OnEraseBkgnd( CDC * pDC );

	void SetDocument( const IOrgTreeDoc * document );
	const IOrgTreeDoc * GetDocument() { return m_document; }
	COrgCtrlView & GetView() { return m_view; }
};
