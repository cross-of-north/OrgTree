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

void IOrgTreeDoc::GetAllNodes( COrgTreeDocNodeHandleList & nodes, const POrgTreeDocNodeHandle & phStartNode ) const {
	POrgTreeDocNodeHandle phNode = phStartNode;
	if ( !phStartNode ) {
		nodes.clear();
	}
	if ( ValidateRecursiveNode( phNode ) ) {
		nodes.push_back( phNode );
		POrgTreeDocNodeHandle phChildNode;
		while ( GetNextChildNode( phNode, phChildNode ) ) {
			GetAllNodes( nodes, phChildNode );
		}
	}
}

void IOrgTreeDoc::GetChildrenByProperty( const POrgTreeDocNodeHandle & phParent, const wchar_t * strName, const CString & strValue, COrgTreeDocNodeHandleList & children ) const {
	children.clear();
	POrgTreeDocNodeHandle phChild;
	while ( GetNextChildNode( phParent, phChild ) ) {
		CString value;
		if ( GetNodeProperty( phChild, strName, value ) ) {
			if ( value == strValue ) {
				children.push_back( phChild );
			}
		}
	}
}

void IOrgTreeDoc::GetNodesByPath( const CStringArray & path, COrgTreeDocNodeHandleList & nodes, const POrgTreeDocNodeHandle & phStartNode, const int iListIndex ) const {
	int list_index = iListIndex;
	if ( list_index < path.GetCount() ) {
		// there are still levels to search
		bool bSkipNonMatchingLevels = false;
		POrgTreeDocNodeHandle phNode = phStartNode;
		if ( path.GetAt( 0 ).IsEmpty() && list_index < 2 ) {
			// search path starts with a ":" (empty string)
			// this means that the search can start at any node
			bSkipNonMatchingLevels = true;
			if ( list_index == 0 ) {
				list_index = 1;
			}
		}
		if ( !phStartNode ) {
			nodes.clear();
		}
		if ( ValidateRecursiveNode( phNode ) ) {
			CMapStringToString properties;
			GetNodeProperties( phNode, properties );
			std::map < CString, bool > matched_properties;
			bool bMatch = true;
			bool bDescend = false;
			while ( bMatch && list_index < path.GetCount() ) {
				// searching for matching value in the node properties for every token in the search path
				CString value_to_search = path.GetAt( list_index );
				if ( value_to_search.IsEmpty() ) {
					// "::" (empty string) in a search path means that the search should descend to child nodes
					bMatch = false;
					bDescend = true;
					list_index++;
				} else {
					bMatch = false;
					// looking every property value in the node for a match
					// do not match property values twice
					for ( POSITION pos = properties.GetStartPosition(); pos != NULL; ) {
						CString name, value;
						properties.GetNextAssoc( pos, name, value );
						if (
							matched_properties.find( name ) == matched_properties.end()
							&&
							value == value_to_search
						) {
							// found a matching property value, go to next search path token
							bMatch = true;
							matched_properties[ name ] = true;
							list_index++;
							break;
						}
					}
				}
			}
			bool bPartialMatch = ( matched_properties.size() > 0 ); // some properties matched
			if ( bPartialMatch && bMatch ) {
				// all properties matched, this is a terminal match node
				nodes.push_back( phNode );
				bDescend = false;
			} else {
				// not a terminal match node
				if ( !bDescend && bSkipNonMatchingLevels ) {
					// no match and descent here, but we are skipping non-matching levels
					bDescend = true;
					// start anew with the next level
					list_index = iListIndex;
				}
				if ( bDescend ) {
					// descending to children
					POrgTreeDocNodeHandle phChildNode;
					while ( GetNextChildNode( phNode, phChildNode ) ) {
						GetNodesByPath( path, nodes, phChildNode, list_index );
					}
				}
			}
		}
	}
}

void IOrgTreeDoc::GetNodesByPath( const CString & path, COrgTreeDocNodeHandleList & nodes ) const {
	CStringArray arPath;
	CString token;
	int curPos = 0;
	while ( AfxExtractSubString( token, path, curPos, L':' ) ) {
		arPath.Add( token );
		curPos++;
	}
	GetNodesByPath( arPath, nodes );
}
