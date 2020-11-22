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
static const int s2r_Dispatcher_ID = 1000;

// Protocol Dispatcher
class s2r_Dispatcher: public network2::cProtocolDispatcher
{
public:
	s2r_Dispatcher();
protected:
	virtual bool Dispatch(cPacket &packet, const ProtocolHandlers &handlers) override;
};
static s2r_Dispatcher g_visualprogram_s2r_Dispatcher;


// ProtocolHandler
class s2r_ProtocolHandler : virtual public network2::iProtocolHandler
{
public:
	friend class s2r_Dispatcher;
	s2r_ProtocolHandler() { m_format = ePacketFormat::JSON; }
	virtual bool Welcome(visualprogram::Welcome_Packet &packet) { return true; }
	virtual bool AckLogin(visualprogram::AckLogin_Packet &packet) { return true; }
	virtual bool ReqRunVisualProg(visualprogram::ReqRunVisualProg_Packet &packet) { return true; }
	virtual bool ReqStopVisualProg(visualprogram::ReqStopVisualProg_Packet &packet) { return true; }
};


static const int r2s_Dispatcher_ID = 2000;

// Protocol Dispatcher
class r2s_Dispatcher: public network2::cProtocolDispatcher
{
public:
	r2s_Dispatcher();
protected:
	virtual bool Dispatch(cPacket &packet, const ProtocolHandlers &handlers) override;
};
static r2s_Dispatcher g_visualprogram_r2s_Dispatcher;


// ProtocolHandler
class r2s_ProtocolHandler : virtual public network2::iProtocolHandler
{
public:
	friend class r2s_Dispatcher;
	r2s_ProtocolHandler() { m_format = ePacketFormat::JSON; }
	virtual bool ReqLogin(visualprogram::ReqLogin_Packet &packet) { return true; }
	virtual bool AckRunVisualProg(visualprogram::AckRunVisualProg_Packet &packet) { return true; }
	virtual bool AckStopVisualProg(visualprogram::AckStopVisualProg_Packet &packet) { return true; }
};


}
