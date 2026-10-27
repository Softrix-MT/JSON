#include "../INCLUDE/StdHead.h"

#include "../INCLUDE/CJSONArray.h"

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
CJSONArray::CJSONArray(JSONAnchor* pobj) : VJSONMember(pobj)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONArray::~CJSONArray(void)
{
	Uninitialize();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВbВТВЕВБВФВЕВmВПВДВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONArray::CreateNode(JSONNodeType type, void** ppobj)
{
	JSONAnchorPtr<JSONNode>		pnode;
	VJSONMember*				pmem;
	HRESULT						hResult;

	if (FAILED(hResult=BJSONNodeCollection::Create(m_pobjCounter, type, pnode, &pmem))) return(hResult);
	if (FAILED(hResult=AppendNode(pnode))) return(hResult);

	*ppobj = pnode.Detach();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВoВБВТВУВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONArray::Parse(BParseControl& stm)
{
	HRESULT		hResult;

	if (!stm.Bytes()) {
		if (FAILED(hResult=stm.Load(1))) return(hResult);
		}
// Start Check
	if (stm.Value(0) != '[') return(E_INVALIDARG);
	stm.Empty();
	if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
// Element
	while(stm.Value(0) != ']') {
		for(;;) {
			JSONAnchorPtr<VJSONNode>	pnode;
			VJSONMember*				pmem;
			int							val;
// value
//			buf.stack++;
			if (FAILED(hResult=BJSONNodeCollection::Parse(this, stm, pnode, &pmem))) return(hResult);
//			buf.stack--;
			if (FAILED(hResult=AppendNode(pnode))) return(hResult);
			pnode.Destroy();

			if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
			if ((val=stm.Value(0)) == ']') break;
			if (val != ',') return(E_INVALIDARG);
			stm.Empty();
			if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
			}
		}
	stm.Empty();

	return(NOERROR);
}
