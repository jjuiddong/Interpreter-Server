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

	network2::cNetController netController;
	cRemoteInterpreter remoteInterpreter;
	if (!remoteInterpreter.Init(netController, url, port))
	{
		cout << "Error RemoteInterpreter Initialize" << endl;
		return 0;
	}

	cout << "Start Remote Interpreter" << endl;

	cTimer timer;
	timer.Create();
	while (g_isLoop)
	{
		const float dt = (float)timer.GetDeltaSeconds();
		netController.Process(dt);
		if (!remoteInterpreter.Update(dt))
			break;
		Sleep(1);
	}

	netController.Clear();
	dbg::TerminateLogThread();
	return 1;
}
