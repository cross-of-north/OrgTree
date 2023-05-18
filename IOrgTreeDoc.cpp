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

bool IOrgTreeDoc::HitTest( const CRect & rect, POrgTreeDocNodeHandle & phHitNode, const bool bScreenCoords, const POrgTreeDocNodeHandle & phStartNode ) const {
	bool bResult = false;
	POrgTreeDocNodeHandle phNode = phStartNode;
	phHitNode.reset();
	if ( ValidateRecursiveNode( phNode ) ) {
		if ( CRect().IntersectRect( bScreenCoords ? GetNodeScreenRect( phNode ) : GetNodeRect( phNode ), rect ) != 0 ) {
			phHitNode = phNode;
			bResult = true;
		} else {
			POrgTreeDocNodeHandle phChildNode;
			while ( GetNextChildNode( phNode, phChildNode ) ) {
				bResult = HitTest( rect, phHitNode, bScreenCoords, phChildNode );
				if ( bResult ) {
					break;
				}
			}
		}
	}
	return bResult;
}

bool IOrgTreeDoc::HitTest( const CPoint & point, POrgTreeDocNodeHandle & phHitNode, const bool bScreenCoords ) const {
	CRect rect( point.x - 1, point.y - 1, point.x + 1, point.y + 1 );
	return HitTest( rect, phHitNode );
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
	phFocusedNode.reset();
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

void IOrgTreeDoc::SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const wchar_t * strValue ) {
	SetNodeProperty( phNode, strName, CString( strValue ) );
}