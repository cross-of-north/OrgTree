#pragma once

#include "IOrgTreeDoc.h"
#include "COrgCtrlview.h"

class COrgCtrlPainter {
protected:
    CDC & m_dc;
    const CRect m_rcClient;
    const IOrgTreeDoc & m_document;
    const COrgCtrlView & m_view;
    CRect m_rcDataBorders;
    void MeasureNode( const POrgTreeDocNodeHandle & phNode );
    void PaintNode( const POrgTreeDocNodeHandle & phNode, const int iDepth, const int iOrder, int & iCount );
public:
    COrgCtrlPainter( CDC & dc, const CRect & rcClient, const IOrgTreeDoc & document, const COrgCtrlView & view );
    void Paint( void );
};
