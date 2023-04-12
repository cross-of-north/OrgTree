#pragma once

class IOrgTreeDocNodeHandle {

    friend class IOrgTreeDoc;

private:

    IOrgTreeDocNodeHandle( const IOrgTreeDocNodeHandle & ) = delete;
    IOrgTreeDocNodeHandle & operator=( const IOrgTreeDocNodeHandle & ) = delete;

protected:

    ULONG64 m_handle{ INVALID_NODE_HANDLE };

    static const ULONG64 INVALID_NODE_HANDLE = 0;

public:

    IOrgTreeDocNodeHandle() = default;
    IOrgTreeDocNodeHandle( ULONG64 handle ) : m_handle( handle ) {}

    bool IsValid() const {
        return m_handle != INVALID_NODE_HANDLE;
    }

    void SetHandle( ULONG64 handle ) {
        m_handle = handle;
    }
    ULONG64 GetHandle() const {
        return m_handle;
    }

};

class IOrgTreeDoc {

public:

    virtual bool GetRootNode( IOrgTreeDocNodeHandle & hNode ) const = 0;
    virtual bool GetNextChildNode( const IOrgTreeDocNodeHandle & hParent, IOrgTreeDocNodeHandle & hChild ) const = 0;
    virtual const CRect GetNodeRect( const IOrgTreeDocNodeHandle & hNode ) const = 0;

};