#pragma once

#include "IOrgTreeDoc.h"

class COrgCtrlDataItem: public std::enable_shared_from_this < COrgCtrlDataItem > {
public:
    typedef std::shared_ptr < COrgCtrlDataItem > ptr_t;
    typedef std::vector< ptr_t > array_t;
    static const int INVALID_ORDER_HINT = -1;
protected:
    COrgCtrlDataItem * m_pParent{ nullptr };
    array_t m_children;
    CRect m_rcRect;
    CRect m_rcScreenRect;
    bool m_bFocus{ false };
    int m_iOrderHint{ COrgCtrlDataItem::INVALID_ORDER_HINT };
    void ResetOrderHints();
public:
    COrgCtrlDataItem() = default;
    ~COrgCtrlDataItem();
    const array_t & GetChildren() const { return m_children; }
    //array_t & GetChildren() { return m_children; }
    const CRect & GetRect() const { return m_rcRect; }
    CRect & GetRect() { return m_rcRect; }
    const CRect & GetScreenRect() const { return m_rcScreenRect; }
    CRect & GetScreenRect() { return m_rcScreenRect; }
    bool GetFocus() const { return m_bFocus; }
    void SetFocus( const bool bFocus ) { m_bFocus = bFocus; }
    const COrgCtrlDataItem * GetParent() const { return m_pParent; }
    COrgCtrlDataItem * GetParent() { return m_pParent; }
    void SetParent( COrgCtrlDataItem * pParent ) { m_pParent = pParent; }
    void AddChild( const ptr_t & pChild );
    void RemoveChild( ptr_t & pChild );
    void Delete();
    void Clear();
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
