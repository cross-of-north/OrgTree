// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlData.h"

void COrgCtrlDataItem::ResetOrderHints() {
    for ( int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->SetOrderHint( COrgCtrlDataItem::INVALID_ORDER_HINT );
    }
}

void COrgCtrlDataItem::AddChild( const ptr_t & pChild ) {
    m_children.push_back( pChild );
    pChild->SetParent( this );
    ResetOrderHints();
}

void COrgCtrlDataItem::Clear() {
    ResetOrderHints();
    m_children.clear();
}

void COrgCtrlDataItem::RemoveChild( ptr_t & pChild ) {
    ?????????????????????
    m_children.erase( m_children, *pChild );
}

void COrgCtrlDataItem::Delete() {
    ???????????????????????
}