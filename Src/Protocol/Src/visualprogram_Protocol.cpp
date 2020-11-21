#include "stdafx.h"
#include "visualprogram_Protocol.h"
using namespace visualprogram;

//------------------------------------------------------------------------
// Protocol: Welcome
//------------------------------------------------------------------------
void visualprogram::s2r_Protocol::Welcome(netid targetId, bool isBinary, const string &msg)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 1281093745 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, msg);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "msg", msg);
			stringstream ss;
			boost::property_tree::write_json(ss, props);
			packet << ss.str();
			packet.EndPack();
			GetNode()->Send(targetId, packet);
		} catch (...) {
			dbg::Logp("json packet maker error\n");
		}
	}
}

//------------------------------------------------------------------------
// Protocol: AckLogin
//------------------------------------------------------------------------
void visualprogram::s2r_Protocol::AckLogin(netid targetId, bool isBinary, const string &id, const int &result)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 851424104 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, id);
		marshalling::operator<<(packet, result);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "id", id);
			put(props, "result", result);
			stringstream ss;
			boost::property_tree::write_json(ss, props);
			packet << ss.str();
			packet.EndPack();
			GetNode()->Send(targetId, packet);
		} catch (...) {
			dbg::Logp("json packet maker error\n");
		}
	}
}

//------------------------------------------------------------------------
// Protocol: ReqVisualProgRun
//------------------------------------------------------------------------
void visualprogram::s2r_Protocol::ReqVisualProgRun(netid targetId, bool isBinary, const webvprog::sNodeFile &nodeFile)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 1974715764 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, nodeFile);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "nodeFile", nodeFile);
			stringstream ss;
			boost::property_tree::write_json(ss, props);
			packet << ss.str();
			packet.EndPack();
			GetNode()->Send(targetId, packet);
		} catch (...) {
			dbg::Logp("json packet maker error\n");
		}
	}
}



//------------------------------------------------------------------------
// Protocol: ReqLogin
//------------------------------------------------------------------------
void visualprogram::r2s_Protocol::ReqLogin(netid targetId, bool isBinary, const string &id)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 1956887904 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, id);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "id", id);
			stringstream ss;
			boost::property_tree::write_json(ss, props);
			packet << ss.str();
			packet.EndPack();
			GetNode()->Send(targetId, packet);
		} catch (...) {
			dbg::Logp("json packet maker error\n");
		}
	}
}

//------------------------------------------------------------------------
// Protocol: AckVisualProgRun
//------------------------------------------------------------------------
void visualprogram::r2s_Protocol::AckVisualProgRun(netid targetId, bool isBinary, const int &result)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 1923274341 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, result);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "result", result);
			stringstream ss;
			boost::property_tree::write_json(ss, props);
			packet << ss.str();
			packet.EndPack();
			GetNode()->Send(targetId, packet);
		} catch (...) {
			dbg::Logp("json packet maker error\n");
		}
	}
}



