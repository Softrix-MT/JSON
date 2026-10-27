#include "../INCLUDE/StdHead.h"

#include "../INCLUDE/CJSONObject.h"

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
CJSONObject::CJSONObject(JSONAnchor* pobj) : VJSONMember(pobj)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONObject::~CJSONObject(void)
{
	Uninitialize();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВbВТВЕВБВФВЕВmВПВДВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONObject::CreateNode(JSONNodeType type, LPCSTR key, void** ppobj)
{
	JSONAnchorPtr<JSONNode>		pnode;
	VJSONMember*				pmem;
	HRESULT						hResult;

	if ((!key) || (!::strlen(key))) return(E_INVALIDARG);

	if (FAILED(hResult=BJSONNodeCollection::Create(m_pobjCounter, type, pnode, &pmem))) return(hResult);
	if (FAILED(hResult=pmem->set_Key(key))) return(hResult);
	if (FAILED(hResult=AppendNode(pnode))) return(hResult);

	*ppobj = pnode.Detach();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВeВЙВОВДВmВПВДВЕ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONObject::FindNode(LPCSTR key, void** ppobj)
{
	return(BJSONNodeCollection::FindNode(key, ppobj));
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВoВБВТВУВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONObject::Parse(BParseControl& stm)
{
	HRESULT		hResult;

	if (!stm.Bytes()) {
		if (FAILED(hResult=stm.Load(1))) return(hResult);
		}
// Start Check
	if (stm.Value(0) != '{') return(E_INVALIDARG);
	stm.Empty();
	if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
// Member
	if (stm.Value(0) != '}') {
		for(;;) {
			JSONAnchorPtr<VJSONNode>	pnode;
			VJSONMember*				pmem;
			BStringControl				src;
			int							val;
// string
			if (FAILED(hResult=src.Parse(stm))) return(hResult);
// :
			if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
			if (stm.Value(0) != ':') return(E_INVALIDARG);
			stm.Empty();
// value
			if (FAILED(hResult=stm.SkipWhitespace())) return(E_INVALIDARG);
//			buf.stack++;
			if (FAILED(hResult=BJSONNodeCollection::Parse(this, stm, pnode, &pmem))) return(hResult);
//			buf.stack--;
			BStringControl&		dst=pmem->KeyString();
			dst.Swap(src);
			pmem->EnableKey(true);
			if (FAILED(hResult=AppendNode(pnode))) return(hResult);
			pnode.Destroy();

			if (FAILED(hResult=stm.SkipWhitespace())) return(E_INVALIDARG);
			if ((val=stm.Value(0)) == '}') break;
			if (val != ',') return(E_INVALIDARG);
			stm.Empty();
			if (FAILED(hResult=stm.SkipWhitespace())) return(E_INVALIDARG);
			}
		}
	stm.Empty();

	return(NOERROR);
}
