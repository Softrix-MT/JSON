#ifndef _CJSONString_H_
#define _CJSONString_H_
#include "../INCLUDE/VJSONMember.h"
#include "../INCLUDE/BStringControl.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONString : public JSONString, public VJSONMember, public BStringControl {
	public:
									CJSONString(JSONAnchor* pobj);
		virtual						~CJSONString(void);

	public:
		virtual ULONG				Keep(void) { return(VJSONMember::Keep()); }
		virtual ULONG				Discard(void) { return(VJSONMember::Discard()); }

	public:
		virtual JSONNodeType		IsNodeType(void) { return((m_str != NULL) ? JSONNodeType_String : JSONNodeType_Null); }
		virtual HRESULT				Key(void** ppobj) { return(VJSONMember::Key(ppobj)); }

	public:
//		virtual LPCSTR				get_String(void) { return((BStringControl)*this); }
		virtual LPCSTR				get_String(void) { return(m_str); }
		virtual HRESULT				set_String(LPCSTR str) { return(set_UTF8(str, size_t(-1))); }

	public:
		virtual HRESULT				set_UTF8(LPCSTR str, size_t bytes) { return(BStringControl::set_UTF8(str, bytes)); }
		virtual HRESULT				set_UTF16(LPCWSTR str, size_t length) { return(BStringControl::set_UTF16(str, length)); }
		virtual HRESULT				set_CP(UINT cp, LPCSTR str, size_t bytes) { return(BStringControl::set_CP(cp, str, bytes)); }
		virtual HRESULT				set_ACP(LPCSTR str, size_t bytes) { return(BStringControl::set_CP(CP_ACP, str, bytes)); }
};

#define CJSONNull					CJSONString

#endif	// _CJSONString_H_
