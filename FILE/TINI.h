// -------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------
#include <map>
#include<string>
// -------------------------------------------------------------------------------
using namespace std;

// -------------------------------------------------------------------------------
enum INI_RES {
	INI_SUCCESS = 0, // 成功
		INI_ERROR, // 普通错误
		INI_OPENFILE_ERROR, // 打开文件失败
		INI_NO_ATTR // 无对应的键值
	};

// -------------------------------------------------------------------------------
// 子键索引    子键值
typedef map<std::string, std::string>KEYMAP;
// 主键索引 主键值
typedef map<std::string, KEYMAP>MAINKEYMAP;
// -------------------------------------------------------------------------------
#define CONFIGLEN           256

// -------------------------------------------------------------------------------
class TINI {
private:
	// --------------------------------------------------------
	int vError;
	// 被打开的文件局柄
	FILE* m_fp;
	char m_szKey[CONFIGLEN];
	MAINKEYMAP m_Map;

	// --------------------------------------------------------
	void __fastcall _init_all_vars(bool is_first);
	void __fastcall _init_all_ptr();
	// --------------------------------------------------------
	// 读取config文件
	INI_RES __fastcall _get_key(const char* mAttr, const char* cAttr,
		char* value);
	string __fastcall _trim(const char* source);

	// --------------------------------------------------------
protected:
public:
	// --------------------------------------------------------
	int __fastcall ReadInteger(const char* mAttr, const char* cAttr,
		int def_value = 0);
	char * __fastcall ReadString(const char* mAttr, const char* cAttr,
		const char* def_value = "NULL");
	bool __fastcall ReadBoolean(const char* mAttr, const char* cAttr,
		bool def_value = false);
	// --------------------------------------------------------
	void __fastcall WriteString(const char* mAttr, const char* cAttr,
		const char* value);
	void __fastcall WriteInteger(const char* mAttr, const char* cAttr,
		int value);
	// --------------------------------------------------------
	int __fastcall LoadFile(const char* filename);
	INI_RES __fastcall UnLoadFile(void);
	int __fastcall LoadFileFromStream();
	// --------------------------------------------------------
	TINI(void);
	~TINI(void);
	// --------------------------------------------------------
};
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
/* End Of  File TINI.h */
