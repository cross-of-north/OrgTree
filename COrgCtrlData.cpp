// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlData.h"

COrgCtrlDataItem::~COrgCtrlDataItem() {
}

void COrgCtrlDataItem::ResetOrderHints() {
    for ( int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->SetOrderHint( COrgCtrlDataItem::INVALID_ORDER_HINT );
    }
}

void COrgCtrlDataItem::AddChild( const ptr_t & pChild ) {
    m_children.push_back( pChild );
    pChild->SetParent( shared_from_this() );
    ResetOrderHints();
}

void COrgCtrlDataItem::Clear() {
    ResetOrderHints();
    for ( auto it: m_children ) {
        it->m_pParent.reset();
        it->Delete();
    }
    m_children.clear();
}

void COrgCtrlDataItem::RemoveChild( ptr_t & pChild ) {
    auto it = std::find( m_children.begin(), m_children.end(), pChild );
    if ( it != m_children.end() ) {
        m_children.erase( it );
    }
}

void COrgCtrlDataItem::Delete() {
    if ( m_pParent ) {
        m_pParent->RemoveChild( shared_from_this() );
    }
    m_iOrderHint = COrgCtrlDataItem::INVALID_ORDER_HINT;
    m_rcRect.SetRectEmpty();
    m_rcScreenRect.SetRectEmpty();
    m_bFocus = false;
    m_pParent = nullptr;
    Clear();
}