#ifndef _CJSONBool_H_
#define _CJSONBool_H_
#include "../INCLUDE/VJSONMember.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONBool : public JSONBool, public VJSONMember {
	protected:
		bool						m_val;

	public:
									CJSONBool(JSONAnchor* pobj);
		virtual						~CJSONBool(void);

	public:
		virtual ULONG				Keep(void) { return(VJSONMember::Keep()); }
		virtual ULONG				Discard(void) { return(VJSONMember::Discard()); }

	public:
		virtual JSONNodeType		IsNodeType(void) { return(JSONNodeType_Bool); }
		virtual HRESULT				Key(void** ppobj) { return(VJSONMember::Key(ppobj)); }

	public:
		virtual bool				get_Bool(void) { return(m_val); }
		virtual void				set_Bool(bool val) { m_val=val; }
};


#endif	// _CJSONBool_H_
