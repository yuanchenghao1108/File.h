// ---------------------------------------------------------------------------
#include "Log.h"
#include "..\\File\TFile.h"
// ---------------------------------------------------------------------------
TLog::TLog(const char* filename, EM_LOG_LEVELS level) {
	// --------------------------------------------------------
	_init_all_vars(true);
	// --------------------------------------------------------
	_init_all_ptr(true);
	Log_Level = level;
	// --------------------------------------------------------	
	std::string newpath("");
	GetPathInfo(filename, 1, newpath);
	if (IsDirExist(newpath.c_str())) {
		Create_Directory(newpath.c_str());
	}
	// --------------------------------------------------------	
#ifdef UNICODE
	swprintf(FileName, 100, L"%S", filename);
	File_Handle = CreateFile((LPCWSTR)FileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
#else
	snprintf(FileName, 100, "%s", filename);
	File_Handle = CreateFile((LPCSTR)FileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
#endif
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

	memset(DataTime, 0, 64);
	memset(FileName, 0, 256);
	memset(Log_Buf, 0, LOG_MAX_BUF_LEN);
	memset(Log_Text, 0, LOG_MAX_BUF_LEN);
	
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
const char* __fastcall TLog::_get_date_time(void) {
	// --------------------------------------------
	memset(DataTime, 0, 64);
	// --------------------------------------------
	// Windows
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	// --------------------------------------------
	snprintf(DataTime, 64 - 1, "%04d-%02d-%02d %02d:%02d:%02d:%03d",
		tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,
		tm.wMilliseconds);
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
}

// ---------------------------------------------------------------------------
const char* __fastcall TLog::_printf_log_line_str(EM_LOG_LEVELS level,
	const char* text) {
	// --------------------------------------------------------
	// 判断是否打印
	if ((Log_Level < level) && (Log_Level != LOG_LVL_ERROR) &&
		(Log_Level != LOG_LVL_FATAL) && (level != LOG_LVL_ERROR) &&
		(level != LOG_LVL_FATAL)) {
		return "";
	}
	// --------------------------------------------------------
	memset(Log_Buf, 0, LOG_MAX_BUF_LEN);
	// --------------------------------------------------------
	try {
		// ----------------------------------------------------
		snprintf(Log_Buf, LOG_MAX_BUF_LEN, "%s %s %s \r\n", _get_date_time(),
			_get_level_str(level), text);
		// ----------------------------------------------------
	}
	catch (...) {
		// ----------------------------------------------------
		snprintf(Log_Buf, LOG_MAX_BUF_LEN, "%s %s %s\r\n", _get_date_time(),
			_get_level_str(level), "!!!Input variant args has bugs!!!");
		// ----------------------------------------------------
	}
	// --------------------------------------------------------
	return Log_Buf;
}

// ---------------------------------------------------------------------------
bool __fastcall TLog::_write_log(const char* text, size_t len) {
	// --------------------------------------------------------
	if (!File_Handle) {
		return false;
	}
	// --------------------------------------------------------
	DWORD size_written;
	BOOL result = WriteFile(File_Handle, text, len, &size_written, 0);
	// --------------------------------------------------------
	if ((result == FALSE) || (size_written != len)) {
		return false;
	}
	// --------------------------------------------------------
	return true;
}

// ---------------------------------------------------------------------------
void TLog::PrintLog(EM_LOG_LEVELS level, const char*format, ...) {
	// --------------------------------------------------------
	va_list ap;
	va_start(ap, format);
	memset(Log_Text, 0, LOG_MAX_BUF_LEN);
	// --------------------------------------------------------
	snprintf(Log_Text, LOG_MAX_BUF_LEN, format, ap);
	// --------------------------------------------------------
	_printf_log_line_str(level, Log_Text);
	_write_log(Log_Buf, strlen(Log_Buf));
	// --------------------------------------------------------
	va_end(ap);
	// --------------------------------------------------------
	return;
}

// ---------------------------------------------------------------------------
