#ifndef _CJSONNumber_H_
#define _CJSONNumber_H_
#include "../INCLUDE/VJSONMember.h"

#include "../INCLUDE/BParseControl.h"

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                クラス定義                                 */
/*****************************************************************************/
class CJSONNumber : public JSONNumber, public VJSONMember {
	protected:
		JSONNodeType				m_node;
		struct {
			LONGLONG			lVal;								// &I64d
			double				dblVal;
			}						m_val;

	public:
									CJSONNumber(JSONAnchor* pobj);
		virtual						~CJSONNumber(void);

	public:
		virtual ULONG				Keep(void) { return(VJSONMember::Keep()); }
		virtual ULONG				Discard(void) { return(VJSONMember::Discard()); }

	public:
		virtual JSONNodeType		IsNodeType(void) { return(m_node); }
		virtual HRESULT				Key(void** ppobj) { return(VJSONMember::Key(ppobj)); }

	public:
		virtual LONGLONG			get_Long(void) { return(m_val.lVal); }
		virtual void				set_Long(LONGLONG val);
		virtual double				get_Double(void) { return(m_val.dblVal); }
		virtual void				set_Double(double val);

	public:
		virtual HRESULT				Parse(BParseControl& stm);
};


#endif	// _CJSONNumber_H_
