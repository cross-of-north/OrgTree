#pragma once

#include "COrgCtrlData.h"
#include "COrgCtrlview.h"

class COrgCtrlPainter {
protected:
    CDC & m_dc;
    const CRect m_rcClient;
    const COrgCtrlData & m_data;
    const COrgCtrlView & m_view;
    CRect m_rcDataBorders;
    void MeasureNode( const COrgCtrlDataItem::ptr_t & node );
    void PaintNode( const COrgCtrlDataItem::ptr_t & node, const int iDepth, const int iOrder, int & iCount );
public:
    COrgCtrlPainter( CDC & dc, const CRect & rcClient, const COrgCtrlData & data, const COrgCtrlView & view );
    void Paint( void );
};
