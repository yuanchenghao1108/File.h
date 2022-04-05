// ---------------------------------------------------------------------------
#include "Log.h"
#include "..\\File\File.h"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
TLog::TLog(const TCHAR* filename, const TCHAR* app_name, EM_LOG_LEVELS level) {
	// --------------------------------------------------------
	_init_all_vars(true);
	// --------------------------------------------------------
	_init_all_ptr(true);
	// --------------------------------------------------------
	Log_Level = level;
	// --------------------------------------------------------
	std::string newpath("");
#ifdef UNICODE
	swprintf(FileName, 100, L"%s", filename);
	File_Handle = CreateFile((LPCWSTR)FileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
#else
	snprintf(FileName, 100, "%s", filename);
	File_Handle = CreateFile((LPCSTR)FileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
#endif
	// --------------------------------------------------------	
#ifdef UNICODE
	char file_name[LOG_MAX_PATH_LEN] = { 0 };
	int nChLen = WideCharToMultiByte(CP_ACP, 0, filename, -1, NULL, 0, NULL, NULL);	//获取转换后的char长度 长度为11 10个字符(4+2*3)+1个结束符
	WideCharToMultiByte(CP_ACP, 0, filename, -1, file_name, nChLen, NULL, NULL);
	GetPathInfo(file_name, 1, newpath);
#else
	GetPathInfo(filename, 1, newpath);
#endif
	// --------------------------------------------------------
#ifdef M_SEND_MSG_SELF
#ifdef UNICODE
	swprintf(AppName, LOG_MAX_PATH_LEN, filename);
#else
	snprintf(AppName, LOG_MAX_PATH_LEN, app_name);
#endif
#endif
	// --------------------------------------------------------
	if (!IsDirExist(newpath.c_str())) {
		// ------------------------------------------------
		Create_Directory(newpath.c_str());
		// ------------------------------------------------
	}
	// --------------------------------------------------------

	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
TLog::~TLog() {
	// --------------------------------------------------------
	if (File_Handle) {
		CloseHandle(File_Handle);
		File_Handle = NULL;
	}
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
void __fastcall TLog::_init_all_vars(bool is_first) {
	// --------------------------------------------------------
	if (is_first) {

	}
	// --------------------------------------------------------
	Log_Level = LOG_LVL_SILENT;

	memset(DataTime, 0, LOG_MAX_PATH_LEN);
	memset(FileName, 0, LOG_MAX_PATH_LEN);
	memset(Log_Buf, 0, LOG_MAX_BUF_LEN);
	memset(Log_Text, 0, LOG_MAX_BUF_LEN);
	// --------------------------------------------------------
#ifdef M_SEND_MSG_SELF
	memset(AppName, 0, 256);
#endif
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
const TCHAR* __fastcall TLog::_get_date_time(void) {
	// --------------------------------------------
	memset(DataTime, 0, LOG_MAX_PATH_LEN);
	// --------------------------------------------
	// Windows
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	// --------------------------------------------
#ifdef UNICODE
	_snwprintf(DataTime, LOG_MAX_PATH_LEN - 1, L"%04d-%02d-%02d %02d:%02d:%02d:%03d", tm.wYear,
		tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
#else
	snprintf(DataTime, LOG_MAX_PATH_LEN - 1, "%04d-%02d-%02d %02d:%02d:%02d:%03d", tm.wYear,
		tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
#endif  
	// --------------------------------------------
	return DataTime;
}

// ---------------------------------------------------------------------------
void __fastcall TLog::_init_all_ptr(bool is_first) {
	// --------------------------------------------------------
	if (is_first) {

	}
	// --------------------------------------------------------
	File_Handle = NULL;
	// --------------------------------------------------------
#ifdef M_SEND_MSG_SELF
	hHandle = NULL;
#endif
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
const TCHAR* __fastcall TLog::_printf_log_line_str(EM_LOG_LEVELS level,
	const TCHAR* text) {
	// --------------------------------------------------------
	// 判断是否打印
	if ((Log_Level < level) && (Log_Level != LOG_LVL_ERROR) &&
		(Log_Level != LOG_LVL_FATAL) && (level != LOG_LVL_ERROR) &&
		(level != LOG_LVL_FATAL)) {
		return TEXT("");
	}
	// --------------------------------------------------------
	memset(Log_Buf, 0, LOG_MAX_BUF_LEN);
	// --------------------------------------------------------
	try {
		// ----------------------------------------------------
#ifdef UNICODE
		_snwprintf(Log_Buf, LOG_MAX_BUF_LEN, L"%s %s %s \r\n", _get_date_time(),
			_get_level_str(level), text);
#else
		snprintf(Log_Buf, LOG_MAX_BUF_LEN, "%s %s %s \r\n", _get_date_time(),
			_get_level_str(level), text);
#endif
		// ----------------------------------------------------
	}
	catch (...) {
		// ----------------------------------------------------
#ifdef UNICODE
		_snwprintf(Log_Buf, LOG_MAX_BUF_LEN, L"%s %s %s\r\n", _get_date_time(),
			_get_level_str(level), L"!!!Input variant args has bugs!!!");
#else
		snprintf(Log_Buf, LOG_MAX_BUF_LEN, "%s %s %s\r\n", _get_date_time(),
			_get_level_str(level), "!!!Input variant args has bugs!!!");
#endif
		// ----------------------------------------------------
	}
	// --------------------------------------------------------
	return Log_Buf;
}

// ---------------------------------------------------------------------------
bool __fastcall TLog::_write_log(const TCHAR* text, size_t len) {
	// --------------------------------------------------------
	if (!File_Handle) {
		return false;
	}
	// --------------------------------------------------------
	DWORD size_written;
	BOOL result = WriteFile((HANDLE)File_Handle, text, len, &size_written, 0);
	// --------------------------------------------------------
	if ((result == FALSE) || (size_written != len)) {
		return false;
	}
	// --------------------------------------------------------
	return true;
}

// ---------------------------------------------------------------------------
void TLog::PrintLog(EM_LOG_LEVELS level, const TCHAR *format, ...) {
	// --------------------------------------------------------
	va_list ap;
	va_start(ap, format);
	memset(Log_Text, 0, LOG_MAX_BUF_LEN*sizeof(TCHAR));
	// --------------------------------------------------------
#ifdef UNICODE	
	_vsnwprintf(Log_Text, LOG_MAX_BUF_LEN - 1, format, ap);
#else
	_vsnprintf(Log_Text, LOG_MAX_BUF_LEN - 1, format, ap);
#endif
	// --------------------------------------------------------
	_printf_log_line_str(level, Log_Text);
	// --------------------------------------------------------
#ifdef M_SEND_MSG_SELF
	if (hHandle) {
		SendLog(Log_Buf, level);
	}
	else {
		hHandle = _find_win_handle_with_app_name(AppName);
	}
#endif
	// --------------------------------------------------------
#ifdef UNICODE
	size_t len = wcslen(Log_Buf)*2;
#else
	size_t len = strlen(Log_Buf);
#endif
	_write_log(Log_Buf, len);
	// --------------------------------------------------------
	va_end(ap);
	// --------------------------------------------------------
	return;
}

// ---------------------------------------------------------------------------
#ifdef M_SEND_MSG_SELF

HWND __fastcall TLog::_find_win_handle_with_app_name(const TCHAR* app_name) {
	// --------------------------------------------------------
	return ::FindWindow(NULL, app_name);
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
void __fastcall TLog::SendMsg(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	// --------------------------------------------------------
	::SendMessage(hwnd, Msg, wParam, lParam);
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
void __fastcall TLog::SendLog(const TCHAR* slog, EM_LOG_LEVELS level) {
	// --------------------------------------------------------
	TCHAR str[LOG_MAX_BUF_LEN] = {0};
	COPYDATASTRUCT mydata = { 0 };
	// --------------------------------------------------------
#ifdef UNICODE
	_snwprintf(str, LOG_MAX_BUF_LEN, L"%s", slog);
	int len = wcslen(str);
#else
	snprintf(str, LOG_MAX_BUF_LEN, "%s", slog);
	int len = strlen(str);
#endif
	str[len - 2] = '\0';
	// --------------------------------------------------------
	switch (level) {
	case LOG_LVL_ERROR:
		mydata.dwData = 0x01;
		break;
	case LOG_LVL_WARNING:
		mydata.dwData = 0x02;
		break;
	case LOG_LVL_INFO:
		mydata.dwData = 0x03;
		break;
	case LOG_LVL_DEBUG:
		mydata.dwData = 0x04;
		break;
	case LOG_LVL_DIDO:
		mydata.dwData = 0x05;
		break;
	case LOG_LVL_LOW:
		mydata.dwData = 0x06;
		break;
	default:
		mydata.dwData = 0x07;
		break;
	}

	mydata.cbData = len;
	mydata.lpData = (void*)str;a
	// --------------------------------------------------------
	SendMsg(hHandle, WM_COPYDATA, NULL, (LPARAM) & mydata);
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// End
