#ifndef FILE_H
#define FILE_H
// ---------------------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#include<fstream>
#include <string>
#include <io.h>
#include <list>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
// ---------------------------------------------------------------------------
/*
 mode:
 ios::app|ios::out    	 	  	 :如果没有文件则创建文件，如果有文件，则在文件尾追加
 ios::ate|ios::out     			 :如果没有文件则创建文件，如果有，则清空文件。
 ios::ate|ios::out|ios::in       :如果没有文件，则打开失败，有文件则定位到文件尾
 */
#define  MAX_PATH_LEN													1024*4

// ---------------------------------------------------------------------------
bool LoadFileToStream(const char* file_name, fstream& stream, int mode) {
	// --------------------------------------------------------
	if (!file_name || (file_name == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	stream.clear();
	// --------------------------------------------------------
	stream.open(file_name, mode);
	// --------------------------------------------------------
	if (!stream.is_open()) {
		return false;
	}
	// --------------------------------------------------------
	return true;
}

// ---------------------------------------------------------------------------
bool __fastcall IsFileExist(const char* file_name) {
	// --------------------------------------------------------
	if (!file_name || (file_name == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	if (_access(file_name, 0) == -1) {
		return false;
	}
	// --------------------------------------------------------
	return true;
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
bool Create_Directory(const char* path) {
	// --------------------------------------------------------
	if (!path) {
		return false;
	}
	// --------------------------------------------------------
	if (sizeof(path) > MAX_PATH_LEN) {
		return false;
	}
	// --------------------------------------------------------
	std::string inPath(path);
	// --------------------------------------------------------
	if (inPath.find_last_of("\\") != (inPath.length() - 1)) {
		inPath += "\\";
	}
	// --------------------------------------------------------
	char tmpDirPath[MAX_PATH_LEN] = {0};
	// --------------------------------------------------------
	for (uint32_t i = 0; i < inPath.length(); ++i) {
		// ----------------------------------------------------
		tmpDirPath[i] = path[i];
		// ----------------------------------------------------
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/') {
			if (_access(tmpDirPath, 0) != 0) {
				if (_mkdir(tmpDirPath) != 0) {
					return false;
				}
			}
		}
		// ----------------------------------------------------
	} // for-loop
	// --------------------------------------------------------
	return true;
}

// ---------------------------------------------------------------------------
/*
 char Log_Text[1024 * 4] = {0};

 const char* Print_Log(const char* fmt, ...) {
 // ----------------------------------------------------------
 va_list log_param;
 // ----------------------------------------------------------
 memset(Log_Text, 0, 1024*4);
 // ----------------------------------------------------------
 va_start(log_param, fmt);
 // ----------------------------------------------------------
 _vsntprintf(Log_Text, 1024*4, fmt, log_param);
 // ----------------------------------------------------------
 va_end(log_param);
 // ----------------------------------------------------------
 return Log_Text;
 }
 */
// ---------------------------------------------------------------------------
bool IsDirExist(const char* path) {
	// --------------------------------------------------------
	if (!path || (path == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	if (_access(path, 0) == -1) {
		return false;
	}
	return true;
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
/* 索引目录下所有文件，包括子目录，将索引到的文件放到file_list中 */
int GetFileList(const char* path, std::list<std::string>& file_list) {
	// --------------------------------------------------------
	if (!path || (path == '\0')) {
		return -1;
	}
	// --------------------------------------------------------
	if (_access(path, 0) == -1) {
		return -1;
	}
	// --------------------------------------------------------
	long handle;
	struct _finddata_t fileinfo;
	std::string inPath(path);
	// --------------------------------------------------------
	if (inPath.find_last_of("\\") != (inPath.length() - 1)) {
		inPath += "\\";
	}
	// --------------------------------------------------------
	std::string totalfilename(inPath);
	// --------------------------------------------------------
	inPath += "*";
	// --------------------------------------------------------
	handle = _findfirst((char*)inPath.c_str(), &fileinfo);
	if (handle == -1) {
		return -1;
	}
	// --------------------------------------------------------
	do {
		// ----------------------------------------------------
		if (fileinfo.attrib & _A_SUBDIR) { // 目录
			// ------------------------------------------------
			if ((strcmp(fileinfo.name, ".") != 0) && (strcmp(fileinfo.name,
				"..") != 0)) {
				inPath = totalfilename;
				inPath += fileinfo.name;
				inPath += "\\";
				// printf("%s\n", inPath.c_str());
				GetFileList(inPath.c_str(), file_list);
			}
			// ------------------------------------------------
		}
		else { // 文件
			// ------------------------------------------------
			// printf("%s\n", fileinfo.name);
			// 文件名：
			// file_list.push_back(fileinfo.name);
			// ------------------------------------------------
			// 路径+文件名
			std::string newfilename(totalfilename);
			newfilename += fileinfo.name;
			// ------------------------------------------------
			if (!file_list.empty()) {
				// --------------------------------------------
				bool bexistence = false;
				// --------------------------------------------
				for (std::list<std::string>::iterator iter = file_list.begin();
				iter != file_list.end(); iter++) {
					if (*iter == newfilename) {
						bexistence = true;
						break;
					}
				} // for-loop
				// --------------------------------------------
				if (!bexistence) {
					file_list.push_back(newfilename);
				}
				// --------------------------------------------
			}
			else {
				file_list.push_back(newfilename);
			}
			// ------------------------------------------------
		}
	}
	while (!_findnext(handle, &fileinfo));
	// --------------------------------------------------------
	_findclose(handle);
	// --------------------------------------------------------
	return 0;
}

// ---------------------------------------------------------------------------
/*
 mode:
 0:磁盘名
 1:路径名
 2:文件名
 3:后缀名
 */
int GetPathInfo(const char* path, int mode, std::string& result) {
	// --------------------------------------------------------
	if (!path || path[0] == '\0') {
		return -1;
	}
	char szDrive[64] = {0}; // 磁盘名
	char szDir[1024] = {0}; // 路径名
	char szFname[1024] = {0}; // 文件名
	char szExt[64] = {0}; // 后缀名
	// --------------------------------------------------------
	_splitpath(path, szDrive, szDir, szFname, szExt); // 分解路径
	// --------------------------------------------------------
	switch (mode) {
	case 0:
		result = szDrive;
		break;
	case 1:
		result = szDir;
		break;
	case 2:
		result = szFname;
		break;
	case 3:
		result = szExt;
		break;
	default: ;
		result = "";
	}
	return 0;
}

// ---------------------------------------------------------------------------
void __fastcall Open_File_Dir(const char* file_name) {
	// ------------------------------------------------------
	SHELLEXECUTEINFO ShExecInfo = {0};
	// ------------------------------------------------------
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	// ------------------------------------------------------
	ShExecInfo.fMask =
		SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI |
		SEE_MASK_NO_CONSOLE;
	// ------------------------------------------------------
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	// ------------------------------------------------------
	ShExecInfo.lpFile = file_name; // 调用的程序名
	// ------------------------------------------------------
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW; // SW_HIDE; //SW_SHOW; // 窗口状态为隐藏
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	// ------------------------------------------------------
	// WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}

// ---------------------------------------------------------------------------
char* _Trim(char *str) {
	char *str_last, *str_cur;
	if (str == NULL)
		return NULL;
	// ----------------------------------------------------
	for (; *str == TEXT(' ') || *str == TEXT('\t'); ++str);
	for (str_last = str_cur = str; *str_cur != TEXT('\0'); ++str_cur)
		if (*str_cur != TEXT(' ') && *str_cur != TEXT('\t'))
			str_last = str_cur;
	// ----------------------------------------------------
	*++str_last = 0;
	return str;
}

// ---------------------------------------------------------------------------
bool _Judeg_A(std::string str) {
	// ----------------------------------------------------
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			return true;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			return true;
		}
	}
	// ----------------------------------------------------
	return false;
}

// ---------------------------------------------------------------------------
char* _ToUpper(char* str) {
	// ----------------------------------------------------
	char *str_temp, *str_cur;
	if (str == NULL)
		return NULL;
	// ----------------------------------------------------
	for (str_temp = str_cur = str; *str_cur != TEXT('\0');) {
		*str_temp = toupper(*str_cur);
		str_cur++;
		str_temp = str_cur;
	}
	// ----------------------------------------------------
	*++str_temp = 0;
	return str;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
#endif
