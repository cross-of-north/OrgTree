// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrl.h"
#include "COrgCtrlPainter.h"

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

  m_bDragging=FALSE;//Sets the drawing m_bDragging off
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
    ON_WM_MOUSEWHEEL()
    ON_WM_SIZE()
    ON_WM_TIMER()
    ON_WM_ERASEBKGND()
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
  return 0;
}

void COrgCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  m_bDragging=FALSE;
  //CWnd::OnLButtonUp(nFlags, point);
}

void COrgCtrl::OnPaint() {

    CRect rcClient;
    GetClientRect( rcClient );

    CPaintDC paintDC( this );

    // double-buffered painting
    CDC dc;
    dc.CreateCompatibleDC( &paintDC );
    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap( &paintDC, rcClient.Width(), rcClient.Height() );
    HGDIOBJ oldBitmap = dc.SelectObject( bitmap );

    // do painting in memory DC
    HGDIOBJ oldBrush = dc.SelectObject( GetStockObject( DC_BRUSH ) );
    HGDIOBJ oldPen = dc.SelectObject( GetStockObject( DC_PEN ) );
    dc.SetDCBrushColor( RGB( 255, 255, 255 ) );
    dc.SetDCPenColor( RGB( 255, 255, 255 ) );
    dc.FillSolidRect( rcClient, RGB( 255, 255, 255 ) );
    dc.SetDCPenColor( RGB( 0, 0, 0 ) );

    if ( m_data != NULL ) {
        COrgCtrlPainter painter( dc, rcClient, *m_data, m_view );
        painter.Paint();
    }

    // flush to screen
    paintDC.BitBlt( 0, 0, rcClient.Width(), rcClient.Height(), &dc, 0, 0, SRCCOPY );
    
    // restore DC
    dc.SelectObject( oldPen );
    dc.SelectObject( oldBrush );
    dc.SelectObject( oldBitmap );
}

BOOL COrgCtrl::Create( DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID ) {
    //SetZoomRatio( 4.7f );
    //SetZoomRatio( .3f );
    return CWnd::Create( NULL, _T( "" ), dwStyle | WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        ES_AUTOHSCROLL | WS_BORDER, rect, pParentWnd, nID );
}

float COrgCtrl::GetZoomRatio() const {
    return m_view.GetZoomRatio();
}

void COrgCtrl::SetZoomRatio( float fZoomRatio, const CPoint & ptCenter ) {
    m_view.SetZoomRatio( fZoomRatio, ptCenter );
    Invalidate();
}

BOOL COrgCtrl::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt ) {
    
    if ( ::GetKeyState( VK_CONTROL ) < 0 ) {
        
        float fOldZoomRatio = GetZoomRatio();
        float fNewZoomRatio{ 0 };
        if ( zDelta > 0 ) {
            fNewZoomRatio = fOldZoomRatio * 1.1f;
        } else {
            fNewZoomRatio = fOldZoomRatio * 0.9f;
        }
        // Adjust the view rect to keep the mouse cursor at the same position.
        CPoint ptCursor;
        ::GetCursorPos( &ptCursor );
        ScreenToClient( &ptCursor );
        SetZoomRatio( fNewZoomRatio, ptCursor );
    }

    return CWnd::OnMouseWheel( nFlags, zDelta, pt );
}

void COrgCtrl::OnLButtonDown( UINT nFlags, CPoint point ) {
    if ( m_bDragging == FALSE ) {
        m_ptPrevDragPoint = point;
        m_bDragging = TRUE;
    }
    CWnd::OnLButtonDown(nFlags, point);
}

void COrgCtrl::OnMouseMove( UINT nFlags, CPoint point ) {
    if ( m_bDragging == TRUE ) {
        CPoint delta = point - m_ptPrevDragPoint;
        m_view.Offset( delta );
        m_ptPrevDragPoint = point;
        m_bInvalidate = TRUE;
        m_nTimerID = ::SetTimer( GetSafeHwnd(), m_nTimerID, 10, NULL );
    }
    CWnd::OnMouseMove(nFlags, point);
}

void COrgCtrl::OnSize( UINT nType, int cx, int cy ) {
    CWnd::OnSize( nType, cx, cy );
    CRect rcClient;
    GetClientRect( rcClient );
    m_view.SetSize( rcClient.Width(), rcClient.Height() );
}

void COrgCtrl::OnTimer( UINT_PTR nIDEvent ) {
    if ( m_nTimerID != 0 ) {
        ::KillTimer( GetSafeHwnd(), m_nTimerID );
        m_nTimerID = 0;
    }
    if ( m_bInvalidate ) {
        Invalidate();
        m_bInvalidate = FALSE;
    }
    CWnd::OnTimer( nIDEvent );
}

BOOL COrgCtrl::OnEraseBkgnd( CDC * pDC ) {
    // avoid flickering
    return TRUE;
}

void COrgCtrl::SetData( const IOrgTreeDoc * data ) {
    m_data = data;
}
