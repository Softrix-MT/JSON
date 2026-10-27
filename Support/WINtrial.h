#ifndef _WINtrial_H_
#define _WINtrial_H_

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

/*****************************************************************************/
/*                             エラーコード定義                              */
/*****************************************************************************/
#define E_ELEMENT_NOTFOUND			HRESULT_FROM_WIN32(ERROR_NOT_FOUND)

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
#define isMAX(a, b)					(((a) > (b)) ? (a) : (b)) 
#define isMIN(a, b)					(((a) < (b)) ? (a) : (b)) 
#define memOPTIMUM(n)				((((size_t)(n) / sizeof(size_t)) + 1) * sizeof(size_t))

#define UNI(ch)						L##ch

#if (_MSC_VER <= 1310)											// Visual C++ 7.1 (Visual Studio.NET 2003)
#define _countof(array)				(sizeof(array)/sizeof(array[0]))
#endif	// _MSC_VER <= 1310

typedef ULONGLONG					QWORD;

/*****************************************************************************/
/*                                 関数定義                                  */
/*****************************************************************************/
#if (_MSC_VER <= 1310)											// Visual C++ 7.1 (Visual Studio.NET 2003)
// _stprintf
inline int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...)
{
	va_list	arg;
	va_start(arg, format);
	int result=::vsprintf(buffer, format, arg);
	va_end(arg);
	return(result);
}
inline int swprintf_s(wchar_t *buffer, size_t sizeOfBuffer, const wchar_t *format, ...)
{
	va_list	arg;
	va_start(arg, format);
	int result=::vswprintf(buffer, format, arg);
	va_end(arg);
	return(result);
}
// strncpy
inline void strncpy_s(char *dst, size_t size, const char *src, size_t count) { ::strncpy(dst, src, count); }
inline void wcsncpy_s(wchar_t *dst, size_t size, const wchar_t *src, size_t count) { ::wcsncpy(dst, src, count); }

#ifndef _UNICODE
	#define _stprintf_s				sprintf_s
	#define _tcsncpy_s				strncpy_s
#else
	#define _stprintf_s				swprintf_s
	#define _tcsncpy_s				wcsncpy_s
#endif

#endif	// _MSC_VER <= 1310

#endif

