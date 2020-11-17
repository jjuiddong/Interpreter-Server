//------------------------------------------------------------------------
// Name:    visualprogram_ProtocolHandler.h
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
#pragma once

#include "visualprogram_ProtocolData.h"

namespace visualprogram {

using namespace network2;
using namespace marshalling_json;
static const int w2s_Dispatcher_ID = 1000;

// Protocol Dispatcher
class w2s_Dispatcher: public network2::cProtocolDispatcher
{
public:
	w2s_Dispatcher();
protected:
	virtual bool Dispatch(cPacket &packet, const ProtocolHandlers &handlers) override;
};
static w2s_Dispatcher g_visualprogram_w2s_Dispatcher;


// ProtocolHandler
class w2s_ProtocolHandler : virtual public network2::iProtocolHandler
{
public:
	friend class w2s_Dispatcher;
	w2s_ProtocolHandler() { m_format = ePacketFormat::JSON; }
	virtual bool RecvVisProgData(visualprogram::RecvVisProgData_Packet &packet) { return true; }
	virtual bool AckLogin(visualprogram::AckLogin_Packet &packet) { return true; }
	virtual bool ReqRun(visualprogram::ReqRun_Packet &packet) { return true; }
};


static const int s2w_Dispatcher_ID = 2000;

// Protocol Dispatcher
class s2w_Dispatcher: public network2::cProtocolDispatcher
{
public:
	s2w_Dispatcher();
protected:
	virtual bool Dispatch(cPacket &packet, const ProtocolHandlers &handlers) override;
};
static s2w_Dispatcher g_visualprogram_s2w_Dispatcher;


// ProtocolHandler
class s2w_ProtocolHandler : virtual public network2::iProtocolHandler
{
public:
	friend class s2w_Dispatcher;
	s2w_ProtocolHandler() { m_format = ePacketFormat::JSON; }
	virtual bool ReqLogin(visualprogram::ReqLogin_Packet &packet) { return true; }
	virtual bool ReqVisProgData(visualprogram::ReqVisProgData_Packet &packet) { return true; }
	virtual bool AckRun(visualprogram::AckRun_Packet &packet) { return true; }
};


}
