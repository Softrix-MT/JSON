#ifndef _CJSONValue_H_
#define _CJSONValue_H_
#include "../INCLUDE/VJSONMember.h"

#include "../INCLUDE/BStringControl.h"
#include "../INCLUDE/BJSONNodeCollection.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONValue : public JSONValue, public VJSONMember {
	protected:
		JSONNodeType				m_node;

	protected:
// Bool
		bool						m_bool;
// Number
		struct {
			LONGLONG			lVal;								// &I64d
			double				dblVal;
			}						m_num;
// String
		BStringControl				m_str;
// Array & Object
		BJSONNodeCollection			m_list;

	public:
									CJSONValue(JSONAnchor* pobj);
		virtual						~CJSONValue(void);

	public:
//									operator BStringControl&() { return(m_str); }
//									operator BJSONNodeCollection&() { return(m_list); }

	public:
		virtual ULONG				Keep(void) { return(VJSONMember::Keep()); }
		virtual ULONG				Discard(void) { return(VJSONMember::Discard()); }

	public:
		virtual JSONNodeType		IsNodeType(void) { return(m_node); }
		void						SetNodeType(JSONNodeType type) { m_node = type; }

	public:
// String
		virtual LPCSTR				get_String(void);
		virtual HRESULT				set_String(LPCSTR str) { return(set_UTF8(str, size_t(-1))); }

		virtual HRESULT				set_UTF8(LPCSTR str, size_t bytes);
		virtual HRESULT				set_UTF16(LPCWSTR str, size_t length);
		virtual HRESULT				set_CP(UINT cp, LPCSTR str, size_t bytes);
		virtual HRESULT				set_ACP(LPCSTR str, size_t bytes) { return(set_CP(CP_ACP, str, bytes)); }
// Number
		virtual LONGLONG			get_Long(void) { return(m_num.lVal); }
		virtual void				set_Long(LONGLONG val);
		virtual double				get_Double(void) { return(m_num.dblVal); }
		virtual void				set_Double(double val);
// Bool
		virtual bool				get_Bool(void) { return(m_bool); }
		virtual void				set_Bool(bool val);
// Array & Object
		virtual int					NodeSize(void);
		virtual HRESULT				Node(int index, void** ppvobj);
		virtual void				RemoveNode(int index);
		virtual HRESULT				CreateNode(JSONNodeType type, void** ppobj, LPCSTR key);
// Object
		virtual int					FindNode(LPCSTR key);
		virtual HRESULT				FindNode(LPCSTR key, void** ppobj);
// Member
		virtual HRESULT				Key(void** ppobj);

	public:
		virtual HRESULT				ParseString(BParseControl& stm);
		virtual HRESULT				ParseNumber(BParseControl& stm);
		virtual HRESULT				ParseArray(BParseControl& stm);
		virtual HRESULT				ParseObject(BParseControl& stm);
		virtual HRESULT				ParseNull(BParseControl& stm);
		virtual HRESULT				ParseTrue(BParseControl& stm);
		virtual HRESULT				ParseFalse(BParseControl& stm);
};

#endif	// _CJSONValue_H_
