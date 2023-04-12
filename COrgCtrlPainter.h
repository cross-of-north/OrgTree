#pragma once

#include "IOrgTreeDoc.h"
#include "COrgCtrlview.h"

class COrgCtrlPainter {
protected:
    CDC & m_dc;
    const CRect m_rcClient;
    const IOrgTreeDoc & m_data;
    const COrgCtrlView & m_view;
    CRect m_rcDataBorders;
    void MeasureNode( const IOrgTreeDocNodeHandle & hNode );
    void PaintNode( const IOrgTreeDocNodeHandle & hNode, const int iDepth, const int iOrder, int & iCount );
public:
    COrgCtrlPainter( CDC & dc, const CRect & rcClient, const IOrgTreeDoc & data, const COrgCtrlView & view );
    void Paint( void );
};
