//
// 2020-11-13, jjuiddong
// Visual Programming Remote Interpreter
//	- visual program source download from webserver
//	- run visual program with script interpreter
//
#pragma once


class cRemoteInterpreter : public visualprogram::w2s_ProtocolHandler
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
	virtual bool RecvVisProgData(visualprogram::RecvVisProgData_Packet &packet) override;
	virtual bool AckLogin(visualprogram::AckLogin_Packet &packet) override;
	virtual bool ReqRun(visualprogram::ReqRun_Packet &packet) override;
	virtual bool ReqEvent(visualprogram::ReqEvent_Packet &packet) override;


public:
	network2::cNetController m_netController;
	network2::cWebClient m_client;
	visualprogram::s2w_Protocol m_protocol;
	cTimer m_timer;
	float m_syncTime;

	common::script::cInterpreter m_interpreter;
	common::script::cDebugger m_debugger;
	common::script::cIntermediateCode m_icode;
};
