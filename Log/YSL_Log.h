// -------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------
#ifndef YSL_LOG_H
#define YSL_LOG_H
// -------------------------------------------------------------------------------
#include <log4cplus/appender.h>
#include <log4cplus/log4cplus.h>
#include <log4cplus/fileappender.h>
#include<log4cplus/logger.h>
#include<log4cplus/layout.h>
#include <memory>
#include<string>
// -------------------------------------------------------------------------------
using namespace log4cplus;
using namespace log4cplus::helpers;
// -------------------------------------------------------------------------------
#define M_MAX_BUFF_SIZE												(1024*10)
// -------------------------------------------------------------------------------
class YSL_Log
{
	// -----------------------------------------------------
private:
	// -----------------------------------------------------
	int vError;
	SharedObjectPtr<Appender> pAppend;
	std::string str_Pattern;
	Logger pLogger;
	char* pBuff;
	// -----------------------------------------------------
	void __fastcall _init_all_vars(bool isfirst);
	void __fastcall _init_all_ptr(void);
	// -----------------------------------------------------
	

protected:
	// -----------------------------------------------------
public:
	Logger __fastcall GetLogPtr(void) {
		if (&pLogger) {
			return pLogger;
		}
	}

	char* __fastcall GetBuffPtr(void) {
		if (pBuff) {
			return pBuff;
		}
		return NULL;
	}
	// -----------------------------------------------------
	void __fastcall _set_log_text(const char* fmt, ...);
	YSL_Log(LogLevel level, const char* filename);
	~YSL_Log();
	// -----------------------------------------------------
};

// -------------------------------------------------------------------------------
#define LOG_FATAL(obj,format,...)  do{pDebugLog->_set_log_text(format, ##__VA_ARGS__); LOG4CPLUS_FATAL(obj->GetLogPtr(),obj->GetBuffPtr());}while(0)
#define LOG_ERROR(obj,format,...)  do{pDebugLog->_set_log_text(format, ##__VA_ARGS__); LOG4CPLUS_ERROR(obj->GetLogPtr(),obj->GetBuffPtr());}while(0)
#define LOG_WARN(obj,format,...)   do{pDebugLog->_set_log_text(format, ##__VA_ARGS__); LOG4CPLUS_WARN(obj->GetLogPtr(),obj->GetBuffPtr());}while(0)
#define LOG_INFO(obj,format,...)   do{pDebugLog->_set_log_text(format, ##__VA_ARGS__); LOG4CPLUS_INFO(obj->GetLogPtr(),obj->GetBuffPtr());}while(0)
#define LOG_DEBUG(obj,format,...)  do{pDebugLog->_set_log_text(format, ##__VA_ARGS__); LOG4CPLUS_DEBUG(obj->GetLogPtr(),obj->GetBuffPtr());}while(0)
#define LOG_TRACE(obj,format,...)  do{pDebugLog->_set_log_text(format, ##__VA_ARGS__); LOG4CPLUS_TRACE(obj->GetLogPtr(),obj->GetBuffPtr());}while(0)
// -------------------------------------------------------------------------------
#endif // !YSL_LOG_H


