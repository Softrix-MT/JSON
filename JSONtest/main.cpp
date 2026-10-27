#include <JSONtrial.h>
#include <shlwapi.h>
#include <string.h>

#include <limits.h>
#include <float.h>

#pragma comment(lib, "shlwapi.lib")

/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class XFileStream : public ISequentialStream {
	protected:
		HANDLE						m_hFile;

	public:
									XFileStream(void) { m_hFile=NULL; }
		virtual						~XFileStream(void) {}

	public:
		virtual HRESULT				Open(LPCTSTR szPath) {
			Close();

			m_hFile = ::CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE) {
				m_hFile = NULL;
				return(HRESULT_FROM_WIN32(::GetLastError()));
				}

			return(NOERROR);
		}
		virtual void				Close(void) {
			if (m_hFile != NULL) ::CloseHandle(m_hFile);
			m_hFile = NULL;
		}

	public:
// IUnknown ﾒｿｯﾄﾞ
		STDMETHODIMP				QueryInterface(REFIID riID, void** ppvobj) { return(E_NOTIMPL); }
		STDMETHODIMP_(ULONG)		AddRef(void) { return(E_NOTIMPL); }
		STDMETHODIMP_(ULONG)		Release(void) { return(E_NOTIMPL); }
// ISequentialStream ﾒｿｯﾄﾞ
		STDMETHODIMP				Read(LPVOID pvbuf, ULONG cbSize, ULONG* pcbRead) {
			ULONG	nBytes;

			if (!pcbRead) pcbRead = &nBytes;
			if (!::ReadFile(m_hFile, pvbuf, cbSize, pcbRead, NULL)) return(HRESULT_FROM_WIN32(::GetLastError()));

			return((cbSize == *pcbRead) ? NOERROR : S_FALSE);
		}
		STDMETHODIMP				Write(LPCVOID pvbuf, ULONG cbSize, ULONG* pcbWritten) {
			ULONG	nBytes;

			if (!pcbWritten) pcbWritten = &nBytes;
			if (!::WriteFile(m_hFile, pvbuf, cbSize, pcbWritten, NULL)) return(HRESULT_FROM_WIN32(::GetLastError()));
			return(NOERROR);
		}
};

/*****************************************************************************/
/*                                コード領域                                 */
/*****************************************************************************/
static HRESULT OnTextLoad(void)
{
	JSONAnchorPtr<JSONDocument>	pjson;
	LPCSTR						str="{ \"name\" : \"ABCDEF\", \"data\" : [ \"A\\uD800\\uDC01B\" , 12345 ], \"age\" : 12345.54321E-2 }  ";
	TCHAR						path[MAX_PATH];
	HRESULT						hResult;

	if (FAILED(hResult=::JSONLoadString(str, &pjson))) return(hResult);
	if (FAILED(hResult=pjson->SetProperty(JSONProperty_Indent, TRUE))) return(hResult);

	::memset(path, 0, sizeof(path));
	if (GetModuleFileName(NULL, path, _countof(path))) {
		XFileStream		file;

		PathRemoveFileSpec(path);
		strcat(path, "\\JSON_OnTextLoad.json");

		if (FAILED(hResult=file.Open(path))) return(hResult);
		if (FAILED(hResult=pjson->Write(&file))) return(hResult);
		}

	return(NOERROR);
}

static HRESULT OnCreateNode(void)
{
	JSONAnchorPtr<JSONDocument>	pjson;
	JSONAnchorPtr<JSONObject>	proot;
	JSONAnchorPtr<JSONString>	pstr;
	JSONAnchorPtr<JSONNumber>	pnum;
	TCHAR						path[MAX_PATH];
	HRESULT						hResult;

	if (FAILED(hResult=::JSONCreateDocument(&pjson))) return(hResult);
	if (FAILED(hResult=pjson->SetProperty(JSONProperty_Indent, TRUE))) return(hResult);

	if (FAILED(hResult=pjson->CreateNode(JSONNodeType_Object, proot))) return(hResult);

	if (FAILED(hResult=proot->CreateNode(JSONNodeType_String, "key1", pstr))) return(hResult);
	if (FAILED(hResult=pstr->set_UTF16(UNI("value1"), -1))) return(hResult);
	pstr.Destroy();

	if (FAILED(hResult=proot->CreateNode(JSONNodeType_String, "key2", pstr))) return(hResult);
	if (FAILED(hResult=pstr->set_ACP("value2", -1))) return(hResult);
	pstr.Destroy();

	if (FAILED(hResult=proot->CreateNode(JSONNodeType_Number, "key3", pnum))) return(hResult);
	pnum->set_Double(0.00000000000000123456789);
	pnum.Destroy();

	proot.Destroy();
	::memset(path, 0, sizeof(path));
	if (GetModuleFileName(NULL, path, _countof(path))) {
		XFileStream		file;

		PathRemoveFileSpec(path);
		strcat(path, "\\JSON_OnCreateNode.json");

		if (FAILED(hResult=file.Open(path))) return(hResult);
		if (FAILED(hResult=pjson->Write(&file))) return(hResult);
		}

	return(NOERROR);
}

int main()
{
	HRESULT		hResult;

	if (FAILED(hResult=OnTextLoad())) return(hResult);
	if (FAILED(hResult=OnCreateNode())) return(hResult);

    return 0;
}
