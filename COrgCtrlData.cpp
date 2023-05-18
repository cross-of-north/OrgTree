// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlData.h"

COrgCtrlDataItem::~COrgCtrlDataItem() {
}

void COrgCtrlDataItem::ResetProperties() {
    m_properties.clear();
}

void COrgCtrlDataItem::AddChild( const ptr_t & pChild ) {
    m_children.push_back( pChild );
    pChild->SetParent( this );
}

void COrgCtrlDataItem::Clear() {
    ResetProperties();
    for ( auto it: m_children ) {
        it->SetParent( nullptr );
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
    auto locked_this = shared_from_this();
    if ( m_pParent ) {
        m_pParent->RemoveChild( locked_this );
    }
    ResetProperties();
    m_pParent = nullptr;
    Clear();
}

bool COrgCtrlDataItem::GetString( const wchar_t * name, std::wstring & value ) const {
    auto it = m_properties.find( name );
    bool bResult = !( it == m_properties.end() );
    if ( bResult ) {
        value = it->second;
    } else {
        value.clear();
    }
    return bResult;
}

bool COrgCtrlDataItem::GetInt( const wchar_t * name, __int64 & value ) const {
    std::wstring s;
    bool bResult = GetString( name, s );
    if ( bResult ) {
        value = std::stoi( s );
    } else {
        value = 0;
    }
    return bResult;
}

void COrgCtrlDataItem::SetString( const wchar_t * name, const std::wstring & value ) {
    m_properties[ name ] = value;
}

void COrgCtrlDataItem::SetInt( const wchar_t * name, const __int64 value ) {
    SetString( name, std::to_wstring( value ) );
}
