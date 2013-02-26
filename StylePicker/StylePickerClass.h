#pragma once
#include <list>
#include <map>

typedef std::list<CString> StyleList;

class CStylePicker
{
public:
	CStylePicker(void);
	~CStylePicker(void);

	VOID AddStyle(CString name,DWORD value);
	VOID AddFakeStyle(CString name,CString value);
	VOID GetStyleList(StyleList& list);
	VOID GetFakeStyleList(StyleList& list);

	DWORD GetStyleValue(const StyleList& list);
	VOID GetStyleByValue(DWORD value,StyleList& list);
	BOOL IsFitFakeStyle(CString fakeStyle,const StyleList& list);
	VOID GetFitFakeStyle(const StyleList& style,StyleList& fakeStyle);
	VOID GetStyleByFakeStyle(CString fakeStyle,StyleList& list);
protected:
	std::map<CString,DWORD> m_styleMap;
	std::map<CString,StyleList > m_fakeStyleMap;
};

