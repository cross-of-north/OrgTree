#pragma once

class IOrgTreeDoc {

public:

    typedef ULONG64 node_handle_t;
    static const node_handle_t INVALID_NODE_HANDLE = 0;

    static bool IsValidNode( const node_handle_t node ) {
        return node != INVALID_NODE_HANDLE;
    }

    const node_handle_t GetFirstChildNode( const node_handle_t hParent ) const {
        return GetNextChildNode( hParent, INVALID_NODE_HANDLE );
    }

    virtual const node_handle_t GetRootNode() const = 0;
    virtual const node_handle_t GetNextChildNode( const node_handle_t hParent, const node_handle_t hCurrentChild ) const = 0;
    virtual const CRect GetNodeRect( const node_handle_t hNode ) const = 0;

};