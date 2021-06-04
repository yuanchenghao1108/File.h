/* --------------------------------------------------------------------+
 |                                 Type.hpp
 +---------------------------------------------------------------------+
 |Copyright (c) 2013,CHENGDU TD-TECH Ltd. eTOP Department
 |All rights reserved.
 |
 |Author    : David Liu
 |Date		: 2013-10-04
 |Version	: 2.00
 |POPI		: eTOP Internal Use Only
 |
 |Description: The file includes all the definitions about data type
 |             information,which will be used in others source file.
 |
 |Dependencies:Independence
 |
 |
 |Notes: If you use all the source code for others system platform or complier
 |       ,please change the definitions,and auto change all others source
 |       files' data type.
 |
 |PROMPT				- from - \\Header\\Type.hpp
 |
 |
 |Update History:
 |
 +---------------------------------------------------------------------+
 | Revision | Description   | Date	    | Initials	|
 +---------------------------------------------------------------------+
 |   1.00   | First Release | 2003-10-04	    |           |
 +---------------------------------------------------------------------+
 |   2.00   | Unicode Release | 2013-09-30	    | David Liu   |
 +---------------------------------------------------------------------+
 |
 |Compilation: Compiled by BCB6.0
 |Support RAD2010 - XE4
 */

#ifndef TYPE_DEF_HPP
#define TYPE_DEF_HPP
// ---------------------------------------------------------------------------
#if defined(_MSC_VER) && (_MSC_VER >= 1020) || defined(__BCPLUSPLUS__)
# pragma once
#endif
// ---------------------------------------------------------------------------
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
typedef char s8;
typedef short int s16;
typedef __int32 s32;
typedef __int64 s64;
typedef double f64;

#ifndef byte
#define   byte					u8
#endif

#ifndef word16
#define   word16				u16
#endif

#ifndef word32
#define   word32				u32
#endif

#ifndef word64
#define   word64				u64
#endif

#ifndef ascii
#define   ascii					char
#endif

#ifndef qword
#define   qword					u64
#endif

#ifndef uint8
#define   uint8					u8
#endif

#ifndef uint16
#define   uint16				u16
#endif

#ifndef uint32
#define   uint32				u32
#endif

#ifndef uint64
#define   uint64				u64
#endif

#ifndef int8
#define   int8					s8
#endif

#ifndef int16
#define   int16					s16
#endif

#ifndef int32
#define   int32					s32
#endif

#ifndef int64
#define   int64					s64
#endif

typedef u8 uint1; /* Unsigned 8  bit value type. */
typedef u16 uint2; /* Unsigned 16 bit value type. */
typedef u32 uint4; /* Unsigned 32 bit value type. */

typedef s8 int1; /* Signed 8  bit value type. */
typedef s16 int2; /* Signed 16 bit value type. */
typedef s32 int4; /* Signed 32 bit value type. */
typedef s32 sint31; /* Signed 32 bit value */
typedef s16 sint15; /* Signed 16 bit value */
typedef s8 sint7; /* Signed 8  bit value */

/* for compatibility with standard library */

#if (defined(__GNUC__) && !defined(__alpha)) || defined(__MWERKS__)
typedef unsigned short int word;
typedef unsigned long dword;
typedef unsigned long long qword;
#elif defined(_MSC_VER) || defined(__BCPLUSPLUS__)
typedef unsigned __int16 word;
typedef unsigned __int32 dword;
typedef unsigned __int64 qword;
#else
typedef u16 word;
typedef u32 dword;
#endif
// ---------------------------------------------------------------------------
const unsigned int WORD_SIZE = sizeof(word);
const unsigned int WORD_BITS = WORD_SIZE * 8;
const unsigned int WORD16_SIZE = sizeof(word16);
const unsigned int WORD16_BITS = WORD16_SIZE * 8;
// ---------------------------------------------------------------------------
/* .Aliases for minimum and maximum for types------------------- */
#define    U8_MAX  255
#define    U8_MIN  0
#define    U16_MAX 65535
#define    U16_MIN 0
#define    U32_MAX 4294967295UL
#define    U32_MIN 0
#define    U64_MIN 0
#define    U64_MAX 18446744073709551615ui64

#define    S8_MAX  127
#define    S8_MIN  (-127-1)
#define    S16_MAX 32767
#define    S16_MIN (-32767-1)
#define    S32_MAX 2147483647L
#define    S32_MIN (-2147483647L-1)
#define    S64_MAX 9223372036854775807i64
#define    S64_MIN (-9223372036854775807i64-1)

// ---------------------------------------------------------------------------
#include <Classes.hpp>

// --------------------------------------------------------------------------
#pragma warn -8026
#pragma warn -8027

// ---------------------------------------------------------------------------
__inline void __fastcall _set_date_time_format(void) {
#if __BORLANDC__ >= 0x650
	FormatSettings.DateSeparator = '-';
	FormatSettings.ShortDateFormat = L"yyyy-mm-dd";
	FormatSettings.LongDateFormat = L"yyyy-mm-dd";

	FormatSettings.TimeSeparator = ':';
	FormatSettings.ShortTimeFormat = L"hh:mm:ss";
	FormatSettings.LongTimeFormat = L"hh:mm:ss";

	FormatSettings.TimeAMString = L"AM";
	FormatSettings.TimePMString = L"PM";
#else
	DateSeparator = '-';
	ShortDateFormat = "yyyy-mm-dd";
	LongDateFormat = "yyyy-mm-dd";

	TimeSeparator = ':';
	ShortTimeFormat = "hh:mm:ss";
	LongTimeFormat = "hh:mm:ss";

	TimeAMString = "AM";
	TimePMString = "PM";
#endif
}

__inline String __fastcall _DateTimeToStr(TDateTime dt) {
#if __BORLANDC__ >= 0x620
	return FormatDateTime(L"yyyy-mm-dd hh:mm:ss", dt);
#else
	return FormatDateTime("yyyy-mm-dd hh:mm:ss", dt);
#endif
}

__inline String __fastcall _DateTimeToFileNameStr(TDateTime dt) {
#if __BORLANDC__ >= 0x620
	return FormatDateTime(L"yyyy-mm-dd hh-mm-ss", dt);
#else
	return FormatDateTime("yyyy-mm-dd hh-mm-ss", dt);
#endif
}

__inline String __fastcall _DateToStr(TDate dt) {
#if __BORLANDC__ >= 0x620
	return FormatDateTime(L"yyyy-mm-dd", dt);
#else
	return FormatDateTime("yyyy-mm-dd", dt);
#endif
}

__inline String __fastcall _TimeToStr(TTime dt) {
#if __BORLANDC__ >= 0x620
	return FormatDateTime(L"hh:mm:ss", dt);
#else
	return FormatDateTime("hh:mm:ss", dt);
#endif
}

__inline TDateTime __fastcall _StrToDateTime(String s_dt) {
	TDateTime datetime;
	TFormatSettings my_format_settings = FormatSettings;
	bool flag;
#if __BORLANDC__ >= 0x650
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"yyyy/mm/dd";
	my_format_settings.LongDateFormat = L"yyyy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"yyyy/mm/dd";
	my_format_settings.LongDateFormat = L"yyyy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"yy/mm/dd";
	my_format_settings.LongDateFormat = L"yy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"yy/mm/dd";
	my_format_settings.LongDateFormat = L"yy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;

	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"mm/dd/yyyy";
	my_format_settings.LongDateFormat = L"mm/dd/yyyy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"mm/dd/yyyy";
	my_format_settings.LongDateFormat = L"mm/dd/yyyy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"mm/dd/yy";
	my_format_settings.LongDateFormat = L"mm/dd/yy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"mm/dd/yy";
	my_format_settings.LongDateFormat = L"mm/dd/yy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = L"hh:mm:ss";
	my_format_settings.LongTimeFormat = L"hh:mm:ss";

	my_format_settings.TimeAMString = L"AM";
	my_format_settings.TimePMString = L"PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
#else
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "yyyy/mm/dd";
	my_format_settings.LongDateFormat = "yyyy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "yyyy/mm/dd";
	my_format_settings.LongDateFormat = "yyyy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "yy/mm/dd";
	my_format_settings.LongDateFormat = "yy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "yy/mm/dd";
	my_format_settings.LongDateFormat = "yy/mm/dd";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;

	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "mm/dd/yyyy";
	my_format_settings.LongDateFormat = "mm/dd/yyyy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "mm/dd/yyyy";
	my_format_settings.LongDateFormat = "mm/dd/yyyy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "mm/dd/yy";
	my_format_settings.LongDateFormat = "mm/dd/yy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "mm/dd/yy";
	my_format_settings.LongDateFormat = "mm/dd/yy";

	my_format_settings.TimeSeparator = ':';
	my_format_settings.ShortTimeFormat = "hh:mm:ss";
	my_format_settings.LongTimeFormat = "hh:mm:ss";

	my_format_settings.TimeAMString = "AM";
	my_format_settings.TimePMString = "PM";
	datetime = Now();
	flag = TryStrToDateTime(s_dt, datetime, my_format_settings);
	if (flag)
		return datetime;
#endif
	// Use FormatSettings, and get exception
	return StrToDateTime(s_dt);
}

__inline TDateTime __fastcall _StrToDate(String s_dt) {
	TDate date;
	TFormatSettings my_format_settings = FormatSettings;
	bool flag;
#if __BORLANDC__ >= 0x650
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"yyyy/mm/dd";
	my_format_settings.LongDateFormat = L"yyyy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"yyyy/mm/dd";
	my_format_settings.LongDateFormat = L"yyyy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"yy/mm/dd";
	my_format_settings.LongDateFormat = L"yy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"yy/mm/dd";
	my_format_settings.LongDateFormat = L"yy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;

	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"mm/dd/yyyy";
	my_format_settings.LongDateFormat = L"mm/dd/yyyy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"mm/dd/yyyy";
	my_format_settings.LongDateFormat = L"mm/dd/yyyy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = L"mm/dd/yy";
	my_format_settings.LongDateFormat = L"mm/dd/yy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = L"mm/dd/yy";
	my_format_settings.LongDateFormat = L"mm/dd/yy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
#else
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "yyyy/mm/dd";
	my_format_settings.LongDateFormat = "yyyy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "yyyy/mm/dd";
	my_format_settings.LongDateFormat = "yyyy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "yy/mm/dd";
	my_format_settings.LongDateFormat = "yy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "yy/mm/dd";
	my_format_settings.LongDateFormat = "yy/mm/dd";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;

	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "mm/dd/yyyy";
	my_format_settings.LongDateFormat = "mm/dd/yyyy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;

	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "mm/dd/yyyy";
	my_format_settings.LongDateFormat = "mm/dd/yyyy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '-';
	my_format_settings.ShortDateFormat = "mm/dd/yy";
	my_format_settings.LongDateFormat = "mm/dd/yy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
	my_format_settings.DateSeparator = '/';
	my_format_settings.ShortDateFormat = "mm/dd/yy";
	my_format_settings.LongDateFormat = "mm/dd/yy";
	date = Date();
	flag = TryStrToDateTime(s_dt, date, my_format_settings);
	if (flag)
		return date;
#endif
	// Use FormatSettings, and get exception
	return StrToDate(s_dt);
}

#pragma warn -8058

__inline TDateTime __fastcall _StrToTime(String s_dt) {
	return StrToTime(s_dt);
}

// ---------------------------------------------------------------------------
__inline DWORD __fastcall _get_tick_count(DWORD &tBegin) {
	tBegin = GetTickCount();
	return tBegin;
}

__inline DWORD __fastcall _get_tick_count_elapsed(DWORD &tEnd, DWORD tBegin) {
	if ((tEnd = GetTickCount()), tEnd < tBegin)
		tEnd = tEnd + (86400000 - tBegin) + 1;
	else
		tEnd = tEnd - tBegin + 1;
	return tEnd;
}
#define _GetTickCount(x,y) _get_tick_count_elapsed(x,y)
#pragma warn +8058

// ---------------------------------------------------------------------------
#ifdef _DELPHI_STRING_UNICODE
#else
#endif
// ---------------------------------------------------------------------------
// 不能用于返回值 为 TCHAR*,临时变量
#ifdef UNICODE
#define _String				String
#else
#define _String				AnsiString
#endif
// ---------------------------------------------------------------------------
/*
 #if __BORLANDC__ >= 0x620
 wcscpy(Params.WinClassName,String(APPNAME).w_str());
 #elif __BORLANDC__ >= 0x0560
 strcpy(Params.WinClassName,APPNAME);
 #else
 strcpy(Params.WinClassName,APPNAME);
 #endif
 */
#if __BORLANDC__ >= 0x620
// #include <Classes.hpp>

/*
 __inline  wchar_t *GetComStringA(AnsiString str)
 {
 if(str.Trim() != "")
 return String(str).w_str();
 else
 return String(" ").w_str();
 }
 inline wchar_t *GetComString(String str)
 {
 if(str.Trim() != "")
 return String(str).w_str();
 else
 return String(" ").w_str();
 }
 __inline  wchar_t *GetComStringW(WideString str)
 {
 if(str.Trim() != "")
 return String(str).w_str();
 else
 return String(" ").w_str();
 }
 // */
// ---------------------------------------------------------------------------
// 多数支持COM的语言都没法处理单以NULL结尾的字符数组（不管是否是UNICODE）。
// MS: CComBSTR
// BCB: WideString[ WideString(xxx).c_bstr()]
// For Invoke COM Interface
// --------------------------------------------
class _TCOM_BSTR_Call {
public:
	/* -------------------------------------------------------------------- */
	explicit _TCOM_BSTR_Call(void) {
		ws = L"";
	}

	explicit _TCOM_BSTR_Call(const char* _str) : ws(_str) {
		// ws
	}

	explicit _TCOM_BSTR_Call(const wchar_t* _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Call(const AnsiString _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Call(const String _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Call(const WideString _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Call(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
	}

	~_TCOM_BSTR_Call() {
		// ws
	}

	/* -------------------------------------------------------------------- */
	const char * __fastcall c_str(void) {
		cs = ws.data();
		return cs.c_str();
	}

	const wchar_t * __fastcall w_str(void) {
		return (wchar_t*)(ws.data());
	}

	const BSTR __fastcall c_bstr(void) const {
		return ws.c_bstr();
	}

	const AnsiString __fastcall DataAnsi(void) {
		return AnsiString(ws.data());
	}

	const String __fastcall DataString(void) {
		return String(ws.data());
	}

	const WideString __fastcall DataWString(void) {
		return WideString(ws.data());
	}

	/* -------------------------------------------------------------------- */
	// BSTR* __fastcall operator& ()
	BSTR __fastcall Call(void) {
		return *&ws;
	}

	BSTR __fastcall Call(const char* _str) {
		ws = L"";
		ws = _str;
		return *&ws;
	}

	BSTR __fastcall Call(const wchar_t* _str) {
		ws = L"";
		ws = _str;
		return *&ws;
	}

	BSTR __fastcall Call(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return *&ws;
	}

	BSTR __fastcall Call(const AnsiString _str) {
		ws = L"";
		ws = _str;
		return *&ws;
	}

	BSTR __fastcall Call(const String _str) {
		ws = L"";
		ws = _str;
		return *&ws;
	}

	BSTR __fastcall Call(const WideString _str) {
		ws = L"";
		ws = _str;
		return *&ws;
	}

	/* -------------------------------------------------------------------- */
	BSTR* __fastcall Call_Ptr(void) {
		return &ws;
	}

	BSTR* __fastcall Call_Ptr(const char* _str) {
		ws = L"";
		ws = _str;
		return &ws;
	}

	BSTR* __fastcall Call_Ptr(const wchar_t* _str) {
		ws = L"";
		ws = _str;
		return &ws;
	}

	BSTR* __fastcall Call_Ptr(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return &ws;
	}

	BSTR* __fastcall Call_Ptr(const AnsiString _str) {
		ws = L"";
		ws = _str;
		return &ws;
	}

	BSTR* __fastcall Call_Ptr(const String _str) {
		ws = L"";
		ws = _str;
		return &ws;
	}

	BSTR* __fastcall Call_Ptr(const WideString _str) {
		ws = L"";
		ws = _str;
		return &ws;
	}

	/* -------------------------------------------------------------------- */
private:
	/* -------------------------------------------------------------------- */
	WideString ws;
	AnsiString cs;

	/* -------------------------------------------------------------------- */
	_TCOM_BSTR_Call(const _TCOM_BSTR_Call&);
	void operator = (const _TCOM_BSTR_Call&);
	/* -------------------------------------------------------------------- */
};
#define String_2_BSTR_Call(_str) _TCOM_BSTR_Call().Call(_str)

// --------------------------------------------
// For COM Internal BSTR return
// *result = AnsiC_BSTR("xxxx");
// *result = AnsiW_BSTR("xxxx");
// *result = AnsiS_BSTR("xxxx");
// *result = Str_BSTR("xxxx");
// *result = WideS_BSTR("xxxx");
class _TCOM_BSTR_Ret {
public:
	/* -------------------------------------------------------------------- */
	explicit _TCOM_BSTR_Ret(void) {
		ws = L"";
	}

	explicit _TCOM_BSTR_Ret(const char* _str) : ws(_str) {
		// ws
	}

	explicit _TCOM_BSTR_Ret(const wchar_t* _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Ret(const AnsiString _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Ret(const String _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Ret(const WideString _str) : ws(_str) {

	}

	explicit _TCOM_BSTR_Ret(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
	}

	~_TCOM_BSTR_Ret() {
		// ws
	}

	/* -------------------------------------------------------------------- */
	// wchar_t* __fastcall Copy() const
	BSTR __fastcall Copy(void) {
		if (ws.IsEmpty()) {
			ws = L" ";
		}
		return ws.Copy();
	}

	BSTR __fastcall Copy(const char* _str) {
		ws = L"";
		ws = _str;
		return ws.Copy();
	}

	BSTR __fastcall Copy(const wchar_t* _str) {
		ws = L"";
		ws = _str;
		return ws.Copy();
	}

	BSTR __fastcall Copy(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return ws.Copy();
	}

	BSTR __fastcall Copy(const AnsiString _str) {
		ws = L"";
		ws = _str;
		return ws.Copy();
	}

	BSTR __fastcall Copy(const String _str) {
		ws = L"";
		ws = _str;
		return ws.Copy();
	}

	BSTR __fastcall Copy(const WideString _str) {
		ws = L"";
		ws = _str;
		return ws.Copy();
	}

	/* -------------------------------------------------------------------- */
	/*
	 [in, out]BSTR 调用方式
	 _TCOM_BSTR_Call str_bstr;
	 p->func(&str_bsr.Call_Ptr(str));
	 WideString wstr = str_bstr.DataWString();
	 */

	BSTR __fastcall Trans(const BSTR _bstr, const char* _str) {
		ws = L"";
		ws.Attach(_bstr);
		ws = _str;
		return ws.Detach();
	}

	BSTR __fastcall Trans(const BSTR _bstr, const wchar_t* _str) {
		ws = L"";
		ws.Attach(_bstr);
		ws = _str;
		return ws.Detach();
	}

	BSTR __fastcall Trans(const BSTR _bstr, const BSTR _bstr_in) {
		ws = L"";
		ws.Attach(_bstr);
		WideString ws_temp;
		ws_temp.Attach(_bstr_in);
		ws = ws_temp;
		return ws.Detach();
	}

	BSTR __fastcall Trans(const BSTR _bstr, const AnsiString _str) {
		ws = L"";
		ws.Attach(_bstr);
		ws = _str;
		return ws.Detach();
	}

	BSTR __fastcall Trans(const BSTR _bstr, const String _str) {
		ws = L"";
		ws.Attach(_bstr);
		ws = _str;
		return ws.Detach();
	}

	BSTR __fastcall Trans(const BSTR _bstr, const WideString _str) {
		ws = L"";
		ws.Attach(_bstr);
		ws = _str;
		return ws.Detach();
	}

	/* -------------------------------------------------------------------- */
private:
	/* -------------------------------------------------------------------- */
	WideString ws;

	/* -------------------------------------------------------------------- */
	_TCOM_BSTR_Ret(const _TCOM_BSTR_Ret&);
	void operator = (const _TCOM_BSTR_Ret&);
	/* -------------------------------------------------------------------- */
};
#define String_2_BSTR_Ret(_str) _TCOM_BSTR_Ret().Copy(_str)
#define BSTR_In_Out_Ret(_bstr, _str) _TCOM_BSTR_Ret().Trans(_bstr, _str)
// --------------------------------------------
// For COM return/convert BSTR to string, ansistring...
// __inline AnsiString BSTR_AnsiS(BSTR str)
// __inline String BSTR_Str(BSTR str)
// __inline WideString BSTR_WideS(BSTR str)
// __inline WideString Str_WideS(String str)

class _TCOM_BSTR_Ret_Value {
public:
	/* -------------------------------------------------------------------- */
	explicit _TCOM_BSTR_Ret_Value(void) {
		ws = L"";
		cs = "";
	}

	explicit _TCOM_BSTR_Ret_Value(const BSTR _bstr) {
		ws = L"";
		cs = "";
		ws.Attach(_bstr);
	}

	~_TCOM_BSTR_Ret_Value() {
		// ws
	}

	/* -------------------------------------------------------------------- */
	const char * __fastcall c_str(void) {
		cs = ws.data();
		return cs.c_str();
	}

	const wchar_t * __fastcall w_str(void) {
		return (wchar_t*)(ws.data());
	}

	const BSTR __fastcall c_bstr(void) const {
		return ws.c_bstr();
	}

	const AnsiString __fastcall DataAnsi(void) {
		return AnsiString(ws.data());
	}

	const String __fastcall DataString(void) {
		return String(ws.data());
	}

	const WideString __fastcall DataWString(void) {
		return WideString(ws.data());
	}

	/* -------------------------------------------------------------------- */
	const char* __fastcall _c_str(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return c_str();
	}

	const wchar_t * __fastcall _w_str(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return w_str();
	}

	const BSTR __fastcall _b_str(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return c_bstr();
	}

	AnsiString __fastcall _a_string(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return DataAnsi();
	}

	String __fastcall _string(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return DataString();
	}

	WideString __fastcall _w_string(const BSTR _bstr) {
		ws = L"";
		ws.Attach(_bstr);
		return DataWString();
	}

	/* -------------------------------------------------------------------- */
private:
	/* -------------------------------------------------------------------- */
	WideString ws;
	AnsiString cs;

	/* -------------------------------------------------------------------- */
	_TCOM_BSTR_Ret_Value(const _TCOM_BSTR_Ret_Value&);
	void operator = (const _TCOM_BSTR_Ret_Value&);
	/* -------------------------------------------------------------------- */
};
#define BSTR_2_Char(_bstr) _TCOM_BSTR_Ret_Value()._c_str(_bstr)
#define BSTR_2_WChar(_bstr) _TCOM_BSTR_Ret_Value()._w_str(_bstr)
#define BSTR_2_BSTR(_bstr) _TCOM_BSTR_Ret_Value()._b_str(_bstr)
#define BSTR_2_AString(_bstr) _TCOM_BSTR_Ret_Value()._a_string(_bstr)
#define BSTR_2_String(_bstr) _TCOM_BSTR_Ret_Value()._string(_bstr)
#define BSTR_2_WString(_bstr) _TCOM_BSTR_Ret_Value()._w_string(_bstr)
// --------------------------------------------

// --------------------------------------------
#endif

// --------------------------------------------------------------------------
#pragma warn +8026
#pragma warn +8027
// ---------------------------------------------------------------------------
#endif  // #ifndef TYPE_DEF_HPP
// *************************** END OF TYPE.HPP*************************
