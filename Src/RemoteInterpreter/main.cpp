//
// 2020-11-13, jjuiddong
// remote interpreter with websocket
//
//
#include "stdafx.h"
#include "remoteinterpreter.h"

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

	cRemoteInterpreter remoteInterpreter;
	if (!remoteInterpreter.Init(url, port))
	{
		cout << "Error RemoteInterpreter Initialize" << endl;
		return 0;
	}

	cout << "Start Remote Interpreter" << endl;

	while (g_isLoop)
	{
		if (!remoteInterpreter.Update())
			break;
		Sleep(1);
	}

	dbg::TerminateLogThread();
	return 1;
}
