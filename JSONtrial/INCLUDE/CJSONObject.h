#ifndef _CJSONObject_H_
#define _CJSONObject_H_
#include "../INCLUDE/VJSONMember.h"
#include "../INCLUDE/BJSONNodeCollection.h"

#include "../INCLUDE/BParseControl.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONObject : public JSONObject, public VJSONMember, public BJSONNodeCollection {
	public:
									CJSONObject(JSONAnchor* pobj);
		virtual						~CJSONObject(void);

	public:
		virtual ULONG				Keep(void) { return(VJSONMember::Keep()); }
		virtual ULONG				Discard(void) { return(VJSONMember::Discard()); }

	public:
		virtual JSONNodeType		IsNodeType(void) { return(JSONNodeType_Object); }
		virtual HRESULT				Key(void** ppobj) { return(VJSONMember::Key(ppobj)); }

	public:
		virtual int					NodeSize(void) { return(BJSONNodeCollection::NodeSize()); }
		virtual HRESULT				Node(int index, void** ppvobj) { return(BJSONNodeCollection::Node(index, ppvobj)); }
		virtual void				RemoveNode(LPCSTR key) { BJSONNodeCollection::RemoveNode(key); }

	public:
		virtual HRESULT				CreateNode(JSONNodeType type, LPCSTR key, void** ppobj);
		virtual HRESULT				FindNode(LPCSTR key, void** ppobj);

	public:
		virtual HRESULT				Parse(BParseControl& stm);
};


#endif	// _CJSONObject_H_
