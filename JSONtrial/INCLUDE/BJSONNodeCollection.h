#ifndef _BJSONNodeCollection_H_
#define _BJSONNodeCollection_H_

#include "../INCLUDE/BArray.h"
#include "../INCLUDE/VJSONMember.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class BJSONNodeCollection {
	protected:
		BArray<JSONValue*>			m_node;

	public:
									BJSONNodeCollection(void);
		virtual						~BJSONNodeCollection(void);

	public:
		virtual int					NodeSize(void) { return(m_node.Size()); }

	public:
		virtual int					FindNode(LPCSTR key);
		virtual HRESULT				FindNode(LPCSTR key, void** ppvobj);
		virtual HRESULT				AppendNode(JSONValue* pxml);
		virtual void				RemoveNode(int index);
		virtual void				RemoveNode(LPCSTR key);
		virtual void				EmptyNode(void);
		virtual HRESULT				Node(int index, void** ppvobj);

	public:
		static HRESULT				Create(JSONAnchor* proot, JSONNodeType type, void** ppobj, VJSONMember** const ppmem);
		static HRESULT				Parse(JSONAnchor* proot, BParseControl& stm, void** ppobj, VJSONMember** const ppmem);

	public:
		virtual void				Uninitialize(void);
};


#endif	// _BJSONNodeCollection_H_
