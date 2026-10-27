#ifndef _VJSONMember_H_
#define _VJSONMember_H_
#include "../INCLUDE/VJSONNode.h"
#include "../INCLUDE/BStringControl.h"

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
class VJSONMember : public VJSONNode {
	class XJSONString : public JSONString, public VJSONNode, public BStringControl {
		public:
									XJSONString(void) {}
			virtual					~XJSONString(void) {}

		public:
			virtual ULONG			Keep(void) { return(VJSONNode::Keep()); }
			virtual ULONG			Discard(void){ return(VJSONNode::Discard()); }

		public:
			virtual JSONNodeType	IsNodeType(void) { return((m_str != NULL) ? JSONNodeType_String : JSONNodeType_Null); }
			virtual HRESULT			Key(void** ppobj) { return(E_NOTIMPL); }

		public:
			virtual LPCSTR			get_String(void) { return(m_str); }
			virtual HRESULT			set_String(LPCSTR str) { return(set_UTF8(str, size_t(-1))); }

		public:
			virtual HRESULT			set_UTF8(LPCSTR str, size_t bytes) { return(BStringControl::set_UTF8(str, bytes)); }
			virtual HRESULT			set_UTF16(LPCWSTR str, size_t length) { return(BStringControl::set_UTF16(str, length)); }
			virtual HRESULT			set_CP(UINT cp, LPCSTR str, size_t bytes) { return(BStringControl::set_CP(cp, str, bytes)); }
			virtual HRESULT			set_ACP(LPCSTR str, size_t bytes) { return(BStringControl::set_CP(CP_ACP, str, bytes)); }
	};
	protected:
		bool						m_keyEnable;
		XJSONString					m_key;

	public:
									VJSONMember(JSONAnchor* pobj);
		virtual						~VJSONMember(void);

	public:
		virtual void				EnableKey(bool enable) { m_keyEnable=enable; }
		virtual BStringControl&		KeyString(void) { return(m_key); }

	public:
		virtual HRESULT				Key(void** ppobj);
		virtual HRESULT				set_Key(LPCSTR key);
};

/*****************************************************************************/
/*                              ГCГУГЙГCГУТшЛ`                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline VJSONMember::VJSONMember(JSONAnchor* pobj) : VJSONNode(pobj), m_keyEnable(false)
{
	m_key.Delegation(this);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline VJSONMember::~VJSONMember(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВjВЕВЩ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT VJSONMember::Key(void** ppobj)
{
	if (!m_keyEnable) return(E_NOTIMPL);

	*ppobj = static_cast<JSONString*>(&m_key);
	m_key.Keep();
	return(NOERROR);
}
inline HRESULT VJSONMember::set_Key(LPCSTR key)
{
	EnableKey(true);
	return(m_key.set_UTF8(key, -1));
}


#endif	// _VJSONMember_H_
