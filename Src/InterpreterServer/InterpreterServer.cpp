
#include "stdafx.h"
#include "interpreterserver.h"


cInterpreterServer::cInterpreterServer()
{
}

cInterpreterServer::~cInterpreterServer()
{
	Clear();
}


// initialize interpreter server
// url: interpreter web server url
// port: interpreter web server port
bool cInterpreterServer::Init(const string &url, const int port)
{
	Clear();

	m_timer.Create();
	m_client.AddProtocolHandler(this);
	m_client.RegisterProtocol(&m_protocol);

	if (!m_netController.StartWebClient(&m_client, url, port))
	{
		dbg::Logc(2, "Error WebClient Connection url:%s, port:%d\n", url.c_str(), port);
		return false;
	}

	return true;
}


// process
bool cInterpreterServer::Update()
{
	const double dt = m_timer.GetDeltaSeconds();
	m_netController.Process((float)dt);
	return m_client.IsFailConnection()? false : true;
}


// receive from webserver
bool cInterpreterServer::RecvVisProgData(visualprogram::RecvVisProgData_Packet &packet)
{
	m_protocol.ReqLogin(network2::SERVER_NETID, false, "ReqLogin", "InterpreterServer");

	return true;
}


bool cInterpreterServer::AckLogin(visualprogram::AckLogin_Packet &packet)
{
	return true;
}


bool cInterpreterServer::ReqRun(visualprogram::ReqRun_Packet &packet)
{ 

	return true;
}


void cInterpreterServer::Clear()
{
	m_client.Close();
	m_netController.Clear();
}
