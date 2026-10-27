#ifndef _CJSONArray_H_
#define _CJSONArray_H_
#include "../INCLUDE/VJSONMember.h"
#include "../INCLUDE/BJSONNodeCollection.h"

#include "../INCLUDE/BParseControl.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONArray : public JSONArray, public VJSONMember, public BJSONNodeCollection {
	public:
									CJSONArray(JSONAnchor* pobj);
		virtual						~CJSONArray(void);

	public:
		virtual ULONG				Keep(void) { return(VJSONMember::Keep()); }
		virtual ULONG				Discard(void) { return(VJSONMember::Discard()); }

	public:
		virtual JSONNodeType		IsNodeType(void) { return(JSONNodeType_Array); }
		virtual HRESULT				Key(void** ppobj) { return(VJSONMember::Key(ppobj)); }

	public:
		virtual int					NodeSize(void) { return(BJSONNodeCollection::NodeSize()); }
		virtual HRESULT				Node(int index, void** ppvobj) { return(BJSONNodeCollection::Node(index, ppvobj)); }
		virtual void				RemoveNode(int index) { BJSONNodeCollection::RemoveNode(index); }

	public:
		virtual HRESULT				CreateNode(JSONNodeType type, void** ppobj);

	public:
		virtual HRESULT				Parse(BParseControl& stm);
};


#endif	// _CJSONArray_H_
