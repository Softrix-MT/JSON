#ifndef _BString_H_
#define _BString_H_

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
class BString {
	protected:
		LPSTR						m_str;
		size_t						m_bytes;

	public:
									BString(void);
		virtual						~BString(void);

	public:
//									operator LPCSTR();

	protected:
		void*						Reallocation(void* pbuf, size_t bytes) { return(::realloc(pbuf, memOPTIMUM(bytes))); }

	public:
		virtual LPSTR				Buffer(int index) { return(&m_str[index]); }

	public:
		virtual HRESULT				Reallocation(size_t bytes);
		virtual void				Deallocation(void);
//		HRESULT						Append(LPCSTR str, size_t byte=-1);
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
inline BString::BString(void)
{
	m_str = NULL;
	m_bytes = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline BString::~BString(void)
{
	Deallocation();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                      ВПВРВЕВТВБВФВПВТ  ВkВoВbВrВsВq                       */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
inline BString::operator LPCSTR(void)
{
	if (m_str) m_str[m_bytes-1] = NULL;
	return(m_str);
}
*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                         ВqВЕВБВМВМВПВГВБВФВЙВПВО                          */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BString::Reallocation(size_t bytes)
{
	if (!bytes) bytes = 1;
	if (m_bytes < bytes) {
		LPVOID		pvbuf;

		if ((pvbuf=Reallocation(m_str, bytes)) == NULL) return(E_OUTOFMEMORY);
		m_str = LPSTR(pvbuf);
		m_str[m_bytes] = NULL;
		m_bytes = bytes;
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                         ВcВЕВБВМВМВПВГВБВФВЙВПВО                          */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void BString::Deallocation(void)
{
	if (m_str) {
		::free(m_str);
		m_str = NULL;
		}
	m_bytes = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               В`ВРВРВЕВОВД                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
inline HRESULT BString::Append(LPCSTR str, size_t bytes)
{
	size_t		index=0;
	HRESULT		hResult;

	if (!str) str = "";
	if (bytes == size_t(-1)) bytes = ::strlen(str);

	if (m_str) index = ::strlen(m_str);
	if (FAILED(hResult=Reallocation(index+bytes+sizeof("")))) return(hResult);
	if (bytes) strncpy_s(&m_str[index], (bytes+1), str, bytes);
	m_str[index+bytes] = NULL;

	return(NOERROR);
}
*/

#endif	// _BString_H_
