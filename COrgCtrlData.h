#pragma once

class COrgCtrlDataItem {
public:
    typedef std::shared_ptr < COrgCtrlDataItem > ptr_t;
    typedef std::vector< ptr_t > array_t;
protected:
    const COrgCtrlDataItem * m_pParent{ nullptr };
    array_t m_children;
    CRect m_rcRect;
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
