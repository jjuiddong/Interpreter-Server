//
// 2020-11-13, jjuiddong
// Visual Programming Remote Interpreter
//	- visual program source download from webserver
//	- run visual program with script interpreter
//
// 2021-09-17
//	- refactoring, no compile error, but not execute
//
#pragma once


class cRemoteInterpreter : public visualprogram::s2r_ProtocolHandler
						, public all::AllProtocolDisplayer
						, public script::iFunctionCallback
{
public:
	cRemoteInterpreter();
	virtual ~cRemoteInterpreter();

	bool Init(network2::cNetController &netController
		, const string &url, const int port);
	bool Update(const float deltaSeconds);
	void Clear();


protected:
	bool WriteVisProgFile(const StrPath &fileName, const webvprog::sNodeFile &nodeFile);

	// interpreter function callback
	virtual script::eCallbackState Function(script::cVirtualMachine &vm
		, const string &scopeName
		, const string &funcName
		, void *arg) override;

	// visualprogram protocol handler
	virtual bool Welcome(visualprogram::Welcome_Packet &packet) override;
	virtual bool AckLogin(visualprogram::AckLogin_Packet &packet) override;
	virtual bool ReqRunVisualProg(visualprogram::ReqRunVisualProg_Packet &packet) override;
	virtual bool ReqStopVisualProg(visualprogram::ReqStopVisualProg_Packet &packet) override;
	virtual bool ReqRunVisualProgStream(visualprogram::ReqRunVisualProgStream_Packet &packet) override;

public:
	network2::cRemoteDebugger2 m_remoteDebugger;
	visualprogram::r2s_Protocol m_protocol;
	vector<BYTE> m_nodeFileStream;
};
