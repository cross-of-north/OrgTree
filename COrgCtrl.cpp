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
    ON_WM_PAINT()
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

class COrgCtrlView {
protected:
    float m_fZoomRatio{ 1 };
    CRect m_rcScreenRect;
public:
    float GetZoomRatio() const { return m_fZoomRatio; }
    const CRect & GetScreenRect() const { return m_rcScreenRect; }
};

class COrgCtrlDataItem;

class COrgCtrlDataItem {
public:
    typedef std::shared_ptr < COrgCtrlDataItem > ptr_t;
    typedef std::vector< ptr_t > array_t;
protected:
    array_t m_children;
    CRect m_rcRect;
public:
    COrgCtrlDataItem() = default;
    /*
    COrgCtrlDataItem( const COrgCtrlDataItem & source )
        : m_children( source.m_children )
    {
    }
    COrgCtrlDataItem & operator =( const COrgCtrlDataItem & source ) {
        m_children = source.m_children;
        return *this;
    }
    */
    const array_t & GetChildren() const { return m_children; }
    array_t & GetChildren() { return m_children; }
    const CRect & GetRect() const { return m_rcRect; }
    CRect & GetRect() { return m_rcRect; }
private:
    COrgCtrlDataItem( const COrgCtrlDataItem & source ) = delete;
    COrgCtrlDataItem & operator =( const COrgCtrlDataItem & source ) = delete;
};

COrgCtrlDataItem g_data{};

void paint_node( CPaintDC & dc, const COrgCtrlDataItem::ptr_t & node ) {
    const CRect & node_rect = node->GetRect();
    ASSERT( node_rect.Height() > 0 && node_rect.Width() > 0);
    for ( const auto & child : node->GetChildren() ) {
        const CRect & child_rect = child->GetRect();
        dc.MoveTo( node_rect.left + node_rect.Width() / 2, node_rect.top + node_rect.Height() / 2 );
        dc.LineTo( child_rect.left + child_rect.Width() / 2, child_rect.top + child_rect.Height() / 2 );
        paint_node( dc, child );
    }
    dc.Rectangle( node->GetRect() );
}

void COrgCtrl::OnPaint() {
    CPaintDC dc( this );
    auto it = g_data.GetChildren().begin();
    if ( it != g_data.GetChildren().end() ) {
        paint_node( dc, *it );
    }
}

BOOL COrgCtrl::Create( DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID ) {
    COrgCtrlDataItem::ptr_t pRoot = std::make_shared< COrgCtrlDataItem >();
    pRoot->GetRect() = { 50, 50, 70, 60 };
    COrgCtrlDataItem::ptr_t node1 = std::make_shared< COrgCtrlDataItem >();
    node1->GetRect() = { 80, 20, 100, 30 };
    COrgCtrlDataItem::ptr_t node2 = std::make_shared< COrgCtrlDataItem >();
    node2->GetRect() = { 80, 40, 100, 50 };
    COrgCtrlDataItem::ptr_t node3 = std::make_shared< COrgCtrlDataItem >();
    node3->GetRect() = { 80, 60, 100, 70 };
    g_data.GetChildren().push_back( pRoot );
    pRoot->GetChildren().push_back( node1 );
    pRoot->GetChildren().push_back( node2 );
    pRoot->GetChildren().push_back( node3 );
    return CWnd::Create( NULL, _T( "" ), dwStyle | WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        ES_AUTOHSCROLL | WS_BORDER, rect, pParentWnd, nID );
}