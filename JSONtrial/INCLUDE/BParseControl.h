#ifndef _BParseControl_H_
#define _BParseControl_H_
#include "../INCLUDE/BString.h"
#include <objidl.h>

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
class BParseControl : public BString {
	protected:
		ISequentialStream*			m_pobjStream;
		struct {
			size_t				start;
			size_t				end;
			}						m_scope;
		size_t						m_stack;
		size_t						m_marker;

	public:
									BParseControl(ISequentialStream* pstm);
		virtual						~BParseControl(void);

	public:
									operator ISequentialStream*() { return(m_pobjStream); }

	public:
		size_t						Bytes(void) { return(m_scope.end-m_scope.start); }
		int							Value(size_t index) { return(BYTE(m_str[m_scope.start+index])); }
		LPSTR						Buffer(int index) { return(&m_str[m_scope.start+index]); }
		void						Beginning(size_t index) { m_scope.start=index; }
//		void						Terminal(size_t index) { m_scope.end=index; }
	public:
		void						Inc(void) { m_stack++; }
		void						Dec(void) { m_stack--; }
//		size_t						get_Stack(void) { return(m_stack); }
//		size_t						get_Market(void) { return(m_marker); }

	public:
		virtual void				Deallocation(void);
		HRESULT						Load(size_t bytes);
		void						Empty(void);

	public:
		static bool					IsWhiteSpace(int val);
		HRESULT						SkipBOM(void);
		HRESULT						SkipWhitespace(void);
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
inline BParseControl::BParseControl(ISequentialStream* pstm) : m_pobjStream(pstm)
{
	m_scope.start = 0;
	m_scope.end = 0;
	m_stack = 0;
	m_marker = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline BParseControl::~BParseControl(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                         ВcВЕВБВМВМВПВГВБВФВЙВПВО                          */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void BParseControl::Deallocation(void)
{
	BString::Deallocation();

	m_scope.start = 0;
	m_scope.end = 0;
	m_marker = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВuВБВМВХВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
inline int BParseControl::Value(size_t index)
{
	size_t		index=m_bytes;
	ULONG		bytesRead=0;
	HRESULT		hResult;

	if (FAILED(hResult=Reallocation(m_bytes+bytes))) return(hResult);
	if (FAILED(hResult=m_pobjStream->Read(&m_str[index], bytes, &bytesRead))) return(hResult);

	m_scope.end = m_bytes;
	return(NOERROR);
}
*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВkВПВБВД                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BParseControl::Load(size_t bytes)
{
	ULONG		bytesRead=0;
	HRESULT		hResult;

	if (FAILED(hResult=Reallocation(m_scope.end+bytes))) return(hResult);
	if (FAILED(hResult=m_pobjStream->Read(&m_str[m_scope.end], ULONG(bytes), &bytesRead))) return(hResult);

	if (bytesRead != bytes) bytes = bytesRead;
	m_scope.end += bytes;

	return((bytesRead) ? hResult : E_INVALIDARG);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВdВНВРВФВЩ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void BParseControl::Empty(void)
{
	m_marker += m_scope.end;
	m_scope.start = 0;
	m_scope.end = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                         ВhВУВvВИВЙВФВЕВrВРВБВГВЕ                          */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline bool BParseControl::IsWhiteSpace(int val)
{
#if 0
	if (val <= 0x20) return(true);
#else
	if ((val == 0x20)												// ГXГyБ[ГX(Space)
//	|| (val == 0x00)												// NULL
	|| (val == 0x09)												// РЕХ╜Г^Гu(Horizontal tab)
	|| (val == 0x0A)												// Й№Нs(Line feed or New line)
	|| (val == 0x0D)) {												// ХЬЛA(Carriage return)
		return(true);
		}
#endif

	return(false);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВrВЛВЙВРВaВnВl                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BParseControl::SkipBOM(void)
{
	HRESULT		hResult;

	if (!Bytes()) {
		if (FAILED(hResult=Load(1))) return(hResult);
		}
	switch(BYTE(m_str[m_scope.end-1])) {
		case 0xEF :																		// UTF-8
			if ((hResult=Load(2)) != NOERROR) return(E_INVALIDARG);
			if (::memcmp(&m_str[m_scope.end-3], "\xEF\xBB\xBF", 3)) return(E_INVALIDARG);
			Empty();
			break;
#if 0
		case 0xFE :																		// UTF-16(Big Endian)
			if ((hResult=Load(1)) != NOERROR) return(E_INVALIDARG);
			if (::memcmp(&m_str[m_scope.end-2], "\xFE\xFF", 2)) return(E_INVALIDARG);
			Empty();
			return(E_INVALIDARG);
		case 0xFF :																		// UTF-16/UTF-32(Little Endian)
			if ((hResult=Load(1)) != NOERROR) return(E_INVALIDARG);
			if (::memcmp(&m_str[m_scope.end-2], "\xFF\xFE", 2)) return(E_INVALIDARG);
			Empty();
			if ((hResult=Load(1)) != NOERROR) return(E_INVALIDARG);
			if (BYTE(m_str[m_scope.end-1]) == '\x00') {									// UTF-32(Little Endian)
				if ((hResult=Load(1)) != NOERROR) return(E_INVALIDARG);
				if (::memcmp(&m_str[m_scope.end-2], "\x00\x00", 2)) return(E_INVALIDARG);
				Empty();
				}
			return(E_INVALIDARG);
		case 0x00 :																		// UTF-32(Big Endian)
			if ((hResult=Load(3)) != NOERROR) return(E_INVALIDARG);
			if (::memcmp(&m_str[m_scope.end-4], "\x00\x00\xFE\xFE", 4)) return(E_INVALIDARG);
			Empty();
			return(E_INVALIDARG);
		case 0x2B :																		// UTF-7
			if ((hResult=Load(2)) != NOERROR) return(E_INVALIDARG);
			if (::memcmp(&m_str[m_scope.end-3], "\x2B\x2F\x76", 3)) return(E_INVALIDARG);
			Empty();
			return(E_INVALIDARG);
#endif
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                       ВrВЛВЙВРВvВИВЙВФВЕВУВРВБВГВЕ                        */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BParseControl::SkipWhitespace(void)
{
	HRESULT		hResult;

	if (!Bytes()) {
		if (FAILED(hResult=Load(1))) return(hResult);
		}
	while(IsWhiteSpace(BYTE(m_str[m_scope.end-1]))) {
		Empty();
		if ((hResult=Load(1)) != NOERROR) return(E_INVALIDARG);
		}

	return(NOERROR);
}

#endif	// _BParseControl_H_
