// IOCP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "IOCPBase.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
using namespace std;

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

class CMyServer : public IOCPBase
{
public:
	// 新连接
	void OnConnectionEstablished(SocketContext *sockContext)
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout << setw(4) << sys.wYear << "-" << setw(2) << sys.wMonth << "-";
		cout << setw(2) << sys.wDay << " ";
		cout << setw(2) << sys.wHour << ":" << setw(2) << sys.wMinute << ":";
		cout << setw(2) << sys.wSecond << "." << setw(3) << sys.wMilliseconds << ": ";
		cout << "Accept a connection，Current connects：" << GetConnectCnt() << endl;
		//printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：Accept a connection，Current connects：%d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, GetConnectCnt());
	}

	// 连接关闭
	void OnConnectionClosed(SocketContext *sockContext)
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout << setw(4) << sys.wYear << "-" << setw(2) << sys.wMonth << "-";
		cout << setw(2) << sys.wDay << " ";
		cout << setw(2) << sys.wHour << ":" << setw(2) << sys.wMinute << ":";
		cout << setw(2) << sys.wSecond << "." << setw(3) << sys.wMilliseconds << ": ";
		cout << "a connection closed！" << endl;
		cout << "Current connects：" << GetConnectCnt() << endl;
		//printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：A connection had closed，Current connects：%d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, GetConnectCnt());
	}

	// 连接上发生错误
	void OnConnectionError(SocketContext *sockContext, int error)
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout << setw(4) << sys.wYear << "-" << setw(2) << sys.wMonth << "-";
		cout << setw(2) << sys.wDay << " ";
		cout << setw(2) << sys.wHour << ":" << setw(2) << sys.wMinute << ":";
		cout << setw(2) << sys.wSecond << "." << setw(3) << sys.wMilliseconds << ": ";
		cout << "a connection erro："<< error << endl;
		cout << "Current connects：" << GetConnectCnt() << endl;
		//printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：A connection erro： %d，Current connects：%d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, error, GetConnectCnt());
	}

	// 读操作完成
	void OnRecvCompleted(SocketContext *sockContext, IOContext *ioContext)
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout << setw(4) << sys.wYear << "-" << setw(2) << sys.wMonth << "-";
		cout << setw(2) << sys.wDay << " ";
		cout << setw(2) << sys.wHour << ":" << setw(2) << sys.wMinute << ":";
		cout << setw(2) << sys.wSecond << "." << setw(3) << sys.wMilliseconds << ": ";
		cout << "Recv data！" << endl;
		cout << ioContext->wsaBuf.buf << endl;
		//printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：Recv data： %s \n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, ioContext->wsaBuf.buf);
	}

	// 写操作完成
	void OnSendCompleted(SocketContext *sockContext, IOContext *ioContext)
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout << setw(4) << sys.wYear << "-" << setw(2) << sys.wMonth << "-";
		cout << setw(2) << sys.wDay << " ";
		cout << setw(2) << sys.wHour << ":" << setw(2) << sys.wMinute << ":";
		cout << setw(2) << sys.wSecond << "." << setw(3) << sys.wMilliseconds << ": ";
		cout << "Send data successd！" << endl;
	}

};
	
int main()
{
	CMyServer *pServer = new CMyServer;

	// 开启服务
	if (pServer->Start())
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：Server start succussed on port:%d... \n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, pServer->GetPort());
	}
	else
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：Server start failed！\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
		return 0;
	}

	// 创建事件对象，让ServerShutdown程序能够关闭自己
	HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, L"ShutdownEvent");
	::WaitForSingleObject(hEvent, INFINITE);
	::CloseHandle(hEvent);

	// 关闭服务
	pServer->Stop();
	delete pServer;

	SYSTEMTIME sys;
	GetLocalTime(&sys);
	printf("%4d-%02d-%02d %02d:%02d:%02d.%03d：Server Closed \n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
    return 0;
}

