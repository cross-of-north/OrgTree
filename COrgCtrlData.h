#pragma once

#include "IOrgTreeDoc.h"

class COrgCtrlDataItem: public std::enable_shared_from_this < COrgCtrlDataItem > {
public:
    typedef std::shared_ptr < COrgCtrlDataItem > ptr_t;
    typedef std::vector< ptr_t > array_t;
    typedef std::map < std::string, std::string > properties_t;
protected:
    COrgCtrlDataItem * m_pParent{ nullptr };
    array_t m_children;
    properties_t m_properties;
    void ResetProperties();
public:
    COrgCtrlDataItem() = default;
    ~COrgCtrlDataItem();
    const array_t & GetChildren() const { return m_children; }
    const COrgCtrlDataItem * GetParent() const { return m_pParent; }
    COrgCtrlDataItem * GetParent() { return m_pParent; }
    void SetParent( COrgCtrlDataItem * pParent ) { m_pParent = pParent; }
    void AddChild( const ptr_t & pChild );
    void RemoveChild( ptr_t & pChild );
    void Delete();
    void Clear();

    bool GetString( const char * name, std::string & value ) const;
    bool GetInt( const char * name, int & value ) const;
    void SetString( const char * name, const std::string & value );
    void SetInt( const char * name, const int value );

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
