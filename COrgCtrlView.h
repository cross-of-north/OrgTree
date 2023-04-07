#pragma once

class COrgCtrlView {
protected:
    float m_fZoomRatio{ 1 };
    CRect m_rcScreenRect;
public:
    float GetZoomRatio() const { return m_fZoomRatio; }
    void SetZoomRatio( float fZoomRatio, const CPoint & ptCenter = {} );
    const CRect & GetScreenRect() const { return m_rcScreenRect; }
    CRect & GetScreenRect() { return m_rcScreenRect; }
    CRect ToViewRect( const CRect & rcRect ) const;
    void Offset( const CPoint & offset );
    void SetSize( int cx, int cy );
};
