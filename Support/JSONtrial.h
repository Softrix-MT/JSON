#ifndef _JSONtrial_H_
#define _JSONtrial_H_
#include <WINtrial.h>

/*****************************************************************************/
/*                                ГIГvГVГЗГУ                                 */
/*****************************************************************************/
#ifndef JSONLIBRARY
	#ifndef _WIN64
		#ifndef _DEBUG
			#if (_MSC_VER <= 1200)								// VC++ 6.0
				#pragma comment(lib, "JSONtri06x86.lib")
	//		#elif (_MSC_VER <= 1300)							// VC++ 7.0
	//		#elif (_MSC_VER <= 1310)							// VC++ 7.1
	//		#elif (_MSC_VER <= 1400)							// VC++ 8.0
	//		#elif (_MSC_VER <= 1500)							// VC++ 9.0
			#elif (_MSC_VER <= 1600)							// VC++ 10.0
				#pragma comment(lib, "JSONtri10x86.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "JSONtri10x86.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
			#endif
		#else
			#if (_MSC_VER <= 1200)								// VC++ 6.0
				#pragma comment(lib, "JSONtri06x86d.lib")
	//		#elif (_MSC_VER <= 1300)							// VC++ 7.0
	//		#elif (_MSC_VER <= 1310)							// VC++ 7.1
	//		#elif (_MSC_VER <= 1400)							// VC++ 8.0
	//		#elif (_MSC_VER <= 1500)							// VC++ 9.0
			#elif (_MSC_VER <= 1600)							// VC++ 10.0
				#pragma comment(lib, "JSONtri10x86d.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "JSONtriE2x86d.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "JSONtriE2x86d.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
			#endif
		#endif
	#else
		#ifndef _DEBUG
			#if (_MSC_VER <= 1600)								// VC++ 10.0
				#pragma comment(lib, "JSONtri10x64.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "JSONtriE2x64.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "JSONtriE2x64.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
			#endif
		#else
			#if (_MSC_VER <= 1600)								// VC++ 10.0
				#pragma comment(lib, "JSONtri10x64d.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "JSONtriE2x64d.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "JSONtriE2x64d.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
			#endif
		#endif
	#endif
#endif

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
typedef enum JSONNodeType {
//		JSONNodeType_None		= 0x0000,
		JSONNodeType_Object		= 0x0010,
		JSONNodeType_Array		= 0x0020,
		JSONNodeType_String		= 0x0030,
		JSONNodeType_Null		= 0x0031,
		JSONNodeType_Number		= 0x0040,
		JSONNodeType_I8			= 0x0041,						// LONGLONG
		JSONNodeType_R4			= 0x0042,						// double
		JSONNodeType_Bool		= 0x0050,
		} JSONNodeType;

#define IsJSONNodeType(n)			(n&0xFFF0)

typedef enum JSONProperty {
		JSONProperty_Indent			= 1,
		JSONProperty_NewLine		= ( JSONProperty_Indent + 1 ) ,
#if 0
		JSONProperty_ByteOrderMark	= ( JSONProperty_NewLine + 1 ) ,
		_JSONProperty_Last			= JSONProperty_ByteOrderMark,
#else
		_JSONProperty_Last			= JSONProperty_NewLine ,
#endif
		} JSONProperty;

/*****************************************************************************/
/*                                Н\СвС╠ТшЛ`                                 */
/*****************************************************************************/
// SHCreateStreamOnFile
// CreateStreamOnHGlobal
/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
#if defined(__cplusplus) && !defined(CINTERFACE)

/*---------------------------------------------------------------------------*/
/*                           ВiВrВnВmВ`ВОВГВИВПВТ                            */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONAnchor {
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
		} JSONAnchor;

/*---------------------------------------------------------------------------*/
/*                             ВiВrВnВmВmВПВДВЕ                              */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONNode {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONNode
		virtual JSONNodeType		IsNodeType(void) = 0;
		virtual HRESULT				Key(void** ppobj) = 0;
		} JSONNode;

/*---------------------------------------------------------------------------*/
/*                           ВiВrВnВmВrВФВТВЙВОВЗ                            */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONString {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONNode
		virtual JSONNodeType		IsNodeType(void) = 0;
		virtual HRESULT				Key(void** ppobj) = 0;
// JSONString
		virtual LPCSTR				get_String(void) = 0;					// UTF-8
		virtual HRESULT				set_String(LPCSTR str) = 0;				// UTF-8

		virtual HRESULT				set_UTF8(LPCSTR str, size_t bytes) = 0;
		virtual HRESULT				set_UTF16(LPCWSTR str, size_t length) = 0;
		virtual HRESULT				set_CP(UINT CodePage, LPCSTR str, size_t bytes) = 0;
		virtual HRESULT				set_ACP(LPCSTR str, size_t bytes) = 0;
		} JSONString;

/*---------------------------------------------------------------------------*/
/*                           ВiВrВnВmВmВХВНВВВЕВТ                            */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONNumber {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONNode
		virtual JSONNodeType		IsNodeType(void) = 0;
		virtual HRESULT				Key(void** ppobj) = 0;
// JSONNumber
		virtual LONGLONG			get_Long(void) = 0;
		virtual void				set_Long(LONGLONG val) = 0;
		virtual double				get_Double(void) = 0;
		virtual void				set_Double(double val) = 0;
		} JSONNumber;

/*---------------------------------------------------------------------------*/
/*                             ВiВrВnВmВaВПВПВМ                              */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONBool {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONNode
		virtual JSONNodeType		IsNodeType(void) = 0;
		virtual HRESULT				Key(void** ppobj) = 0;
// JSONBool
		virtual bool				get_Bool(void) = 0;
		virtual void				set_Bool(bool val) = 0;
		} JSONBool;

/*---------------------------------------------------------------------------*/
/*                            ВiВrВnВmВ`ВТВТВБВЩ                             */
/*---------------------------------------------------------------------------*/
typedef struct tsgJSONArray {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONNode
		virtual JSONNodeType		IsNodeType(void) = 0;
		virtual HRESULT				Key(void** ppobj) = 0;
// JSONArray
		virtual int					NodeSize(void) = 0;
		virtual HRESULT				Node(int index, void** ppobj) = 0;

		virtual HRESULT				CreateNode(JSONNodeType type, void** ppobj) = 0;
		virtual void				RemoveNode(int index) = 0;
		} JSONArray;

/*---------------------------------------------------------------------------*/
/*                           ВiВrВnВmВnВВВКВЕВГВФ                            */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONObject {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONNode
		virtual JSONNodeType		IsNodeType(void) = 0;
		virtual HRESULT				Key(void** ppobj) = 0;
// JSONObject
		virtual int					NodeSize(void) = 0;
		virtual HRESULT				Node(int index, void** ppobj) = 0;

		virtual HRESULT				CreateNode(JSONNodeType type, LPCSTR key, void** ppobj) = 0;
		virtual HRESULT				FindNode(LPCSTR key, void** ppobj) = 0;
		virtual void				RemoveNode(LPCSTR key) = 0;
		} JSONObject;

/*---------------------------------------------------------------------------*/
/*                         ВiВrВnВmВcВПВГВХВНВЕВОВФ                          */
/*---------------------------------------------------------------------------*/
typedef struct tagJSONDocument {
// JSONAnchor
		virtual ULONG				Keep(void) = 0;
		virtual ULONG				Discard(void) = 0;
// JSONDocument
		virtual HRESULT				CreateNode(JSONNodeType type, void** ppobj) = 0;
		virtual HRESULT				Node(void** ppobj) = 0;

		virtual HRESULT				SetProperty(JSONProperty prop, BOOL enable) = 0;
		virtual HRESULT				SetPropertyChars(JSONProperty prop, LPCSTR str) = 0;

		virtual HRESULT				Read(ISequentialStream* pobj) = 0;
		virtual HRESULT				Write(ISequentialStream* pobj) = 0;
		} JSONDocument;

/*---------------------------------------------------------------------------*/
/*                        ВiВrВnВmВ`ВОВГВИВПВТВoВФВТ                         */
/*---------------------------------------------------------------------------*/
template <class TYPE>
class JSONAnchorPtr {
	protected:
		TYPE*						m_pObject;

	public:
									JSONAnchorPtr(void);
									JSONAnchorPtr(TYPE* pobj);
									JSONAnchorPtr(const JSONAnchorPtr<TYPE>& obj);
		virtual						~JSONAnchorPtr(void);

	public:
									operator void**() { return((void**)&m_pObject); }
									operator TYPE*() const { return(m_pObject); }
		TYPE*						operator->(void) const { return(m_pObject); }
		TYPE&						operator*(void) const { return(*m_pObject); }
		TYPE**						operator&(void) { return(&m_pObject); }
		TYPE*						operator=(TYPE* pobj) { HRESULT h=Attach(pobj); return((h==NOERROR) ? m_pObject : NULL); }
		TYPE*						operator=(const JSONAnchorPtr<TYPE>& obj) { HRESULT h=Attach(obj); return((h==NOERROR) ? m_pObject : NULL); }

	public:
		bool						IsNull(void) { return(m_pObject == NULL); }

	public:
		virtual HRESULT				Attach(TYPE* pobj);
		virtual TYPE*				Detach(void);
		virtual void				Destroy(void);
};

/*****************************************************************************/
/*                              ГCГУГЙГCГУТшЛ`                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                        ВiВrВnВmВ`ВОВГВИВПВТВoВФВТ                         */
/*                                ВbВkВ`ВrВr                                 */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template <class TYPE>
inline JSONAnchorPtr<TYPE>::JSONAnchorPtr(void)
{
	m_pObject = NULL;
}
template <class TYPE>
inline JSONAnchorPtr<TYPE>::JSONAnchorPtr(TYPE* pobj)
{
	m_pObject = pobj;
	if (m_pObject != NULL) m_pObject->Keep();
}
template <class TYPE>
inline JSONAnchorPtr<TYPE>::JSONAnchorPtr(const JSONAnchorPtr<TYPE>& obj)
{
	m_pObject = obj.m_pObject;
	if (m_pObject != NULL) m_pObject->Keep();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template <class TYPE>
inline JSONAnchorPtr<TYPE>::~JSONAnchorPtr(void)
{
	if (m_pObject) m_pObject->Discard();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               В`ВФВФВБВГВИ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template <class TYPE>
inline HRESULT JSONAnchorPtr<TYPE>::Attach(TYPE* pobj)
{
	Destroy();
	if (pobj != NULL) {
		m_pObject = pobj;
		m_pObject->Keep();
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВcВЕВФВБВГВИ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template <class TYPE>
inline TYPE* JSONAnchorPtr<TYPE>::Detach(void)
{
	TYPE*	pobj=m_pObject;

	m_pObject = NULL;
	return(pobj);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВcВЕВУВФВТВПВЩ                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
template <class TYPE>
inline void JSONAnchorPtr<TYPE>::Destroy(void)
{
	if (m_pObject) {
		m_pObject->Discard();
		m_pObject = NULL;
		}
}

#endif	// defined(__cplusplus) && !defined(CINTERFACE)

/*****************************************************************************/
/*                                Г}ГNГНТшЛ`                                 */
/*****************************************************************************/
#define JSONDiscard(p)		{ if (p!=NULL) { p->Discard(); p=NULL; } }

/*****************************************************************************/
/*                                 К╓РФТшЛ`                                  */
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

HRESULT		JSONCreateDocument(JSONDocument** ppjson);
HRESULT		JSONLoadStream(ISequentialStream* pstm, JSONDocument** ppjson);
HRESULT		JSONLoadString(LPCSTR str, JSONDocument** ppvobj);

#ifdef __cplusplus
}
#endif

#endif	// _JSONtrial_H_
