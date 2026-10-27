#ifndef _BArray_H_
#define _BArray_H_
#include <new.h>

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
template<class TYPE, class ARG_TYPE=const TYPE&>
class BArray {
	private:
		TYPE*						m_pBuffer;
		int							m_nLimit;
		int							m_nSize;

	public:
									BArray(void);
		virtual						~BArray(void);

	public:
		const TYPE&					operator[](int nIndex) const { return(m_pBuffer[nIndex]); }
		TYPE&						operator[](int nIndex) { return(m_pBuffer[nIndex]); }
									operator TYPE*() { return(m_pBuffer); }

		int							Size(void) const { return(m_nSize); }
		HRESULT						Size(int nSize) { return(Secure(nSize)); }
		int							Byte(void) const { return(m_nSize*sizeof(TYPE)); }
		const TYPE*					Buffer(int nIndex=0) const { return(&m_pBuffer[nIndex]); }
		TYPE*						Buffer(int nIndex=0) { return(&m_pBuffer[nIndex]); }
		TYPE						GetAt(int nIndex) const { return(m_pBuffer[nIndex]); }
		const TYPE&					ElementAt(int nIndex) const { return(m_pBuffer[nIndex]); }
		TYPE&						ElementAt(int nIndex) { return(m_pBuffer[nIndex]); }

	public:
		TYPE*						begin(void) { return(m_pBuffer); }
		TYPE*						end(void) { return(m_pBuffer+m_nSize); }

	protected:
		virtual HRESULT				Reallocate(int nSize);

	public:
		HRESULT						Allocate(int nSize);
		HRESULT						Secure(int nSize);
		HRESULT						SetAt(int nIndex, ARG_TYPE newElement);
		HRESULT						Append(int nSize, int nExtSize=8);
		HRESULT						Add(ARG_TYPE newElement, int nExtSize=8);
		HRESULT						Add(const BArray& newElement, int nExtSize=8);
		HRESULT						Copy(const BArray& newElement);
		HRESULT						Insert(int nIndex, ARG_TYPE newElement);
		HRESULT						Insert(int nIndex, const BArray& newElement);
		void						Remove(int nIndex, int nSize=1);
		void						Empty(void);
		void						Destroy(void);
};

/*****************************************************************************/
/*                              ГCГУГЙГCГУТшЛ`                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВP                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВqВЕВБВМВМВПВГВБВФВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Reallocate(int nSize)
{
//	if (m_nLimit < nSize) {
		LPVOID	pvBuffer;

		if (!(pvBuffer=::realloc(m_pBuffer, memOPTIMUM(ULONG(nSize)*sizeof(TYPE))))) return(E_OUTOFMEMORY);
		m_pBuffer = static_cast<TYPE*>(pvBuffer);
		m_nLimit = nSize;
//		}

	return(NOERROR);
}

/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline BArray<TYPE, ARG_TYPE>::BArray(void)
{
	m_pBuffer = NULL;
	m_nLimit = 0;
	m_nSize = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline BArray<TYPE, ARG_TYPE>::~BArray(void)
{
	Destroy();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             В`ВМВМВПВГВБВФВЕ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Allocate(int nSize)
{
	HRESULT		hResult;

	if (m_nLimit < nSize) {
		if (FAILED(hResult=Reallocate(nSize))) return(hResult);
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВrВЕВГВХВТВЕ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Secure(int nSize)
{
	HRESULT		hResult;

	if (m_nSize == nSize) return(NOERROR);
	if (m_nLimit < nSize) {
		if (FAILED(hResult=Reallocate(nSize))) return(hResult);
		}

	m_nSize = nSize;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВrВЕВФВ`ВФ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::SetAt(int nIndex, ARG_TYPE newElement)
{
	if ((nIndex < 0) || (m_nSize <= nIndex)) return(E_INVALIDARG);

	m_pBuffer[nIndex] = newElement;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               В`ВРВРВЕВОВД                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Append(int nSize, int nExtSize)
{
	int			nTotal=m_nSize+nSize;
	HRESULT		hResult;

	if (m_nLimit < nTotal) {
		if (FAILED(hResult=Reallocate(nTotal+nExtSize))) return(hResult);
		}

	m_nSize = nTotal;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  В`ВДВД                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement, int nExtSize)
{
	int			nIndex=m_nSize;
	HRESULT		hResult;

	if (m_nLimit <= m_nSize) {
		if (FAILED(hResult=Reallocate(m_nSize+nExtSize))) return(hResult);
		}
	m_nSize++;

	m_pBuffer[nIndex] = newElement;
	return(NOERROR);
}
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Add(const BArray& newElement, int nExtSize)
{
	int			nLoop, nIndex=m_nSize;
	int			nSize=m_nSize+newElement.m_nSize;
	HRESULT		hResult;

	if (m_nLimit <= nSize) {
		if (FAILED(hResult=Reallocate(nSize+nExtSize))) return(hResult);
		}
	m_nSize += newElement.m_nSize;

	for(nLoop=0; nLoop<newElement.m_nSize; nLoop++) m_pBuffer[nIndex+nLoop] = newElement[nLoop];
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВbВПВРВЩ                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Copy(const BArray& newElement)
{
	int			nKills=m_nSize;
	int			nLoop;
	HRESULT		hResult;

	m_nSize = 0;
	_DestructElements(m_pBuffer, nKills);
	if (m_nLimit < newElement.m_nSize) {
		if (FAILED(hResult=Reallocate(newElement.m_nSize))) return(hResult);
		}

	m_nSize = newElement.m_nSize;
	for(nLoop=0; nLoop<newElement.m_nSize; nLoop++) m_pBuffer[nLoop] = newElement[nLoop];
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВhВОВУВЕВТВФ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Insert(int nIndex, ARG_TYPE newElement)
{
	int			nSize=m_nSize+1;
	HRESULT		hResult;

	if ((nIndex < 0) || (m_nSize <= nIndex)) return(E_INVALIDARG);

	if (m_nLimit < nSize) {
		if (FAILED(hResult=Reallocate(nSize))) return(hResult);
		}
	::memmove(&m_pBuffer[nIndex+1], &m_pBuffer[nIndex], ((m_nSize-nIndex)*sizeof(TYPE)));

	m_nSize++;
	m_pBuffer[nIndex] = newElement;
	return(NOERROR);
}
template<class TYPE, class ARG_TYPE>
inline HRESULT BArray<TYPE, ARG_TYPE>::Insert(int nIndex, const BArray& newElement)
{
	int			nLoop, nSize=m_nSize+newElement.m_nSize;
	HRESULT		hResult;

	if ((nIndex < 0) || (m_nSize <= nIndex)) return(E_INVALIDARG);

	if (m_nLimit < nSize) {
		if (FAILED(hResult=Reallocate(nSize))) return(hResult);
		}
	::memmove(&m_pBuffer[nIndex+newElement.m_nSize], &m_pBuffer[nIndex], ((m_nSize-nIndex)*sizeof(TYPE)));

	m_nSize += newElement.m_nSize;
	for(nLoop=0; nLoop<newElement.m_nSize; nLoop++) m_pBuffer[nIndex+nLoop] = newElement[nLoop];
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВqВЕВНВПВЦВЕ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline void BArray<TYPE, ARG_TYPE>::Remove(int nIndex, int nSize)
{
	int		nMoveCount=m_nSize-(nIndex+nSize);

	if ((nIndex < 0) || (m_nSize <= nIndex)
	|| (nSize < 1) || (nMoveCount < 0)) return;

	m_nSize -= nSize;
	if (nMoveCount) ::memmove(&m_pBuffer[nIndex], &m_pBuffer[nIndex+nSize], (nMoveCount*sizeof(TYPE)));
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВdВНВРВФВЩ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline void BArray<TYPE, ARG_TYPE>::Empty(void)
{
	m_nSize = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВcВЕВУВФВТВПВЩ                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template<class TYPE, class ARG_TYPE>
inline void BArray<TYPE, ARG_TYPE>::Destroy(void)
{
	if (m_pBuffer != NULL) {
		int		nKills=m_nSize;

		m_nSize = 0;
		m_nLimit = 0;
		::free(m_pBuffer);
		m_pBuffer = NULL;
		}
}


#endif
