#include "pch.h"

#include "IOrgTreeDoc.h"

bool IOrgTreeDoc::ValidateRecursiveNode( POrgTreeDocNodeHandle & phNode ) const {
	if ( !phNode ) {
		POrgTreeDocNodeHandle phRootNode;
		if ( GetRootNode( phRootNode ) ) {
			GetNextChildNode( phRootNode, phNode );
		}
	}
	return !!phNode;
}

bool IOrgTreeDoc::HitTest( const CPoint & point, POrgTreeDocNodeHandle & phHitNode, const POrgTreeDocNodeHandle & phStartNode ) const {
	bool bResult = false;
	POrgTreeDocNodeHandle phNode = phStartNode;
	if ( ValidateRecursiveNode( phNode ) ) {
		if ( GetNodeScreenRect( phNode ).PtInRect( point ) ) {
			phHitNode = phNode;
			bResult = true;
		} else {
			POrgTreeDocNodeHandle phChildNode;
			while ( GetNextChildNode( phNode, phChildNode ) ) {
				bResult = HitTest( point, phHitNode, phChildNode );
				if ( bResult ) {
					break;
				}
			}
		}
	}
	return bResult;
}

void IOrgTreeDoc::ClearFocus( const POrgTreeDocNodeHandle & phNode_ ) {
	POrgTreeDocNodeHandle phNode = phNode_;
	if ( ValidateRecursiveNode( phNode ) ) {
		SetNodeFocus( phNode, false );
		POrgTreeDocNodeHandle phChildNode;
		while ( GetNextChildNode( phNode, phChildNode ) ) {
			ClearFocus( phChildNode );
		}
	}
}

bool IOrgTreeDoc::GetFocusedNode( POrgTreeDocNodeHandle & phFocusedNode, const POrgTreeDocNodeHandle & phStartNode ) const {
	bool bResult = false;
	POrgTreeDocNodeHandle phNode = phStartNode;
	if ( ValidateRecursiveNode( phNode ) ) {
		if ( GetNodeFocus( phNode ) ) {
			phFocusedNode = phNode;
			bResult = true;
		} else {
			POrgTreeDocNodeHandle phChildNode;
			while ( GetNextChildNode( phNode, phChildNode ) ) {
				bResult = GetFocusedNode( phFocusedNode, phChildNode );
				if ( bResult ) {
					break;
				}
			}
		}
	}
	return bResult;
}

