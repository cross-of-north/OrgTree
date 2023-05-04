// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlView.h"

CRect COrgCtrlView::ToNormalViewRect( const CRect & rcRect ) const {
    CRect rcViewRect;
    rcViewRect.left = m_rcScreenRect.left + LONG( float( rcRect.left ) * m_fZoomRatio );
    rcViewRect.top = m_rcScreenRect.top + LONG( float( rcRect.top ) * m_fZoomRatio );
    rcViewRect.right = m_rcScreenRect.left + LONG( float( rcRect.right ) * m_fZoomRatio );
    rcViewRect.bottom = m_rcScreenRect.top + LONG( float( rcRect.bottom ) * m_fZoomRatio );
    return rcViewRect;
}

CRect COrgCtrlView::ToTransposedViewRect( const CRect & rcRect, const bool bRotate ) const {
    CRect rcViewRect;
    rcViewRect.left = m_rcScreenRect.left + LONG( float( rcRect.top ) * m_fZoomRatio );
    rcViewRect.top = m_rcScreenRect.top + LONG( float( rcRect.left ) * m_fZoomRatio );
    rcViewRect.right = m_rcScreenRect.left + LONG( float( rcRect.bottom ) * m_fZoomRatio );
    rcViewRect.bottom = m_rcScreenRect.top + LONG( float( rcRect.right ) * m_fZoomRatio );
    CPoint offset( m_rcNormalDataRect.Width() / 2, -m_rcNormalDataRect.Height() / 2 );
    rcViewRect.OffsetRect( offset );
    if ( bRotate ) {
        auto width = rcViewRect.Width();
        auto height = rcViewRect.Height();
        rcViewRect.left = rcViewRect.left + width / 2 - height / 2;
        rcViewRect.right = rcViewRect.right - width / 2 + height / 2;
        rcViewRect.top = rcViewRect.top + height / 2 - width / 2;
        rcViewRect.bottom = rcViewRect.bottom - height / 2 + width / 2;
    }
    return rcViewRect;
}

CRect COrgCtrlView::ToViewRect( const CRect & rcRect, const int iDepth, const int iOrder, const int iCount ) const {
    CRect rcViewRect = rcRect;
    switch ( m_mode ) {
        case COrgCtrlView::Mode::LeftToRight:
        {
            rcViewRect = ToNormalViewRect( rcRect );
            break;
        }
        case COrgCtrlView::Mode::Tree:
        {
            rcViewRect = ToTransposedViewRect( rcRect, true );
            break;
        }
        case COrgCtrlView::Mode::UpsideDownTree:
        {
            rcViewRect = ToTransposedViewRect( rcRect, true );
            ASSERT( !m_rcTransposedDataRect.IsRectEmpty() );
            CPoint center = m_rcTransposedDataRect.CenterPoint();
            rcViewRect.top += ( center.y - rcViewRect.top ) * 2;
            rcViewRect.bottom += ( center.y - rcViewRect.bottom ) * 2;
            rcViewRect.NormalizeRect();
            break;
        }
        case COrgCtrlView::Mode::Outlook:
        {
            CRect rcLayoutRect;
            rcLayoutRect.top = iCount * rcRect.Height() * 2;
            rcLayoutRect.bottom = rcLayoutRect.top + rcRect.Height();
            rcLayoutRect.left = iDepth * rcRect.Width() * 2;
            rcLayoutRect.right = rcLayoutRect.left + rcRect.Width();
            rcViewRect = ToNormalViewRect( rcLayoutRect );
            break;
        }
        case COrgCtrlView::Mode::Gallery:
        {
          // TODO
        }
        default:
        {
            ASSERT( false );
            break;
        }
    }
    return rcViewRect;
}


void COrgCtrlView::SetZoomRatio( float fZoomRatio, const CPoint & ptCenter ) {

    // Zooming around the specified point (mouse cursor)
    CPoint ptCornerDistance = ptCenter - m_rcScreenRect.TopLeft();
    CPoint ptNewCornerDistance = ptCornerDistance;
    float fRateChange = fZoomRatio / m_fZoomRatio;
    ptNewCornerDistance.x = LONG( float( ptNewCornerDistance.x ) * fRateChange );
    ptNewCornerDistance.y = LONG( float( ptNewCornerDistance.y ) * fRateChange );
    CPoint ptOffset = ptCornerDistance - ptNewCornerDistance;
    m_rcScreenRect.OffsetRect( ptOffset );

    m_fZoomRatio = fZoomRatio;
}

void COrgCtrlView::Offset( const CPoint & offset ) {
    m_rcScreenRect.OffsetRect( offset );
}

void COrgCtrlView::SetSize( int cx, int cy ) {
    m_rcScreenRect.right = m_rcScreenRect.left + cx;
    m_rcScreenRect.bottom = m_rcScreenRect.top + cy;
}

void COrgCtrlView::SetDataRect( const CRect & rcDataRect ) const {
    COrgCtrlView * this_ = const_cast < COrgCtrlView * > ( this );
    this_->m_rcNormalDataRect = ToNormalViewRect( rcDataRect );
    this_->m_rcTransposedDataRect = ToTransposedViewRect( rcDataRect );
}
