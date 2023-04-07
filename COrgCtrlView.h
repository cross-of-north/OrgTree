#pragma once

class COrgCtrlView {
public:
    typedef enum {
        LeftToRight,
        Tree,
        UpsideDownTree,
    } Mode;
protected:
    float m_fZoomRatio{ 1 };
    CRect m_rcScreenRect;
    COrgCtrlView::Mode m_mode{ COrgCtrlView::Mode::LeftToRight };
    CRect m_rcNormalDataRect;
    CRect m_rcTransposedDataRect;
    CRect ToNormalViewRect( const CRect & rcRect ) const;
    CRect ToTransposedViewRect( const CRect & rcRect, const bool bRotate = false ) const;
public:
    float GetZoomRatio() const { return m_fZoomRatio; }
    void SetZoomRatio( float fZoomRatio, const CPoint & ptCenter = {} );
    const CRect & GetScreenRect() const { return m_rcScreenRect; }
    CRect & GetScreenRect() { return m_rcScreenRect; }
    CRect ToViewRect( const CRect & rcRect ) const;
    void Offset( const CPoint & offset );
    void SetSize( int cx, int cy );
    void SetMode( COrgCtrlView::Mode mode ) { m_mode = mode; }
    COrgCtrlView::Mode GetMode() const { return m_mode; }
    void SetDataRect( const CRect & rcDataRect ) const;
};
