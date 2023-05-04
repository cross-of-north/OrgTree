/********************************************************************
* THIS PROGRAM IS THE CONFIDENTIAL AND PROPRIETARY PRODUCT OF
* HIVEWARE INC. ANY UNAUTHORIZED USE, REPRODUCTION,
* OR TRANSFER OF THIS PROGRAM IS STRICTLY PROHIBITED. COPYRIGHT (c)
* 2012-2023 BY HIVEWARE INC. (FULL DISTRIBUTION VIA HIVEWARE OPEN SOURCE
* (READ_ONLY_NOT_COPYABLE) (OR_UNTIL_PROVEN_NOT_COPYABLE_AT_LEAST_COPYCHAINTRACEABLE_IF_COPIED).)  ALL RIGHTS RESERVED.
********************************************************************/
#pragma once

#define FRONTINSTANCEISLOADED_ARGSET bool
#define LAUNCHHIVE_ARGSET CString, CString, int, std::streamsize, UUID
#define NETWORKENDPOINT_SOCKADDRSTORAGE_ARGSET NetworkEndPoint, SOCKADDR_STORAGE, IpAddrHwIfQualityType // RT:230501 RT:200117

//##############################################################################

enum class ConsumerHwMsgKind : size_t // RT:200925: (see DESIGN-1327 Limit Listening Sockets To Known Hw Types)
{
  TEST, // RT:200925: test if this hw msg type was found in the list of hw msg handlers
  ACTUAL // RT:200925: carry out the hw msg task of receiving and parinsg the hw msg
};

//##############################################################################

enum class ConsumerHwMsgState: size_t // RT:200925: (see DESIGN-1327 Limit Listening Sockets To Known Hw Types)
{
  PASSED, // RT:200925: an hw msg type was found in the list of hw msg handlers
  FAILED // RT:200925: no hw msg task of receiving and parinsg the hw msg
};

//##############################################################################

enum class CxNodeAction : size_t
{
  NOT_YET_SET,
  DO_ACTION_ON_ALL_NODES,
  ACTION_ON_THIS_CONTEXT_NODE,
  ACTION_ON_THIS_MIGRATE_NODE,
  BEGIN_HIERARCHICAL_CONTEXT_NODE_DELETE,
  BEGIN_HIERARCHICAL_MIGRATE_NODE_DELETE,
  END
};

using CxNodeActionDescrStrMap = std::map< CxNodeAction, CString >;
extern CxNodeActionDescrStrMap cxNodeActionDescrStrMap;

// (see DESIGN-1254 GetDescrStr)
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( CxNodeAction cxNodeAction );


enum class TheGrammarSubAction : size_t
{
  NOT_YET_SET,
  FRONTEND_INSTANCE_IS_LOADED,
  MAKE_TARGET_WORK_AVAILABLE,
  DISPLAY_FRONTEND_CALLBACK_MSG,
  LAUNCH_OWNEDMIRROR,
  LAUNCH_MYFILES,
  LAUNCH_MYFAMILY,
  SET_LOGGER_FILEPATHNAME_IMPORT_SGML_FILE,
  EXPORT_SGML_FILE,
  BEGIN_INITIAL_OWNED_MIRROR_HWMSG_VOLLEY,
  BEGIN_INITIAL_MYFILES_ANCESTOR_HWMSG_VOLLEY,
  BEGIN_INITIAL_MYFAMILY_ANCESTOR_HWMSG_VOLLEY,
  INVITE_NEW_SUBSCRIBER,
  SIGNUPAUTH_NONCEAESKEY, // RT:190507
  END
};

using TheGrammarSubActionDescrStrMap = std::map< TheGrammarSubAction, CString >;
extern TheGrammarSubActionDescrStrMap theGrammarSubActionDescrStrMap;

// (see DESIGN-1254 GetDescrStr)
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( TheGrammarSubAction theGrammarSubAction );

//##############################################################################

enum class LaunchHiveArgSet
{
  FILEPATHNAME,
  OTHERIPADDRESS,
  OTHERPORTNUMBER,
  AESKEY,
  UUID
};

using LaunchHiveArgSetDescrStrMap = std::map< LaunchHiveArgSet, CString >;
extern LaunchHiveArgSetDescrStrMap launchHiveArgSetDescrStrMap;

// (see DESIGN-1254 GetDescrStr)
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( LaunchHiveArgSet launchHiveArgSet );

//##############################################################################

// These lex states represent the actual type and state of the context node and not the parsing states which tend to reflect the various states during parsing.
enum class LexNodeState
{
  NOT_YET_SET,
  ELEMENT_EDIT,                 // element edit control
  NONTERMINAL_ELEMENT_BUTTON,   // left hand side before colon nonterminal. All other nonterminals are defined from within a production rule.
  PRODUCTION_RULE_MODEL_EDIT,   // production rule union edit control
  PRODUCTION_RULE_MODEL_BUTTON, // right hand side after colon items like nonterminals, terminals and grammar parsing tokens like occurrence indicators and sublist clauses
  SUBLIST_PRODUCTION_RULE,      // a production rule within SGML parentheses
  ATTRIBUTE_DECLARATION_BLOCK,  // TODO
  SEMANTIC_ACTION_BLOCK_BUTTON, // starts with left brace and ends with right brace with code in between
  END
};

using LexNodeStateDescrStrMap = std::map< LexNodeState, CString > ;
extern LexNodeStateDescrStrMap lexNodeStateDescrStrMap;
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( LexNodeState lexNodeState );

//##############################################################################

enum class NodeType
{
  NOT_YET_SET,
  CONTEXT_NODE,
  MIGRATE_NODE,
  END
};

using NodeTypeDescrStrMap = std::map< NodeType, CString >;
extern NodeTypeDescrStrMap nodeTypeDescrStrMap;
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( NodeType nodeType );

//##############################################################################

enum class AuthorizationLevel
{
  NOT_YET_SET = 0,
  SUBSCRIBER = 1, // the subscriber only receives content and context changes from other nodes and doesn't create anything himself
  CONTENT_EDITOR = 2, // the author may not create any nonterminals on this node; only content
  CONTEXT_EDITOR = 4, // the author may create or change the production rule to a depth of 1, 2, 3 or any depth depending on 'depth' variable
  ROOT_CONTEXT_EDITOR = 8, // like the 'start node' item in conventional compiler theory, this is the node that listens for incoming new grammar requests which occur after being accepted as a new subscriber. 
  END
};

using AuthorizationLevelDescrStrMap = std::map< AuthorizationLevel, CString >;
extern AuthorizationLevelDescrStrMap authorizationLevelDescrStrMap;
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( AuthorizationLevel authorizationLevel );

//##############################################################################

// RT:201118: was missing. is needed to compile old code, back in use.
enum class RelationToReferenceItem
{
  NOT_YET_SET = 0,
  ROOT_ITEM,
  CHILD_ITEM,
  SIBLING_ITEM,
  END
};

using RelationToReferenceItemDescrStrMap = std::map< RelationToReferenceItem, CString >;
extern RelationToReferenceItemDescrStrMap relationToReferenceItemDescrStrMap;
extern CString DECLSPEC_SDCDCHIVEWARE GetDescrStr( RelationToReferenceItem relationToReferenceItem );

//##############################################################################
