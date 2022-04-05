// ---------------------------------------------------------------------------
#include "SerialPort.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "..\\Head\\type.h"
#include  "..\\ErrorType\\err_type.h"
// ---------------------------------------------------------------------------
SerialPort::SerialPort()
{
	vError = ERR_SUCCESS;
}

// ---------------------------------------------------------------------------
SerialPort::~SerialPort()
{
	// --------------------------------------------------------
	close();
	// --------------------------------------------------------
}

// ---------------------------------------------------------------------------
bool SerialPort::open(const char* portname, int baudrate, char parity, char databit, char stopbit, char synchronizeflag)
{
	// --------------------------------------------------------
	this->Synchronizeflag = synchronizeflag;
	HANDLE hCom = NULL;
	vError = ERR_SUCCESS;
	// --------------------------------------------------------
	if (this->Synchronizeflag)
	{
		// ----------------------------------------------------
		//同步方式
		hCom = CreateFileA((LPCSTR)portname, //串口名
			GENERIC_READ | GENERIC_WRITE, //支持读写
			0, //独占方式，串口不支持共享
			NULL,//安全属性指针，默认值为NULL
			OPEN_EXISTING, //打开现有的串口文件
			0, //0：同步方式，FILE_FLAG_OVERLAPPED：异步方式
			NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL
		// ----------------------------------------------------
	}
	else
	{
		// ----------------------------------------------------
		//异步方式
		hCom = CreateFileA((LPCSTR)portname, //串口名
			GENERIC_READ | GENERIC_WRITE, //支持读写
			0, //独占方式，串口不支持共享
			NULL,//安全属性指针，默认值为NULL
			OPEN_EXISTING, //打开现有的串口文件
			FILE_FLAG_OVERLAPPED, //0：同步方式，FILE_FLAG_OVERLAPPED：异步方式
			NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL
		// ----------------------------------------------------
	}
	// --------------------------------------------------------
	if (hCom == (HANDLE)-1)
	{
		vError = ERR_OPEN_PORT_FAIL;
		return false;
	}
	// --------------------------------------------------------
	//配置缓冲区大小 
	if (!SetupComm(hCom, M_MAX_BUF_SIZE, M_MAX_BUF_SIZE))
	{
		vError = ERR_CREATE_MEMORY_SIZE;
		return false;
	}
	// --------------------------------------------------------
	// 配置参数 
	DCB p;
	memset(&p, 0, sizeof(p));
	p.DCBlength = sizeof(p);
	p.BaudRate = baudrate; // 波特率
	p.ByteSize = databit; // 数据位
	// --------------------------------------------------------
	switch (parity) //校验位
	{
	case 0:
		p.Parity = NOPARITY; //无校验
		break;
	case 1:
		p.Parity = ODDPARITY; //奇校验
		break;
	case 2:
		p.Parity = EVENPARITY; //偶校验
		break;
	case 3:
		p.Parity = MARKPARITY; //标记校验
		break;
	}
	// ----------------------------------------------------
	switch (stopbit) //停止位
	{
	case 1:
		p.StopBits = ONESTOPBIT; //1位停止位
		break;
	case 2:
		p.StopBits = TWOSTOPBITS; //2位停止位
		break;
	case 3:
		p.StopBits = ONE5STOPBITS; //1.5位停止位
		break;
	}
	// ----------------------------------------------------
	if (!SetCommState(hCom, &p))
	{
		// 设置参数失败
		vError = ERR_INPUT_PARAMETER;
		return false;
	}
	// ----------------------------------------------------
	//超时处理,单位：毫秒
	//总超时＝时间系数×读或写的字符数＋时间常量
	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 1000; //读间隔超时
	TimeOuts.ReadTotalTimeoutMultiplier = 500; //读时间系数
	TimeOuts.ReadTotalTimeoutConstant = 5000; //读时间常量
	TimeOuts.WriteTotalTimeoutMultiplier = 500; // 写时间系数
	TimeOuts.WriteTotalTimeoutConstant = 2000; //写时间常量
	SetCommTimeouts(hCom, &TimeOuts);
	// ----------------------------------------------------
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空串口缓冲区
	// ----------------------------------------------------
	memcpy(pHandle, &hCom, sizeof(hCom));// 保存句柄
	// ----------------------------------------------------
	return true;
}

// ---------------------------------------------------------------------------
void SerialPort::close()
{
	// ----------------------------------------------------
	HANDLE hCom = *(HANDLE*)pHandle;
	if (hCom) {
		CloseHandle(hCom);
	}
	// ----------------------------------------------------
}

// ---------------------------------------------------------------------------
int SerialPort::send(const void *buf, int len)
{
	// ----------------------------------------------------
	vError = ERR_SUCCESS;
	DWORD dwBytesWrite = len; //成功写入的数据字节数
	DWORD dwBytesWrite_Read;
	HANDLE hCom = *(HANDLE*)pHandle;
	BOOL bWriteStat = false;
	DWORD dwErrorFlags; //错误标志
	COMSTAT comStat; //通讯状态
	OVERLAPPED m_osWrite; //异步输入输出结构体
	// ----------------------------------------------------
	if (!hCom) {
		// ------------------------------------------------
		vError = ERR_NULL_HANDLE;
		// ------------------------------------------------
		return vError;
	}
	// ----------------------------------------------------
	if (this->Synchronizeflag)
	{
		// ------------------------------------------------
		//同步方式
		// ------------------------------------------------
		bWriteStat = WriteFile(hCom, //串口句柄
			buf, //数据首地址
			dwBytesWrite, //要发送的数据字节数
			&dwBytesWrite_Read, //DWORD*，用来接收返回成功发送的数据字节数
			NULL); //NULL为同步发送，OVERLAPPED*为异步发送
		// ------------------------------------------------
	}
	else
	{
		// ------------------------------------------------
		//异步方式
		// ------------------------------------------------
		//创建一个用于OVERLAPPED的事件处理，不会真正用到，但系统要求这么做
		memset(&m_osWrite, 0, sizeof(m_osWrite));
		m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, L"WriteEvent");
		// ------------------------------------------------
		ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态
		// ------------------------------------------------
		bWriteStat = WriteFile(hCom, //串口句柄
			buf, //数据首地址
			dwBytesWrite, //要发送的数据字节数
			&dwBytesWrite_Read, //DWORD*，用来接收返回成功发送的数据字节数
			&m_osWrite); //NULL为同步发送，OVERLAPPED*为异步发送
		// ------------------------------------------------
	}
	// ----------------------------------------------------
	if (!bWriteStat)
	{
		// ------------------------------------------------
		if (GetLastError() == ERROR_IO_PENDING) //如果串口正在写入
		{
			// --------------------------------------------
			WaitForSingleObject(m_osWrite.hEvent, 1000); //等待写入事件1秒钟
			// --------------------------------------------
		}
		else
		{
			// --------------------------------------------
			//ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误
			//CloseHandle(m_osWrite.hEvent); //关闭并释放hEvent内存
			// --------------------------------------------
			vError = ERR_SEND_FAIL;
			// --------------------------------------------
			return vError;
			// --------------------------------------------
		}
		// ------------------------------------------------
	}
	// ----------------------------------------------------
	return dwBytesWrite;
}

// ---------------------------------------------------------------------------
int SerialPort::receive(void *buf, int maxlen)
{
	// ----------------------------------------------------
	HANDLE hCom = *(HANDLE*)pHandle;
	BOOL bReadStat = FALSE;
	DWORD wCount = maxlen; //成功读取的数据字节数
	DWORD dwErrorFlags; //错误标志
	COMSTAT comStat; //通讯状态
	OVERLAPPED m_osRead; //异步输入输出结构体
	// ----------------------------------------------------
	if (!hCom) {
		// ------------------------------------------------
		vError = ERR_NULL_HANDLE;
		// ------------------------------------------------
		return vError;
	}
	// ----------------------------------------------------
	if (this->Synchronizeflag)
	{
		//同步方式
		// ------------------------------------------------
		bReadStat = ReadFile(hCom, //串口句柄
			buf, //数据首地址
			wCount, //要读取的数据最大字节数
			&wCount, //DWORD*,用来接收返回成功读取的数据字节数
			NULL); //NULL为同步发送，OVERLAPPED*为异步发送
		// ------------------------------------------------	
	}
	else
	{
		//异步方式
		// ------------------------------------------------	
		//创建一个用于OVERLAPPED的事件处理，不会真正用到，但系统要求这么做
		memset(&m_osRead, 0, sizeof(m_osRead));
		m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");
		ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态
		// ------------------------------------------------	
		if (!comStat.cbInQue) {
			//如果输入缓冲区字节数为0，则返回false
			vError = ERR_MERRORY_SIZE;
			return vError;
		} 
		// ------------------------------------------------	
		bReadStat = ReadFile(hCom, //串口句柄
			buf, //数据首地址
			wCount, //要读取的数据最大字节数
			&wCount, //DWORD*,用来接收返回成功读取的数据字节数
			&m_osRead); //NULL为同步发送，OVERLAPPED*为异步发送
		// ------------------------------------------------
	}
	// ----------------------------------------------------
	if (!bReadStat)
	{
		// ------------------------------------------------
		if (GetLastError() == ERROR_IO_PENDING) //如果串口正在读取中
		{
			// --------------------------------------------
			//GetOverlappedResult函数的最后一个参数设为TRUE
			//函数会一直等待，直到读操作完成或由于错误而返回
			GetOverlappedResult(hCom, &m_osRead, &wCount, TRUE);
			// --------------------------------------------
		}
		else
		{
			// --------------------------------------------
			ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误
			CloseHandle(m_osRead.hEvent); //关闭并释放hEvent的内存
			// --------------------------------------------
			vError = ERR_READ_FAIL;
			// --------------------------------------------
			return vError;
		}
		// ------------------------------------------------
	}
	// ----------------------------------------------------
	return wCount;
}

// ---------------------------------------------------------------------------
std::vector<std::string> SerialPort::getComPort(void)
{
	// ----------------------------------------------------
	HKEY hKey;
	wchar_t portName[256], w_commName[256];
	std::vector<std::string> comName;
	// ----------------------------------------------------
	//打开串口注册表对应的键值
	if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey))
	{
		// ------------------------------------------------
		int i = 0;
		int mm = 0;
		DWORD  dwLong, dwSize;
		// ------------------------------------------------
		while (TRUE)
		{
			dwLong = dwSize = sizeof(portName);
			//枚举串口
			if (ERROR_NO_MORE_ITEMS == ::RegEnumValue(hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)w_commName, &dwSize))
			{
				break;
			}
			char* commName = wideCharToMultiByte(w_commName);
			comName.push_back(commName);
			delete[] commName;
			i++;
		}//while-loop
		 // ------------------------------------------------
		//关闭注册表
		RegCloseKey(hKey);
		// ------------------------------------------------
	}
	else
	{
		// ------------------------------------------------
		MessageBox(NULL, TEXT("您的计算机的注册表上没有HKEY_LOCAL_MACHINE:Hardware\\DeviceMap\\SerialComm项"), TEXT("警告"), MB_OK);
		// ------------------------------------------------
	}
	//返回串口号
	// ----------------------------------------------------
	return comName;
}

// ---------------------------------------------------------------------------
//End Of File
