#include "../INCLUDE/StdHead.h"

#include "../INCLUDE/CJSONDocument.h"
#include "../INCLUDE/BParseControl.h"

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                              ГБГbГZБ[ГWТшЛ`                               */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
class XStream : public ISequentialStream {
	protected:
		LPCSTR						m_str;
		size_t						m_index;
		size_t						m_bytes;

	public:
									XStream(LPCSTR str) : m_str(str) { m_index=0; m_bytes=::strlen(str); }
		virtual						~XStream(void) {}

	public:
// IUnknown ╥┐п─▐
		STDMETHODIMP				QueryInterface(REFIID riID, void** ppvObject) { return(E_NOTIMPL); }
		STDMETHODIMP_(ULONG)		AddRef(void) { return(E_NOTIMPL); }
		STDMETHODIMP_(ULONG)		Release(void) { return(E_NOTIMPL); }
// ISequentialStream ╥┐п─▐
		STDMETHODIMP				Read(LPVOID pvBuff, ULONG cbSize, ULONG* pcbRead) {
			ULONG		tmp;
			HRESULT		hResult=NOERROR;

			if (!pcbRead) pcbRead = &tmp;
			*pcbRead = 0;
			if (m_bytes <= m_index) return(S_FALSE);
			if (m_bytes <= (m_index+cbSize)) {
				hResult = S_FALSE;
				cbSize = ULONG(m_bytes - m_index);
				}
			if (cbSize == 1) {
				*(LPSTR)(pvBuff) = m_str[m_index++];
				}
			else{
				::memcpy(pvBuff, &m_str[m_index], cbSize);
				m_index += cbSize;
				}
			*pcbRead = cbSize;
			return(hResult);
		}
		STDMETHODIMP				Write(LPCVOID pvBuff, ULONG cbSize, ULONG* pcbWritten) { return(E_NOTIMPL); }
};

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
/*                  ВiВrВnВmВbВТВЕВБВФВЕВcВПВГВХВНВЕВОВФ                     */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT JSONCreateDocument(JSONDocument** ppjson)
{
	CJSONDocument*	pobj;
	HRESULT			hResult;

	if (!ppjson)  return(E_INVALIDARG);
	*ppjson = NULL;

	if ((pobj=new CJSONDocument()) == NULL) return(E_OUTOFMEMORY);
	if (FAILED(hResult=pobj->Initialize())) {
		pobj->Discard();
		return(hResult);
		}

	*ppjson = pobj;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                      ВiВrВnВmВkВПВБВДВrВФВТВЕВБВН                         */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT JSONLoadStream(ISequentialStream* pstm, JSONDocument** ppjson)
{
	CJSONDocument*	pobj;
	HRESULT			hResult;

	if (!ppjson)  return(E_INVALIDARG);
	*ppjson = NULL;

	if ((pobj=new CJSONDocument()) == NULL) return(E_OUTOFMEMORY);
	if ((FAILED(hResult=pobj->Initialize()))
	|| (FAILED(hResult=pobj->Read(pstm)))) {
		pobj->Discard();
		return(hResult);
		}

	*ppjson = pobj;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                      ВiВrВnВmВkВПВБВДВrВФВТВЙВОВЗ                         */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT JSONLoadString(LPCSTR str, JSONDocument** ppjson)
{
	XStream		stm(str);

	return(::JSONLoadStream(&stm, ppjson));
}
