#include "../INCLUDE/StdHead.h"

#include "../INCLUDE/CJSONValue.h"
#include <math.h>

#include <limits.h>
#include <float.h>

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
CJSONValue::CJSONValue(JSONAnchor* pobj) : VJSONMember(pobj)
{
	m_node = JSONNodeType_I8;

	m_bool = false;
	m_num.lVal = 0;
	m_num.dblVal = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONValue::~CJSONValue(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВЗВЕВФБQВrВФВТВЙВОВЗ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
LPCSTR CJSONValue::get_String(void)
{
	if (m_node != JSONNodeType_String) return(NULL);

	return(m_str);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВУВЕВФБQВtВsВeВW                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::set_UTF8(LPCSTR str, size_t bytes)
{
	HRESULT		hResult;

	if (!str) {
		m_node = JSONNodeType_Null;
		return(NOERROR);
		}
	if (FAILED(hResult=m_str.set_UTF8(str, bytes))) return(hResult);
	
	m_node = ((::strlen(m_str)) ? JSONNodeType_String : JSONNodeType_Null);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                            ВУВЕВФБQВtВsВeВPВU                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::set_UTF16(LPCWSTR str, size_t length)
{
	HRESULT		hResult;

	if (!str) {
		m_node = JSONNodeType_Null;
		return(NOERROR);
		}
	if (FAILED(hResult=m_str.set_UTF16(str, length))) return(hResult);
	
	m_node = ((::strlen(m_str)) ? JSONNodeType_String : JSONNodeType_Null);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВУВЕВФБQВbВo                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::set_CP(UINT cp, LPCSTR str, size_t bytes)
{
	HRESULT		hResult;

	if (!str) {
		m_node = JSONNodeType_Null;
		return(NOERROR);
		}
	if (FAILED(hResult=m_str.set_CP(cp, str, bytes))) return(hResult);
	
	m_node = ((::strlen(m_str)) ? JSONNodeType_String : JSONNodeType_Null);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВУВЕВФБQВkВПВОВЗ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void CJSONValue::set_Long(LONGLONG val)
{
	m_num.lVal = val;
	m_node = JSONNodeType_I8;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВУВЕВФБQВcВПВХВВВМВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void CJSONValue::set_Double(double val)
{
	m_num.dblVal = val;
	m_node = JSONNodeType_R4;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВУВЕВФБQВaВПВПВМ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void CJSONValue::set_Bool(bool val)
{
	m_bool = val;
	m_node = JSONNodeType_Bool;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВmВПВДВЕВrВЙВЪВЕ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
int CJSONValue::NodeSize(void)
{
	if ((m_node != JSONNodeType_Object) && (m_node != JSONNodeType_Array)) return(0);

	return(m_list.NodeSize());
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВmВПВДВЕ                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::Node(int index, void** ppvobj)
{
	if ((m_node != JSONNodeType_Object) && (m_node != JSONNodeType_Array)) return(E_INVALIDARG);

	return(m_list.Node(index, ppvobj));
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВqВЕВНВПВЦВЕВmВПВДВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void CJSONValue::RemoveNode(int index)
{
	if ((m_node == JSONNodeType_Object)
	|| (m_node == JSONNodeType_Array)) {
		m_list.RemoveNode(index);
		}
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВbВТВЕВБВФВЕВmВПВДВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::CreateNode(JSONNodeType type, void** ppobj, LPCSTR key)
{
	JSONAnchorPtr<JSONValue>	pnode;
	VJSONMember*				pmem;
	HRESULT						hResult;

	if ((m_node != JSONNodeType_Object) && (m_node != JSONNodeType_Array)) return(E_INVALIDARG);
	if (m_node == JSONNodeType_Object) {
		if ((!key) || (!::strlen(key))) return(E_INVALIDARG);
//		if (FindNode(key) != -1) return(E_INVALIDARG);
		}

	if (FAILED(hResult=m_list.Create(m_pobjCounter, type, pnode, &pmem))) return(hResult);
	if (m_node == JSONNodeType_Object) {
		if (FAILED(hResult=pmem->set_Key(key))) return(hResult);
		}
	if (FAILED(hResult=m_list.AppendNode(pnode))) return(hResult);

	*ppobj = pnode.Detach();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВeВЙВОВДВmВПВДВЕ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
int CJSONValue::FindNode(LPCSTR key)
{
	if (m_node != JSONNodeType_Object) return(-1);
	return(m_list.FindNode(key));
}
HRESULT CJSONValue::FindNode(LPCSTR key, void** ppobj)
{
	if (m_node != JSONNodeType_Object) return(E_INVALIDARG);
	return(m_list.FindNode(key, ppobj));
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВjВЕВЩ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::Key(void** ppobj)
{
//	if (m_node != JSONNodeType_Object) return(E_INVALIDARG);
	return(VJSONMember::Key(ppobj));
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВoВБВТВУВЕВrВФВТВЙВОВЗ                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseString(BParseControl& stm)
{
	HRESULT		hResult;

	if (FAILED(hResult=m_str.Parse(stm))) return(hResult);

	m_node = JSONNodeType_String;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВoВБВТВУВЕВmВХВНВВВЕВТ                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseNumber(BParseControl& stm)
{
	bool			enable=true;
	bool			point=false;
	struct {
		bool	enable;
		bool	sign;
		long	val;
		}			exponent;
	struct {
		bool	sign;
		LONGLONG decimal;
		long	decExp;
		}			number;
	int				val;
	HRESULT			hResult;

	m_num.lVal = 0;
	m_num.dblVal = 0;

	exponent.enable = false;
	exponent.sign = false;
	exponent.val = 0;

	if (!stm.Bytes()) {
		if (FAILED(hResult=stm.Load(1))) return(hResult);
		}
// ХДНЖКmФF
	switch(stm.Value(0)) {
		case '-' :
			number.sign = false;
			stm.Empty();
			if (FAILED(hResult=stm.Load(1))) return(hResult);
			break;
		case '+' :
			number.sign = true;
			stm.Empty();
			if (FAILED(hResult=stm.Load(1))) return(hResult);
			break;
		default :
			number.sign = true;
			break;
		}
// ТlКmФF
	number.decimal = 0;
	number.decExp = 0;
	while(enable) {
		val = stm.Value(0);
		if (('0' <= val) && (val <= '9')) {
			stm.Empty();
			val -= '0';
			if (exponent.enable) {										// ОwРФХФ
				if (exponent.sign) {
					exponent.val = (exponent.val * 10) + val;
					if (DBL_MAX_10_EXP < exponent.val) break;
					}
				else{
					exponent.val = (exponent.val * 10) - val;
					if (exponent.val < DBL_MIN_10_EXP) break;
					}
				}
			else if (!point) {											// РоРФХФ
				if (number.sign) {
					if ((_I64_MAX/10) < m_num.lVal) break;
					if (((_I64_MAX/10) == m_num.lVal) && ((_I64_MAX%10) < val)) break;
					m_num.lVal = (m_num.lVal * 10) + val;
					}
				else{
					val *= -1;
					if (m_num.lVal < (_I64_MIN/10)) break;
					if ((m_num.lVal == (_I64_MIN/10)) && (val < (_I64_MIN%10))) break;
					m_num.lVal = (m_num.lVal * 10) + val;
					}
				}
			else{														// ПмРФХФ
				if ((_I64_MAX/10) < number.decimal) break;
				if (((_I64_MAX/10) == number.decimal) && ((_I64_MAX%10) < val)) break;
				number.decimal = (number.decimal * 10) + val;
				number.decExp--;
				}
			}
		else if (val == '.') {
			stm.Empty();
			if (exponent.enable) break;
			if (point) break;
			point = true;
			}
		else if ((val == 'e') || (val == 'E')) {
			stm.Empty();
			if (exponent.enable) break;
			exponent.enable = true;
			if (FAILED(hResult=stm.Load(1))) return(hResult);
			switch(stm.Value(0)) {
				case '-' :
					exponent.sign = false;
					stm.Empty();
					break;
				case  '+' :
					exponent.sign = true;
					stm.Empty();
					break;
				default :
					exponent.sign = true;
					break;
				}
			}
		else{
			enable = false;
			break;
			}
		if (!stm.Bytes()) {
			if (FAILED(hResult=stm.Load(1))) return(hResult);
			}
		}

	m_num.dblVal = (double)m_num.lVal;
	if ((point) && (number.decimal)) {
		m_node = JSONNodeType_R4;
		if (number.sign)
			m_num.dblVal += double(number.decimal) * ::pow(10., double(number.decExp));
		else
			m_num.dblVal -= double(number.decimal) * ::pow(10., double(number.decExp));
		}
	else
		m_node = JSONNodeType_I8;
	if (exponent.enable) {
		m_node = JSONNodeType_R4;
		m_num.dblVal *= ::pow(10., double(exponent.val));
		}

	if (enable) return(E_INVALIDARG);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВoВБВТВУВЕВ`ВТВТВБВЩ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseArray(BParseControl& stm)
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
			JSONAnchorPtr<JSONValue>	pnode;
			VJSONMember*				pmem;
			int							val;
// value
//			stm.Inc();
			if (FAILED(hResult=m_list.Parse(this, stm, pnode, &pmem))) return(hResult);
//			stm.Dec();
			pmem->EnableKey(false);
			if (FAILED(hResult=m_list.AppendNode(pnode))) return(hResult);
			pnode.Destroy();

			if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
			if ((val=stm.Value(0)) == ']') break;
			if (val != ',') return(E_INVALIDARG);
			stm.Empty();
			if (FAILED(hResult=stm.SkipWhitespace())) return(hResult);
			}
		}
	stm.Empty();

	m_node = JSONNodeType_Array;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВoВБВТВУВЕВnВВВКВЕВГВФ                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseObject(BParseControl& stm)
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
			JSONAnchorPtr<JSONValue>	pnode;
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
//			stm.Inc();
			if (FAILED(hResult=m_list.Parse(this, stm, pnode, &pmem))) return(hResult);
//			stm.Dec();
			BStringControl&		dst=pmem->KeyString();
			dst.Swap(src);
			pmem->EnableKey(true);
			if (FAILED(hResult=m_list.AppendNode(pnode))) return(hResult);
			pnode.Destroy();

			if (FAILED(hResult=stm.SkipWhitespace())) return(E_INVALIDARG);
			if ((val=stm.Value(0)) == '}') break;
			if (val != ',') return(E_INVALIDARG);
			stm.Empty();
			if (FAILED(hResult=stm.SkipWhitespace())) return(E_INVALIDARG);
			}
		}
	stm.Empty();

	m_node = JSONNodeType_Object;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                            ВoВБВТВУВЕВmВХВМВМ                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseNull(BParseControl& stm)
{
	stm.Empty();
	m_node = JSONNodeType_Null;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                            ВoВБВТВУВЕВsВТВХВЕ                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseTrue(BParseControl& stm)
{
	m_bool = true;
	stm.Empty();
	m_node = JSONNodeType_Bool;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВoВБВТВУВЕВeВБВМВУВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONValue::ParseFalse(BParseControl& stm)
{
	m_bool = false;
	stm.Empty();
	m_node = JSONNodeType_Bool;
	return(NOERROR);
}
