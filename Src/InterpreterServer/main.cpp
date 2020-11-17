//
// 2020-11-13, jjuiddong
// interpreter server with websocket
//
//
#include "stdafx.h"
#include "interpreterserver.h"

using namespace std;
using namespace network2;

bool g_isLoop = true;
BOOL CtrlHandler(DWORD fdwCtrlType);
int ThreadFunction();

int main()
{
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		cout << "SetConsoleCtrlHandler failed, code : " << GetLastError() << endl;
		return -1;
	}
	std::thread th(ThreadFunction);
	th.join();

	cout << "Finish Server\n";
	return 0;
}


BOOL CtrlHandler(DWORD fdwCtrlType)
{
	g_isLoop = false;
	return TRUE;
}


// server thread function
int ThreadFunction()
{
	const string url = "jjuiddong.iptime.org";
	const int port = 4001;

	cInterpreterServer server;
	if (!server.Init(url, port))
	{
		cout << "Error InterpreterServer Initialize" << endl;
		return 0;
	}

	cout << "Start Interpreter Server" << endl;

	while (g_isLoop)
	{
		if (!server.Update())
			break;
		Sleep(1);
	}

	return 1;
}
