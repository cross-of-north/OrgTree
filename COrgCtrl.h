#pragma once

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
	CDC cDC;
	BOOL RegisterWndClass();
	CPoint oldpt;
	BOOL flag;
};
