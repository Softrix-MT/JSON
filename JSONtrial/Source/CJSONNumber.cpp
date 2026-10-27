#include "../INCLUDE/StdHead.h"

#include "../INCLUDE/CJSONNumber.h"
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
CJSONNumber::CJSONNumber(JSONAnchor* pobj) : VJSONMember(pobj)
{
	m_node = JSONNodeType_I8;
	m_val.lVal = 0;
	m_val.dblVal = 0;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
CJSONNumber::~CJSONNumber(void)
{
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВУВЕВФБQВkВПВОВЗ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void CJSONNumber::set_Long(LONGLONG val)
{
	m_node = JSONNodeType_I8;
	m_val.lVal = val;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВУВЕВФБQВcВПВХВВВМВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void CJSONNumber::set_Double(double val)
{
	m_node = JSONNodeType_R4;
	m_val.dblVal = val;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВoВБВТВУВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
HRESULT CJSONNumber::Parse(BParseControl& stm)
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

	m_val.lVal = 0;
	m_val.dblVal = 0;

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
		stm.Empty();
		if (('0' <= val) && (val <= '9')) {
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
					if ((_I64_MAX/10) < m_val.lVal) break;
					if (((_I64_MAX/10) == m_val.lVal) && ((_I64_MAX%10) < val)) break;
					m_val.lVal = (m_val.lVal * 10) + val;
					}
				else{
					val *= -1;
					if (m_val.lVal < (_I64_MIN/10)) break;
					if ((m_val.lVal == (_I64_MIN/10)) && (val < (_I64_MIN%10))) break;
					m_val.lVal = (m_val.lVal * 10) + val;
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
			if (exponent.enable) break;
			if (point) break;
			point = true;
			}
		else if ((val == 'e') || (val == 'E')) {
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
	stm.Empty();

	m_val.dblVal = (double)m_val.lVal;
	if ((point) && (number.decimal)) {
		m_node = JSONNodeType_R4;
		if (number.sign)
			m_val.dblVal += double(number.decimal) * ::pow(10., double(number.decExp));
		else
			m_val.dblVal -= double(number.decimal) * ::pow(10., double(number.decExp));
		}
	else
		m_node = JSONNodeType_I8;
	if (exponent.enable) {
		m_node = JSONNodeType_R4;
		m_val.dblVal *= ::pow(10., double(exponent.val));
		}

	if (enable) return(E_INVALIDARG);
	return(NOERROR);
}
