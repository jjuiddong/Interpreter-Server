//
// 2020-11-13, jjuiddong
// Visual Programming Remote Interpreter
//	- visual program source download from webserver
//	- run visual program with script interpreter
//
#pragma once


class cRemoteInterpreter : public visualprogram::s2r_ProtocolHandler
						, public all::AllProtocolDisplayer
						, public script::iFunctionCallback
{
public:
	cRemoteInterpreter();
	virtual ~cRemoteInterpreter();

	bool Init(const string &url, const int port);
	bool Update();
	void Clear();


protected:
	bool WriteVisProgFile(const StrPath &fileName, const webvprog::sNodeFile &nodeFile);

	// interpreter function callback
	virtual int Function(script::cSymbolTable &symbolTable
		, const string &scopeName
		, const string &funcName
		, void *arg) override;

	// visualprogram protocol handler
	virtual bool Welcome(visualprogram::Welcome_Packet &packet) override;
	virtual bool AckLogin(visualprogram::AckLogin_Packet &packet) override;
	virtual bool ReqVisualProgRun(visualprogram::ReqVisualProgRun_Packet &packet) override;


public:
	network2::cRemoteDebugger2 m_remoteDebugger;
	visualprogram::r2s_Protocol m_protocol;
};
