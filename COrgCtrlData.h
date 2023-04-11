#pragma once

#include "IOrgTreeDoc.h"

class COrgCtrlDataItem {
public:
    typedef std::shared_ptr < COrgCtrlDataItem > ptr_t;
    typedef std::vector< ptr_t > array_t;
    static const int INVALID_ORDER_HINT = -1;
protected:
    const COrgCtrlDataItem * m_pParent{ nullptr };
    array_t m_children;
    CRect m_rcRect;
    int m_iOrderHint{ COrgCtrlDataItem::INVALID_ORDER_HINT };
public:
    COrgCtrlDataItem() = default;
    const array_t & GetChildren() const { return m_children; }
    //array_t & GetChildren() { return m_children; }
    const CRect & GetRect() const { return m_rcRect; }
    CRect & GetRect() { return m_rcRect; }
    const COrgCtrlDataItem * GetParent() const { return m_pParent; }
    void SetParent( const COrgCtrlDataItem * pParent ) { m_pParent = pParent; }
    void AddChild( const ptr_t & pChild ) {
        m_children.push_back( pChild );
        pChild->SetParent( this );
    }
    void Clear() {
        m_children.clear();
    }
    const IOrgTreeDoc::node_handle_t GetHandle() const {
        return ( IOrgTreeDoc::node_handle_t )this;
    }
    static COrgCtrlDataItem * FromHandle( const IOrgTreeDoc::node_handle_t hNode ) {
        return ( IOrgTreeDoc::IsValidNode( hNode ) ) ? ( COrgCtrlDataItem * )hNode : NULL;
    }
    int GetOrderHint() const { return m_iOrderHint; }
    void SetOrderHint( const int iOrderHint ) { m_iOrderHint = iOrderHint; }

private:
    COrgCtrlDataItem( const COrgCtrlDataItem & source ) = delete;
    COrgCtrlDataItem & operator =( const COrgCtrlDataItem & source ) = delete;
};

class COrgCtrlData {
public:
    typedef std::shared_ptr < COrgCtrlData > ptr_t;
protected:
    COrgCtrlDataItem m_root;
public:
    const COrgCtrlDataItem & GetRoot() const { return m_root; }
    COrgCtrlDataItem & GetRoot() { return m_root; }
};
