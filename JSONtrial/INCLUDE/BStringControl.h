#ifndef _BStringControl_H_
#define _BStringControl_H_
#include "../INCLUDE/BString.h"

#include "../INCLUDE/BParseControl.h"

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
class BStringControl : public BString {
	public:
									BStringControl(void);
		virtual						~BStringControl(void);

	protected:
		bool						IsWORD(LPCSTR const str);
		WORD						STRtoWORD(LPCSTR const str);
//		int							IsUTF16toUTF8(LPCSTR const str, size_t size, size_t* const putf8);
		int							IsUTF16toUTF8(BParseControl& stm, size_t* const putf8);
//		int							UTF16toUTF8(LPCSTR const str, size_t size, LPSTR* const ppout);
		int							UTF16toUTF8(BParseControl& stm, LPSTR* const ppout);

	public:
		virtual HRESULT				set_UTF8(LPCSTR str, size_t bytes=-1);
		virtual HRESULT				set_UTF16(LPCWSTR str, size_t length=-1);
		virtual HRESULT				set_CP(UINT cp, LPCSTR str, size_t bytes=-1);

	public:
		virtual void				Swap(BStringControl& val);
		virtual HRESULT				Parse(BParseControl& stm);
};

/*****************************************************************************/
/*                              ГCГУГЙГCГУТшЛ`                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВP                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВhВУВvВnВqВc                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline bool BStringControl::IsWORD(LPCSTR const str)
{
	size_t	nLoop;

	for(nLoop=0; nLoop<4; nLoop++) {
		if (!(('0' <= (BYTE)str[nLoop]) && ((BYTE)str[nLoop] <= '9'))
		&& (!('A' <= (BYTE)str[nLoop]) && ((BYTE)str[nLoop] <= 'F'))
		&& (!('a' <= (BYTE)str[nLoop]) && ((BYTE)str[nLoop] <= 'f'))) return(false);
		}

	return(true);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                            ВrВsВqВФВПВvВnВqВc                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline WORD BStringControl::STRtoWORD(LPCSTR const str)
{
	WORD	val=0;
	size_t	nLoop;

	for(nLoop=0; nLoop<4; nLoop++) {
		val <<= 4;

		if (('0' <= (BYTE)str[nLoop]) && ((BYTE)str[nLoop] <= '9')) val += (BYTE)str[nLoop] - '0';
		else if (('A' <= (BYTE)str[nLoop]) && ((BYTE)str[nLoop] <= 'F')) val += 10 + (BYTE)str[nLoop] - 'A';
		else if (('a' <= (BYTE)str[nLoop]) && ((BYTE)str[nLoop] <= 'f')) val += 10 + (BYTE)str[nLoop] - 'a';
		else return(0);
		}

	return(val);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                        ВhВУВtВsВeВPВUВФВПВtВsВeВW                         */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
inline int BStringControl::IsUTF16toUTF8(LPCSTR const str, size_t size, size_t* const putf8)
{
	DWORD	codepoint;
	UINT	tmp;
	int		length=0;

	if (size < 6) return(0);
	if (((BYTE)str[0] != '\\') || ((BYTE)str[1] != 'u')) return(0);

	if (!IsWORD(&str[2])) return(0);
	codepoint = STRtoWORD(&str[2]);
	if (((0xDC00 <= codepoint) && (codepoint <= 0xDFFF))) return(0);		// Й║И╩ГTГНГQБ[Гg
	length = 6;																// \uXXXX

	if ((0xD800 <= codepoint) && (codepoint <= 0xDBFF)) {					// ПуИ╩ГTГНГQБ[Гg
		if (size < 12) return(0);											// input ends unexpectedly
		length += 6;													// \uXXXX\uXXXX

		if (((BYTE)str[6] != '\\') || ((BYTE)str[7] != 'u')) return(0);
		if (!IsWORD(&str[8])) return(0);
		tmp = STRtoWORD(&str[8]);
		if ((tmp < 0xDC00) || (0xDFFF < tmp)) return(0);				// Й║И╩ГTГНГQБ[ГgИ╚КO

		codepoint = 0x10000 + (((codepoint & 0x03FF) << 10) | (tmp & 0x03FF));
		if (0x10FFFF < codepoint) return(0);
		}
	if (codepoint < 0x80) *putf8 += 1;						// normal ascii, encoding 0xxxxxxx
	else if (codepoint < 0x800) *putf8 += 2;				// two bytes, encoding 110xxxxx 10xxxxxx
	else if (codepoint < 0x10000) *putf8 += 3;				// three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx
	else if (codepoint <= 0x10FFFF) *putf8 += 4;			// four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx

	return(length);
}
*/
inline int BStringControl::IsUTF16toUTF8(BParseControl& stm, size_t* const putf8)
{
	DWORD		codepoint;
	int			length=0;
	HRESULT		hResult;
// \u
	if (stm.Bytes() < 2) return(0);
	if ((stm.Value(0) != '\\') || (stm.Value(1) != 'u')) return(0);
// \uXXXX
	if (stm.Bytes() < 6) {
		if ((hResult=stm.Load(6-stm.Bytes())) != NOERROR) return(0);
		}
	if (!IsWORD(stm.Buffer(2))) return(0);
	codepoint = STRtoWORD(stm.Buffer(2));
	if (((0xDC00 <= codepoint) && (codepoint <= 0xDFFF))) return(0);		// Й║И╩ГTГНГQБ[Гg
	length = 6;

	if ((0xD800 <= codepoint) && (codepoint <= 0xDBFF)) {					// ПуИ╩ГTГНГQБ[Гg
		UINT	tmp;
// \uXXXX\u
		if (stm.Bytes() < 8) {
			if ((hResult=stm.Load(8-stm.Bytes())) != NOERROR) return(0);
			}
		if ((stm.Value(6) != '\\') || (stm.Value(7) != 'u')) return(0);
// \uXXXX\uXXXX
		if (stm.Bytes() < 12) {
			if ((hResult=stm.Load(12-stm.Bytes())) != NOERROR) return(0);
			}
		if (!IsWORD(stm.Buffer(8))) return(0);
		tmp = STRtoWORD(stm.Buffer(8));
		if ((tmp < 0xDC00) || (0xDFFF < tmp)) return(0);				// Й║И╩ГTГНГQБ[ГgИ╚КO

		codepoint = 0x10000 + (((codepoint & 0x03FF) << 10) | (tmp & 0x03FF));
		if (0x10FFFF < codepoint) return(0);
		length += 6;
		}
	if (codepoint < 0x80) *putf8 += 1;						// normal ascii, encoding 0xxxxxxx
	else if (codepoint < 0x800) *putf8 += 2;				// two bytes, encoding 110xxxxx 10xxxxxx
	else if (codepoint < 0x10000) *putf8 += 3;				// three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx
	else if (codepoint <= 0x10FFFF) *putf8 += 4;			// four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx

	return(length);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВtВsВeВPВUВФВПВtВsВeВW                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
inline int BStringControl::UTF16toUTF8(LPCSTR const str, size_t size, LPSTR* const ppout)
{
	LPSTR		pdst=*ppout;
	DWORD		codepoint=0;
	BYTE		markUTF8;
	int			lenUTF8, length;
	UINT		tmp;
	int			nLoop;

	if (size < 6) return(0);
//	if (((BYTE)str[0] != '\\') || ((BYTE)str[1] != 'u')) return(0);

//	if (!IsWORD(&str[2])) return(0);
	codepoint = STRtoWORD(&str[2]);
	length = 6;															// \uXXXX

//	if (((0xDC00 <= codepoint) && (codepoint <= 0xDFFF))) return(0);	// Й║И╩ГTГНГQБ[Гg
	if ((0xD800 <= codepoint) && (codepoint <= 0xDBFF)) {				// ПуИ╩ГTГНГQБ[Гg
		if (size < 12) return(0);										// input ends unexpectedly
		length += 6;													// \uXXXX\uXXXX

//		if (((BYTE)str[6] != '\\') || ((BYTE)str[7] != 'u')) return(0);
//		if (!IsWORD(&str[8])) return(0);
		tmp = STRtoWORD(&str[8]);
//		if ((tmp < 0xDC00) || (0xDFFF < tmp)) return(0);				// Й║И╩ГTГНГQБ[ГgИ╚КO

		codepoint = 0x10000 + (((codepoint & 0x03FF) << 10) | (tmp & 0x03FF));
		}
//	if (0x10FFFF < codepoint) return(0);
	if (codepoint < 0x80) {												// normal ascii, encoding 0xxxxxxx
		lenUTF8 = 1;
		}
	else if (codepoint < 0x800) {										// two bytes, encoding 110xxxxx 10xxxxxx
		lenUTF8 = 2;
		markUTF8 = 0xC0;												// 11000000
		}
	else if (codepoint < 0x10000) {										// three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx
		lenUTF8 = 3;
		markUTF8 = 0xE0;												// 11100000
		}
	else if (codepoint <= 0x10FFFF) {									// four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx
		lenUTF8 = 4;
		markUTF8 = 0xF0;												// 11110000
		}
	else{
		return(0);														// invalid unicode codepoint
		}
// encode as utf8
	for(nLoop=(lenUTF8-1); nLoop>0; nLoop--) {
		// 10xxxxxx
		pdst[nLoop] = (BYTE)(0x80 | (codepoint & 0x3F));
		codepoint >>= 6;
		}
// encode first byte
	if (1 < lenUTF8)
		pdst[0] = (BYTE)((codepoint | markUTF8) & 0xFF);
	else
		pdst[0] = (BYTE)(codepoint & 0x7F);

	*ppout = &pdst[lenUTF8];
	return(length);
}
*/
inline int BStringControl::UTF16toUTF8(BParseControl& stm, LPSTR* const ppout)
{
	LPSTR		pdst=*ppout;
	DWORD		codepoint=0;
	BYTE		markUTF8;
	int			lenUTF8, length;
	UINT		tmp;
	int			nLoop;

	if (stm.Bytes() < 6) return(0);
//	if ((stm.Value(0) != '\\') || (stm.Value(1) != 'u')) return(0);

//	if (!IsWORD(stm.Buffer(2))) return(0);
	codepoint = STRtoWORD(stm.Buffer(2));
	length = 6;															// \uXXXX

//	if (((0xDC00 <= codepoint) && (codepoint <= 0xDFFF))) return(0);	// Й║И╩ГTГНГQБ[Гg
	if ((0xD800 <= codepoint) && (codepoint <= 0xDBFF)) {				// ПуИ╩ГTГНГQБ[Гg
		if (stm.Bytes() < 12) return(0);								// input ends unexpectedly
		length += 6;													// \uXXXX\uXXXX

//		if ((stm.Value(6) != '\\') || (stm.Value(7) != 'u')) return(0);
//		if (!IsWORD(stm.Buffer(8))) return(0);
		tmp = STRtoWORD(stm.Buffer(8));
//		if ((tmp < 0xDC00) || (0xDFFF < tmp)) return(0);				// Й║И╩ГTГНГQБ[ГgИ╚КO

		codepoint = 0x10000 + (((codepoint & 0x03FF) << 10) | (tmp & 0x03FF));
		}
//	if (0x10FFFF < codepoint) return(0);
	if (codepoint < 0x80) {												// normal ascii, encoding 0xxxxxxx
		lenUTF8 = 1;
		}
	else if (codepoint < 0x800) {										// two bytes, encoding 110xxxxx 10xxxxxx
		lenUTF8 = 2;
		markUTF8 = 0xC0;												// 11000000
		}
	else if (codepoint < 0x10000) {										// three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx
		lenUTF8 = 3;
		markUTF8 = 0xE0;												// 11100000
		}
	else if (codepoint <= 0x10FFFF) {									// four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx
		lenUTF8 = 4;
		markUTF8 = 0xF0;												// 11110000
		}
	else{
		return(0);														// invalid unicode codepoint
		}
// encode as utf8
	for(nLoop=(lenUTF8-1); nLoop>0; nLoop--) {
		// 10xxxxxx
		pdst[nLoop] = (BYTE)(0x80 | (codepoint & 0x3F));
		codepoint >>= 6;
		}
// encode first byte
	if (1 < lenUTF8)
		pdst[0] = (BYTE)((codepoint | markUTF8) & 0xFF);
	else
		pdst[0] = (BYTE)(codepoint & 0x7F);

	*ppout = &pdst[lenUTF8];
	return(length);
}

/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline BStringControl::BStringControl(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline BStringControl::~BStringControl(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВУВЕВФБQВtВsВeВW                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BStringControl::set_UTF8(LPCSTR str, size_t bytes)
{
	HRESULT		hResult;

	if (!str) str = "";
	if (bytes == size_t(-1)) bytes = ::strlen(str);

	if (FAILED(hResult=Reallocation(bytes+sizeof("")))) return(hResult);
	if (bytes) ::strncpy_s(m_str, (bytes+1), str, bytes);
	m_str[bytes] = NULL;

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                            ВУВЕВФБQВtВsВeВPВU                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BStringControl::set_UTF16(LPCWSTR str, size_t length)
{
const DWORD		flags=0;
	int			tail;
	HRESULT		hResult;

	if (!str) str = UNI("");
	if (length == size_t(-1)) length = ::wcslen(str);

	tail = ::WideCharToMultiByte(CP_UTF8, flags, str, int(length), NULL, 0, NULL, NULL);
	if (FAILED(hResult=Reallocation(tail+sizeof("")))) return(hResult);
	m_str[0] = NULL;

	if (tail) {
		if (!::WideCharToMultiByte(CP_UTF8, flags, str, int(length), m_str, tail, NULL, NULL)) return(NULL);
		m_str[tail] = NULL;
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВУВЕВФБQВbВo                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BStringControl::set_CP(UINT cp, LPCSTR str, size_t bytes)
{
//const DWORD		flags=(((cp == CP_UTF8) || (cp == CP_SYMBOL)) ? 0 : WC_DEFAULTCHAR);
const DWORD		flags=0;
	int			tail;
	LPWSTR		wide;
	HRESULT		hResult;

	if (cp == CP_UTF8) return(set_UTF8(str, bytes));

	if (!str) str = "";
	if (bytes == size_t(-1)) bytes = ::strlen(str);

	tail = ::MultiByteToWideChar(cp, flags, str, int(bytes), NULL, 0);
	if ((wide=LPWSTR(Reallocation(NULL, ((tail+sizeof(""))*sizeof(wchar_t))))) == NULL) return(E_OUTOFMEMORY);
	if (tail) {
		if (!::MultiByteToWideChar(cp, flags, str, int(bytes), wide, tail)) {
			DWORD	err=::GetLastError();
			::free(wide);
			return(HRESULT_FROM_WIN32(err));
			}
		}
	hResult = set_UTF16(wide, tail);
	::free(wide);

	return(hResult);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВrВЧВБВР                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void BStringControl::Swap(BStringControl& val)
{
	LPSTR		str=val.m_str;
	size_t		bytes=val.m_bytes;

	val.m_str = m_str;
	val.m_bytes = m_bytes;

	m_str = str;
	m_bytes = bytes;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВoВБВТВУВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT BStringControl::Parse(BParseControl& stm)
{
	LPSTR		pdst;
	int			val, len;
	size_t		index, size=0, alloc=0;
	HRESULT		hResult;

// Start Check
	if (!stm.Bytes()) {
		if (FAILED(hResult=stm.Load(1))) return(hResult);
		}
	if (stm.Value(size++) != '\"') return(E_INVALIDARG);

	if (stm.Bytes() <= 1) {
		if (FAILED(hResult=stm.Load((size+1)-stm.Bytes()))) return(hResult);
		}
// End Search & Allocation size calculate
	while((val=stm.Value(size)) != '\"') {
		if (val != '\\') {
			alloc++;
			size++;
			}
		else{															// ESCAPE SEQUENCE
			if (stm.Bytes() <= size) return(E_INVALIDARG);
			if (FAILED(hResult=stm.Load(1))) return(hResult);
			switch(stm.Value(size+1)) {
				case 'b':
				case 'f':
				case 'n':
				case 'r':
				case 't':
				case '\"':
				case '\\':
				case '/':
					alloc++;
					size += 2;
					break;
				case 'u':
					stm.Beginning(size);
					if ((len=IsUTF16toUTF8(stm, &alloc)) == 0) return(E_INVALIDARG);
					stm.Beginning(0);
					size += len;
					break;
				default:
					return(E_INVALIDARG);
				}
			}
		if (stm.Bytes() < (size+1)) {
			if (FAILED(hResult=stm.Load((size+1)-stm.Bytes()))) return(hResult);
			}
		}
//	if (stm.Value(size) != '\"') return(E_INVALIDARG);
	size++;

// Allocation
	if (FAILED(hResult=Reallocation(alloc+sizeof("")))) return(hResult);
	pdst = m_str;
// Copy
	for(index=1; index<(size-1); ) {
		if ((val=stm.Value(index)) != '\\') {
			*pdst++ = val;
			index++;
			}
		else{															// ESCAPE SEQUENCE
			val = stm.Value(index+1);
			if (val != 'u') {
				index++;
				switch(val) {
					case 'b': *pdst++ = '\b'; break;
					case 'f': *pdst++ = '\f'; break;
					case 'n': *pdst++ = '\n'; break;
					case 'r': *pdst++ = '\r'; break;
					case 't': *pdst++ = '\t'; break;
					case '\"':
					case '\\':
					case '/':
						*pdst++ = stm.Value(index+1);
						break;
					}
				}
			else{
				stm.Beginning(index);
				if ((len=UTF16toUTF8(stm, &pdst)) == 0) return(E_INVALIDARG);
				index += len;
				stm.Beginning(0);
				}
			}
		}
	*pdst = '\0';
	stm.Empty();

	return(NOERROR);
}

#endif	// _BStringControl_H_
