#pragma once

class IOrgTreeDocNodeHandle {
private:
    IOrgTreeDocNodeHandle( const IOrgTreeDocNodeHandle & ) = delete;
    IOrgTreeDocNodeHandle & operator=( const IOrgTreeDocNodeHandle & ) = delete;
protected:
    IOrgTreeDocNodeHandle() = default;
    virtual ~IOrgTreeDocNodeHandle() = default;
};

typedef std::shared_ptr < IOrgTreeDocNodeHandle > POrgTreeDocNodeHandle;
typedef std::vector < POrgTreeDocNodeHandle > COrgTreeDocNodeHandleList;

class IOrgTreeDoc {

protected:

    bool ValidateRecursiveNode( POrgTreeDocNodeHandle & phNode ) const;

public:

    virtual bool GetRootNode( POrgTreeDocNodeHandle & phNode ) const = 0;
    virtual bool GetNextChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phChild ) const = 0;
    virtual const CRect GetNodeRect( const POrgTreeDocNodeHandle & phNode ) const = 0;
    virtual const CRect GetNodeScreenRect( const POrgTreeDocNodeHandle & phNode ) const = 0;
    virtual void SetNodeRect( POrgTreeDocNodeHandle & phNode, const CRect & rect ) = 0;
    virtual void SetNodeScreenRect( const POrgTreeDocNodeHandle & phNode, const CRect & rect ) const = 0;
    virtual void SetNodeFocus( const POrgTreeDocNodeHandle & phNode, const bool bFocus ) const = 0;
    virtual bool GetNodeFocus( const POrgTreeDocNodeHandle & phNode ) const = 0;
    virtual bool GetLastChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phChild ) const = 0;
    virtual bool GetParentNode( const POrgTreeDocNodeHandle & phNode, POrgTreeDocNodeHandle & phParent ) const = 0;
    virtual void DeleteNode( POrgTreeDocNodeHandle & phNode ) = 0;
    virtual void SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const CString & strValue ) = 0;
    virtual bool GetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, CString & strValue ) const = 0;
    virtual void SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const __int64 iValue ) = 0;
    virtual bool GetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, __int64 & iValue ) const = 0;

    // traits
    bool HitTest( const CPoint & point, POrgTreeDocNodeHandle & phHitNode, const bool bScreenCoords = true ) const;
    bool HitTest( const CRect & rect, POrgTreeDocNodeHandle & phHitNode, const bool bScreenCoords = true, const POrgTreeDocNodeHandle & phStartNode = NULL ) const;
    bool GetFocusedNode( POrgTreeDocNodeHandle & phFocusedNode, const POrgTreeDocNodeHandle & phStartNode = NULL ) const;
    void ClearFocus( const POrgTreeDocNodeHandle & phNode = NULL );
    void SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const wchar_t * strValue );
    void GetAllNodes( COrgTreeDocNodeHandleList & nodes, const POrgTreeDocNodeHandle & phStartNode = NULL ) const;
    void GetChildrenByProperty( const POrgTreeDocNodeHandle & phParent, const wchar_t * strName, const CString & strValue, COrgTreeDocNodeHandleList & children ) const;

};
