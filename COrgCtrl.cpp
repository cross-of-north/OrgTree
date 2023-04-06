// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrgCtrl

COrgCtrl::COrgCtrl()
{
  //Register My window class
  RegisterWndClass();

  flag=FALSE;//Sets the drawing flag off
}

COrgCtrl::~COrgCtrl()
{
}


BEGIN_MESSAGE_MAP(COrgCtrl, CWnd)
  //{{AFX_MSG_MAP(COrgCtrl)
  ON_WM_CREATE()
  ON_WM_LBUTTONDOWN()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COrgCtrl message handlers

BOOL COrgCtrl::RegisterWndClass()
{
  WNDCLASS windowclass;
  HINSTANCE hInst = AfxGetInstanceHandle();

  //Check weather the class is registerd already
  if (!(::GetClassInfo(hInst, ORGCTRLWNDCLASS, &windowclass)))
  {
    //If not then we have to register the new class
    windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;
    windowclass.lpfnWndProc = ::DefWindowProc;
    windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
    windowclass.hInstance = hInst;
    windowclass.hIcon = NULL;
    windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
    windowclass.lpszMenuName = NULL;
    windowclass.lpszClassName = ORGCTRLWNDCLASS;


    if (!AfxRegisterClass(&windowclass))
    {
      AfxThrowResourceException();
      return FALSE;
    }
  }

  return TRUE;

}

int COrgCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  // TODO: Add your specialized creation code here

  
  return 0;
}


void COrgCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default

  if(flag==FALSE)
  {
    oldpt=point;
    flag=TRUE;
  }
  
  //CWnd::OnLButtonDown(nFlags, point);
}

void COrgCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  
  if(flag==TRUE)
  {
  
    CDC *d=GetDC();

    d->MoveTo(oldpt);
    d->LineTo(point);
  

    oldpt=point;
  
    ReleaseDC(d);
  }
  
  //CWnd::OnMouseMove(nFlags, point);
}

void COrgCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  
  flag=FALSE;

  //CWnd::OnLButtonUp(nFlags, point);
}

BOOL COrgCtrl::Create( DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID ) {
    return CWnd::Create( NULL, _T(""), dwStyle | WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        ES_AUTOHSCROLL | WS_BORDER, rect, pParentWnd, nID );
}