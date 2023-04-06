#pragma once

#include "COrgCtrlData.h"

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
	BOOL m_bDragging{ FALSE };
	UINT_PTR m_nTimerID{ 0 };
	BOOL m_bInvalidate{ FALSE };
	COrgCtrlData::ptr_t m_data;

	float GetZoomRatio() const;
	void SetZoomRatio( float fZoomRatio );

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnTimer( UINT_PTR nIDEvent );
	afx_msg BOOL OnEraseBkgnd( CDC * pDC );

	void SetData( const COrgCtrlData::ptr_t data );
};
