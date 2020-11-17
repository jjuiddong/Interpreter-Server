//
// 2020-11-13, jjuiddong
// Visual Programming Interpreter Server
//
#pragma once


class cInterpreterServer : public visualprogram::w2s_ProtocolHandler
						, public all::AllProtocolDisplayer
{
public:
	cInterpreterServer();
	virtual ~cInterpreterServer();

	bool Init(const string &url, const int port);
	bool Update();
	void Clear();


protected:
	// visualprogram protocol handler
	virtual bool RecvVisProgData(visualprogram::RecvVisProgData_Packet &packet) override;
	virtual bool AckLogin(visualprogram::AckLogin_Packet &packet) override;
	virtual bool ReqRun(visualprogram::ReqRun_Packet &packet) override;


public:
	network2::cNetController m_netController;
	network2::cWebClient m_client;
	visualprogram::s2w_Protocol m_protocol;
	cTimer m_timer;
};
