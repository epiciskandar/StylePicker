#include "stdafx.h"
#include "StylePickerClass.h"


CStylePicker::CStylePicker(void)
{
}


CStylePicker::~CStylePicker(void)
{
}

VOID CStylePicker::AddStyle( CString name,DWORD value )
{
	m_styleMap[name] = value;
}

VOID CStylePicker::AddFakeStyle( CString name,CString value )
{
	m_fakeStyleMap[name].push_back(value);
}

VOID CStylePicker::GetStyleList( StyleList& list )
{
	for (auto& i:m_styleMap)
	{
		list.push_back(i.first);
	}
}

VOID CStylePicker::GetFakeStyleList( StyleList& list )
{
	for (auto& i:m_fakeStyleMap)
	{
		list.push_back(i.first);
	}
}

DWORD CStylePicker::GetStyleValue( const StyleList& list )
{
	DWORD value = 0;
	for (auto& i:list)
	{
		auto ifind = m_styleMap.find(i);
		if (ifind != m_styleMap.end())
		{
			value |= ifind->second;
		}
	}
	return value;
}

BOOL CStylePicker::IsFitFakeStyle( CString fakeStyle,const StyleList& list )
{
	auto ifakeStyle = m_fakeStyleMap.find(fakeStyle);
	if (ifakeStyle != m_fakeStyleMap.end())
	{
		for (auto& i:ifakeStyle->second)
		{
			auto ifind = std::find(list.begin(),list.end(),i);
			if (ifind == list.end())
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

VOID CStylePicker::GetFitFakeStyle( const StyleList& style,StyleList& fakeStyle )
{
	for (auto& i:m_fakeStyleMap)
	{
		if (IsFitFakeStyle(i.first,style))
		{
			fakeStyle.push_back(i.first);
		}
	}
}

VOID CStylePicker::GetStyleByFakeStyle( CString fakeStyle,StyleList& list )
{
	auto ifind = m_fakeStyleMap.find(fakeStyle);
	if (ifind != m_fakeStyleMap.end())
	{
		for (auto& i:ifind->second)
		{
			list.push_back(i);
		}
	}
}

VOID CStylePicker::GetStyleByValue( DWORD value,StyleList& list )
{
	for (auto& i:m_styleMap)
	{
		if (value & i.second)
		{
			list.push_back(i.first);
		}
	}
}
