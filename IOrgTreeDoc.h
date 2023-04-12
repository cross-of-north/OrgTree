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

class IOrgTreeDoc {

public:

    virtual bool GetRootNode( POrgTreeDocNodeHandle & phNode ) const = 0;
    virtual bool GetNextChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phChild ) const = 0;
    virtual const CRect GetNodeRect( const POrgTreeDocNodeHandle & phNode ) const = 0;

};