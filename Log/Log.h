// ---------------------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#ifndef Log_H
#define Log_H
// ---------------------------------------------------------------------------
#include <windows.h>
// ---------------------------------------------------------------------------
typedef enum log_levels {
	LOG_LVL_SILENT = 0, LOG_LVL_OUTPUT, LOG_LVL_USER, LOG_LVL_FATAL,
	LOG_LVL_ERROR, LOG_LVL_WARNING, LOG_LVL_INFO, LOG_LVL_DEBUG, LOG_LVL_DIDO,
	LOG_LVL_LOW,
} EM_LOG_LEVELS;

// ---------------------------------------------------------------------------
__inline const char* _get_level_str(EM_LOG_LEVELS level) {
	// --------------------------------------------------------
	switch (level) {
	case LOG_LVL_SILENT:
		return " Silent  : ";
	case LOG_LVL_OUTPUT:
		return " Output  : ";
	case LOG_LVL_USER:
		return " User    : ";
	case LOG_LVL_FATAL:
		return " Fatal   : ";
	case LOG_LVL_ERROR:
		return " Error   : ";
	case LOG_LVL_WARNING:
		return " Warnning: ";
	case LOG_LVL_INFO:
		return " Info    : ";
	case LOG_LVL_DEBUG:
		return " Debug   : ";
	case LOG_LVL_DIDO:
		return " DIDO    : ";
	case LOG_LVL_LOW:
		return " LOW     : ";
	default:
		break;
		return " LOW     : ";
	}
	// --------------------------------------------------------
	return " Unknow  : ";
}

// ---------------------------------------------------------------------------
#define LOG_MAX_BUF_LEN													(1024*4)
// ---------------------------------------------------------------------------
class TLog {
private:
	EM_LOG_LEVELS Log_Level;
	void* File_Handle;
	char DataTime[64];
#ifdef UNICODE
	WCHAR FileName[256];
#else
	char FileName[256];
#endif
	char Log_Buf[LOG_MAX_BUF_LEN];
	char Log_Text[LOG_MAX_BUF_LEN];

	void __fastcall _init_all_vars(bool is_first);
	void __fastcall _init_all_ptr(bool is_first);
	const char* __fastcall _get_date_time(void);
	const char* __fastcall _printf_log_line_str(EM_LOG_LEVELS level,
		const char* text);
	bool __fastcall _write_log(const char* text, size_t len);

#ifdef M_SEND_MSG_SELF
	char AppName[256];
	HWND hHandle;
	HWND __fastcall _find_win_handle_with_app_name(const char* app_name);
#endif
public:
#ifdef M_SEND_MSG_SELF
	void __fastcall SendMsg(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	void __fastcall SendLog(const char* slog,EM_LOG_LEVELS level);
#endif
	void PrintLog(EM_LOG_LEVELS level, const char*format, ...);
	TLog(const char* filename, const char* app_name,EM_LOG_LEVELS level = LOG_LVL_SILENT);
	~TLog();
};
// ---------------------------------------------------------------------------
#define LOG_OUTPUT(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_OUTPUT,__VA_ARGS__);
#define LOG_USER(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_USER,__VA_ARGS__);
#define LOG_FATAL(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_FATAL,__VA_ARGS__);
#define LOG_ERROR(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_ERROR,__VA_ARGS__);
#define LOG_WARNING(...)       	if(pLog)pLog->PrintLog(LOG_LVL_WARNING,__VA_ARGS__);
#define LOG_INFO(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_INFO,__VA_ARGS__);
#define LOG_DEBUG(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_DEBUG,__VA_ARGS__);
#define LOG_DIDO(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_DIDO,__VA_ARGS__);
#define LOG_LOW(...)	       	if(pLog)pLog->PrintLog(LOG_LVL_LOW,__VA_ARGS__);
// ---------------------------------------------------------------------------
#endif
