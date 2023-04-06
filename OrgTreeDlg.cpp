// OrgTreeDlg.cpp : implementation file
//

#include "pch.h"
#include "resource.h"
#include "afxdialogex.h"
#include "OrgTreeDlg.h"


// OrgTreeDlg dialog

IMPLEMENT_DYNAMIC(OrgTreeDlg, CDialogEx)

OrgTreeDlg::OrgTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREEVIEW_FORM, pParent)
{

}

OrgTreeDlg::~OrgTreeDlg()
{
}

void OrgTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OrgTreeDlg, CDialogEx)
END_MESSAGE_MAP()


// OrgTreeDlg message handlers
