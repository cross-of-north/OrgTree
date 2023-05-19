#pragma once

#include "IOrgTreeDoc.h"

class COrgCtrlDataItem: public std::enable_shared_from_this < COrgCtrlDataItem > {
public:
    typedef std::shared_ptr < COrgCtrlDataItem > ptr_t;
    typedef std::vector< ptr_t > array_t;
    typedef std::map < std::wstring, std::wstring > properties_t;
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
    const properties_t & GetProperties() { return m_properties; }
    void AddChild( const ptr_t & pChild );
    void RemoveChild( ptr_t & pChild );
    void Delete();
    void Clear();

    bool GetString( const wchar_t * name, std::wstring & value ) const;
    bool GetInt( const wchar_t * name, __int64 & value ) const;
    void SetString( const wchar_t * name, const std::wstring & value );
    void SetInt( const wchar_t * name, const __int64 value );

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
