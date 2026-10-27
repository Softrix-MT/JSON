#ifndef _CJSONDocument_H_
#define _CJSONDocument_H_
#include "../INCLUDE/VJSONAnchor.h"

#include "../INCLUDE/BParseControl.h"
#include "../INCLUDE/BString.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONDocument : public JSONDocument, public VJSONAnchor {
	class XDescendant : public JSONAnchor {
		private:
			ULONG					m_count;
		public:
									XDescendant(void) { m_count=0; }
			virtual					~XDescendant(void) {}
		public:
			virtual ULONG			Keep(void) { return(++m_count); }
			virtual ULONG			Discard(void) { return(--m_count); }
	};
	class XString : public BString {
		public:
			bool					enable;
			size_t					bytes;
		public:
									XString(void);
			virtual					~XString(void);
		public:
			HRESULT					Store(LPCSTR str);
	};
	protected:
		JSONAnchorPtr<JSONNode>		m_pnode;
		XDescendant					m_XDescendant;

	protected:
		XString						m_indent;
		XString						m_line;
//		XString						m_bom;					// ByteOrderMark

	protected:
		size_t						m_stack;

	public:
									CJSONDocument(void);
		virtual						~CJSONDocument(void);

	public:
		virtual ULONG				Keep(void) { return(VJSONAnchor::Keep()); }
		virtual ULONG				Discard(void){ return(VJSONAnchor::Discard()); }

	protected:
		HRESULT						WriteIndent(ISequentialStream* pstm);
		HRESULT						WriteNewline(ISequentialStream* pstm);
		HRESULT						Write(ISequentialStream* pstm, JSONNode* pobj);
		HRESULT						Write(ISequentialStream* pstm, JSONNumber* pobj);
		HRESULT						Write(ISequentialStream* pstm, JSONString* pobj);
		HRESULT						Write(ISequentialStream* pstm, JSONBool* pobj);
		HRESULT						Write(ISequentialStream* pstm, JSONArray* pobj);
		HRESULT						Write(ISequentialStream* pstm, JSONObject* pobj);

	public:
		virtual HRESULT				Initialize(void);
		virtual HRESULT				CreateNode(JSONNodeType type, void** ppobj);
		virtual HRESULT				Node(void** ppobj);

		virtual HRESULT				SetProperty(JSONProperty prop, BOOL enable);
		virtual HRESULT				SetPropertyChars(JSONProperty prop, LPCSTR str);

		virtual HRESULT				Read(ISequentialStream* pstm);
		virtual HRESULT				Write(ISequentialStream* pstm);
};


#endif	// _CJSONDocument_H_
