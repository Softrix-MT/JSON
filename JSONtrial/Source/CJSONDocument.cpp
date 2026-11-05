#include "../INCLUDE/StdHead.h"

#include "../INCLUDE/CJSONDocument.h"
#include "../INCLUDE/BJSONNodeCollection.h"

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                              ГБГbГZБ[ГWТшЛ`                               */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГfБ[Г^Ч╠Иц                                 */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГRБ[ГhЧ╠Иц                                 */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                                ВbВkВ`ВrВr                                 */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONDocument::XString::XString(void)
{
	enable = false;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONDocument::XString::~XString(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВrВФВПВТВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::XString::Store(LPCSTR str)
{
	HRESULT		hResult;

	if (!str) str = "";
	bytes = ::strlen(str);

	if (FAILED(hResult=Reallocation(bytes+sizeof("")))) return(hResult);
	if (bytes) ::strncpy_s(m_str, (bytes+1), str, bytes);
	m_str[bytes] = '\0';

	return(NOERROR);
}

/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВP                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                         ВvВТВЙВФВЕВhВОВДВЕВОВФ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::WriteIndent(ISequentialStream* pstm)
{
	ULONG		byteWrite=0;
	size_t		nLoop;
	HRESULT		hResult;

	if ((m_indent.enable) && (m_indent.bytes)) {
		for(nLoop=0; nLoop<m_stack; nLoop++) {
			if (FAILED(hResult=pstm->Write(m_indent.Buffer(0), ULONG(m_indent.bytes), &byteWrite))) return(hResult);
			}
		}
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                        ВvВТВЙВФВЕВmВЕВЧВМВЙВОВЕ                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::WriteNewline(ISequentialStream* pstm)
{
	ULONG		byteWrite=0;
	HRESULT		hResult;

	if (m_indent.enable) {
		if (FAILED(hResult=pstm->Write(m_line.Buffer(0), ULONG(m_line.bytes), &byteWrite))) return(hResult);
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВvВТВЙВФВЕ                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::Write(ISequentialStream* pstm, JSONValue* pobj)
{
	HRESULT		hResult;

	switch(IsJSONNodeType(pobj->IsNodeType())) {
		case JSONNodeType_String :
			if (FAILED(hResult=WriteString(pstm, pobj))) return(hResult);
			break;
		case JSONNodeType_Number :
			if (FAILED(hResult=WriteNumber(pstm, pobj))) return(hResult);
			break;
		case JSONNodeType_Bool :
			if (FAILED(hResult=WriteBool(pstm, pobj))) return(hResult);
			break;
		case JSONNodeType_Array :
			if (FAILED(hResult=WriteArray(pstm, pobj))) return(hResult);
			break;
		case JSONNodeType_Object :
			if (FAILED(hResult=WriteObject(pstm, pobj))) return(hResult);
			break;
		default:
			return(E_INVALIDARG);
		}

	return(NOERROR);
}
HRESULT CJSONDocument::Write(ISequentialStream* pstm, JSONKey* pobj)
{
	ULONG		byteWrite=0;
	LPCSTR		str=pobj->get_String();
	size_t		nSize;
	HRESULT		hResult;

	if (!str) return(pstm->Write("null", 4, &byteWrite));

	if (FAILED(hResult=pstm->Write("\"", 1, &byteWrite))) return(hResult);
	nSize = ::strlen(str);
	while(nSize) {
		size_t	nBytes=nSize;

		if ((100*1024*1024) < nBytes) nBytes = (100*1024*1024);
		if (FAILED(hResult=pstm->Write(str, ULONG(nBytes), &byteWrite))) return(hResult);
		str += nBytes;
		nSize -= nBytes;
		}
	if (FAILED(hResult=pstm->Write("\"", 1, &byteWrite))) return(hResult);

	return(NOERROR);
}
HRESULT CJSONDocument::WriteNumber(ISequentialStream* pstm, JSONValue* pobj)
{
	ULONG		byteWrite=0;
	LONGLONG	nval=pobj->get_Long();
	double		dval=pobj->get_Double();
	char		str[256];
	HRESULT		hResult;

	if (dval == double(nval)) {
		::sprintf_s(str, _countof(str), "%I64d", nval);
		}
	else{
		::sprintf_s(str, _countof(str), "%1.17g", dval);
		}

	if (FAILED(hResult=pstm->Write(str, ULONG(::strlen(str)), &byteWrite))) return(hResult);

	return(NOERROR);
}
HRESULT CJSONDocument::WriteString(ISequentialStream* pstm, JSONValue* pobj)
{
	ULONG		byteWrite=0;
	LPCSTR		str=pobj->get_String();
	size_t		nSize;
	HRESULT		hResult;

	if ((!str) || ((nSize=::strlen(str)) == 0)) return(pstm->Write("null", 4, &byteWrite));

	if (FAILED(hResult=pstm->Write("\"", 1, &byteWrite))) return(hResult);
	while(nSize) {
		size_t	nBytes=nSize;

		if ((100*1024*1024) < nBytes) nBytes = (100*1024*1024);
		if (FAILED(hResult=pstm->Write(str, ULONG(nBytes), &byteWrite))) return(hResult);
		str += nBytes;
		nSize -= nBytes;
		}
	if (FAILED(hResult=pstm->Write("\"", 1, &byteWrite))) return(hResult);

	return(NOERROR);
}
HRESULT CJSONDocument::WriteBool(ISequentialStream* pstm, JSONValue* pobj)
{
	ULONG		byteWrite=0;
	HRESULT		hResult;

	if (pobj->get_Bool()) {
		if (FAILED(hResult=pstm->Write("true", 4, &byteWrite))) return(hResult);
		}
	else{
		if (FAILED(hResult=pstm->Write("false", 5, &byteWrite))) return(hResult);
		}

	return(NOERROR);
}
HRESULT CJSONDocument::WriteArray(ISequentialStream* pstm, JSONValue* pobj)
{
	ULONG		byteWrite;
	size_t		nLoop, nSize=pobj->NodeSize();
	HRESULT		hResult;

	if (FAILED(hResult=pstm->Write("[", 1, &byteWrite))) return(hResult);
	if (FAILED(hResult=WriteNewline(pstm))) return(hResult);

	if (nSize) {
		m_stack++;
		for(nLoop=0; nLoop<nSize; nLoop++) {
			JSONAnchorPtr<JSONValue>	pnode;

			if (FAILED(hResult=pobj->Node(int(nLoop), pnode))) return(hResult);
// value
			if (FAILED(hResult=WriteIndent(pstm))) return(hResult);
			if (FAILED(hResult=Write(pstm, pnode))) return(hResult);
			if (nLoop < (nSize-1)) {
				if (FAILED(hResult=pstm->Write(",", 1, &byteWrite))) return(hResult);
				}
			if (FAILED(hResult=WriteNewline(pstm))) return(hResult);
			pnode.Destroy();
			}
		m_stack--;
		}

	if (FAILED(hResult=WriteIndent(pstm))) return(hResult);
	if (FAILED(hResult=pstm->Write("]", 1, &byteWrite))) return(hResult);

	return(NOERROR);
}
HRESULT CJSONDocument::WriteObject(ISequentialStream* pstm, JSONValue* pobj)
{
	ULONG		byteWrite;
	size_t		nLoop, nSize=pobj->NodeSize();
	HRESULT		hResult;

	if (FAILED(hResult=pstm->Write("{", 1, &byteWrite))) return(hResult);
	if (FAILED(hResult=WriteNewline(pstm))) return(hResult);
// Member
	if (nSize) {
		m_stack++;
		for(nLoop=0; nLoop<nSize; nLoop++) {
			JSONAnchorPtr<JSONValue>	pnode;
			JSONAnchorPtr<JSONKey>		pkey;

			if (FAILED(hResult=pobj->Node(int(nLoop), pnode))) return(hResult);
			if (FAILED(hResult=WriteIndent(pstm))) return(hResult);
// string
			if (FAILED(hResult=pnode->Key(pkey))) return(hResult);
			if (pkey->IsNodeType() != JSONNodeType_Key) return(E_FAIL);
			if (FAILED(hResult=Write(pstm, pkey))) return(hResult);
			pkey.Destroy();
// :
			if (m_indent.enable) {
				if (FAILED(hResult=pstm->Write(" : ", 3, &byteWrite))) return(hResult);
				}
			else{
				if (FAILED(hResult=pstm->Write(":", 1, &byteWrite))) return(hResult);
				}
// value
			if (FAILED(hResult=Write(pstm, pnode))) return(hResult);
			if (nLoop < (nSize-1)) {
				if (FAILED(hResult=pstm->Write(",", 1, &byteWrite))) return(hResult);
				}
			if (FAILED(hResult=WriteNewline(pstm))) return(hResult);

			pnode.Destroy();
			}
		m_stack--;
		}
	if (FAILED(hResult=WriteIndent(pstm))) return(hResult);
	if (FAILED(hResult=pstm->Write("}", 1, &byteWrite))) return(hResult);

	return(NOERROR);
}

/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONDocument::CJSONDocument(void)
{
	m_stack = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONDocument::~CJSONDocument(void)
{
	m_pnode.Destroy();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВhВОВЙВФВЙВБВМВЙВЪВЕ                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::Initialize(void)
{
	HRESULT		hResult;

	m_pnode.Destroy();
	if (FAILED(hResult=m_indent.Store("\x20\x20"))) return(hResult);
	if (FAILED(hResult=m_line.Store("\x0D\x0A"))) return(hResult);
//	if (FAILED(hResult=m_bom.Store(\xEF\xBB\xBF))) return(hResult);

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВbВТВЕВБВФВЕВmВПВДВЕ                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::CreateNode(JSONNodeType type, void** ppobj)
{
	VJSONMember*	pmem;
	HRESULT			hResult;

	m_pnode.Destroy();
	if (FAILED(hResult=BJSONNodeCollection::Create(&m_XDescendant, type, m_pnode, &pmem))) return(hResult);

	m_pnode->Keep();
	*ppobj = static_cast<JSONValue*>(m_pnode);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВmВПВДВЕ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::Node(void** ppobj)
{
	if (m_pnode.IsNull()) return(E_INVALIDARG);

	m_pnode->Keep();
	*ppobj = static_cast<JSONValue*>(m_pnode);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                         ВrВЕВФВoВТВПВРВЕВТВФВЩ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::SetProperty(JSONProperty prop, BOOL enable)
{
	switch(prop) {
		case JSONProperty_Indent :
		case JSONProperty_NewLine :
			m_indent.enable = (enable != FALSE);
			return(NOERROR);
		}

	return(E_INVALIDARG);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВrВЕВФВhВОВДВЕВОВФ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::SetPropertyChars(JSONProperty prop, LPCSTR str)
{
	if (!str) {
		m_indent.bytes = 0;
//		m_indent.Deallocation();
		return(E_INVALIDARG);
		}

	switch(prop) {
		case JSONProperty_Indent : return(m_indent.Store(str));
		case JSONProperty_NewLine : return(m_line.Store(str));
		}

	return(E_INVALIDARG);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВqВЕВБВД                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::Read(ISequentialStream* pstm)
{
	BParseControl	ctrl(pstm);
	VJSONMember*	pmem;
	HRESULT			hResult;

	m_pnode.Destroy();
	if (FAILED(hResult=ctrl.SkipBOM())) return(hResult);
	if (FAILED(hResult=ctrl.SkipWhitespace())) {
//		ctrl.Empty();
		return(hResult);
		}
	if (FAILED(hResult=BJSONNodeCollection::Parse(&m_XDescendant, ctrl, m_pnode, &pmem))) {
//		ctrl.Empty();
		return(hResult);
		}
	if (SUCCEEDED(hResult=ctrl.SkipWhitespace())) {
//		ctrl.Empty();
		return(hResult);
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВvВТВЙВФВЕ                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONDocument::Write(ISequentialStream* pstm)
{
	HRESULT			hResult;

	m_stack = 0;
	if (FAILED(hResult=Write(pstm, m_pnode))) return(hResult);

	if (FAILED(hResult=WriteNewline(pstm))) return(hResult);
	return(NOERROR);
}
