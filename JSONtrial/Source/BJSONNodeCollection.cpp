#include "../INCLUDE/StdHead.h"
#include "../INCLUDE/BJSONNodeCollection.h"

#include "../INCLUDE/CJSONValue.h"

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
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
BJSONNodeCollection::BJSONNodeCollection(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
BJSONNodeCollection::~BJSONNodeCollection(void)
{
	Uninitialize();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВeВЙВОВД                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
int BJSONNodeCollection::FindNode(LPCSTR val)
{
	int			nLoop;
	HRESULT		hResult;

	for(nLoop=0; nLoop<m_node.Size(); nLoop++) {
		JSONAnchorPtr<JSONKey>	pnode;

		if ((hResult=m_node[nLoop]->Key(pnode)) == NOERROR) {
			if (!::strcmp(val, pnode->get_String())) return(nLoop);
			pnode.Destroy();
			}
		}

	return(-1);
}
HRESULT BJSONNodeCollection::FindNode(LPCSTR key, void** ppobj)
{
	int		nIndex;

	if ((nIndex=FindNode(key)) >= 0) {
		JSONValue*		pnode=m_node[nIndex];

		*ppobj = pnode;
		pnode->Keep();
		return(NOERROR);
		}

	return(E_ELEMENT_NOTFOUND);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           В`ВРВРВЕВОВДВmВПВДВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT BJSONNodeCollection::AppendNode(JSONValue* pnode)
{
	HRESULT		hResult;

	if (FAILED(hResult=m_node.Add(pnode))) return(hResult);
	pnode->Keep();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВqВЕВНВПВЦВЕ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void BJSONNodeCollection::RemoveNode(int index)
{
	if ((0 <= index) && (index < m_node.Size())) {
		m_node[index]->Discard();
		m_node.Remove(index);
		}
}
void BJSONNodeCollection::RemoveNode(LPCSTR key)
{
	int		nIndex;

	if ((nIndex=FindNode(key)) >= 0) RemoveNode(nIndex);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВdВНВРВФВЩ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void BJSONNodeCollection::EmptyNode(void)
{
	int		nLoop;

	for(nLoop=0; nLoop<m_node.Size(); nLoop++) m_node[nLoop]->Discard();
	m_node.Empty();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВmВПВДВЕ                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT BJSONNodeCollection::Node(int index, void** ppobj)
{
	JSONValue*	pnode;

	if ((index < 0) || (m_node.Size() <= index)) return(E_INVALIDARG);
	pnode = m_node[index];
	pnode->Keep();
	*ppobj = pnode;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВbВТВЕВБВФВЕ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT BJSONNodeCollection::Create(JSONAnchor* proot, JSONNodeType type, void** ppobj, VJSONMember** const ppmem)
{
	CJSONValue*	pnode;

	if (!ppobj)  return(E_INVALIDARG);
	*ppobj = NULL;

	switch(IsJSONNodeType(type)) {
		case JSONNodeType_String :
		case JSONNodeType_Number :
		case JSONNodeType_Bool :
		case JSONNodeType_Array :
		case JSONNodeType_Object :
			break;
		default:
			return(E_INVALIDARG);
		}

	if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
	pnode->SetNodeType(type);

	*ppobj = static_cast<JSONValue*>(pnode);
	*ppmem = static_cast<VJSONMember*>(pnode);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВoВБВТВУВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT BJSONNodeCollection::Parse(JSONAnchor* proot, BParseControl& stm, void** ppobj, VJSONMember** const ppmem)
{
	CJSONValue*	pnode;
	HRESULT		hResult;

	if (!stm.Bytes()) {
		if (FAILED(hResult=stm.Load(1))) return(hResult);
		}
// Number
	if  ((stm.Value(0) == '-') || (('0' <= stm.Value(0)) && (stm.Value(0) <= '9'))) {
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseNumber(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}
// String
	if (stm.Value(0) == '\"') {
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseString(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}
// Array
	if (stm.Value(0) == '[') {
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseArray(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}
// Object
	if (stm.Value(0) == '{') {
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseObject(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}
	if (FAILED(hResult=stm.Load(3))) return(hResult);
// null
	if (!strncmp(stm.Buffer(0), "null", 4)) {							// JSONОdЧlВ═ПмХ╢ОЪИ╚КOВ═NG
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseNull(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}
// true
	if (!strncmp(stm.Buffer(0), "true", 4)) {							// JSONОdЧlВ═ПмХ╢ОЪИ╚КOВ═NG
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseTrue(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}
	if (FAILED(hResult=stm.Load(1))) return(hResult);
// false
	if (!strncmp(stm.Buffer(0), "false", 5)) {							// JSONОdЧlВ═ПмХ╢ОЪИ╚КOВ═NG
		if ((pnode=new CJSONValue(proot)) == NULL) return(E_OUTOFMEMORY);
		if (FAILED(hResult=pnode->ParseTrue(stm))) {
			pnode->Discard();
			return(hResult);
			}
		*ppobj = static_cast<JSONValue*>(pnode);
		*ppmem = static_cast<VJSONMember*>(pnode);
		return(NOERROR);
		}

	return(E_INVALIDARG);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                        ВtВОВЙВОВЙВФВЙВБВМВЙВЪВЕ                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void BJSONNodeCollection::Uninitialize(void)
{
	EmptyNode();
}
