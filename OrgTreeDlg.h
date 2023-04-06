#pragma once
#include "afxdialogex.h"


// OrgTreeDlg dialog

class OrgTreeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OrgTreeDlg)

public:
	OrgTreeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~OrgTreeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TREEVIEW_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
