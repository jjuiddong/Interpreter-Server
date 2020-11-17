#include "stdafx.h"
#include "visualprogram_Protocol.h"
using namespace visualprogram;

//------------------------------------------------------------------------
// Protocol: RecvVisProgData
//------------------------------------------------------------------------
void visualprogram::w2s_Protocol::RecvVisProgData(netid targetId, bool isBinary, const double &lon, const double &lat, const double &altitude, const double &speed, const string &descript)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 2000 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, lon);
		marshalling::operator<<(packet, lat);
		marshalling::operator<<(packet, altitude);
		marshalling::operator<<(packet, speed);
		marshalling::operator<<(packet, descript);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "lon", lon);
			put(props, "lat", lat);
			put(props, "altitude", altitude);
			put(props, "speed", speed);
			put(props, "descript", descript);
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
void visualprogram::w2s_Protocol::AckLogin(netid targetId, bool isBinary, const string &id, const int &result)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 2001 );
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
// Protocol: ReqRun
//------------------------------------------------------------------------
void visualprogram::w2s_Protocol::ReqRun(netid targetId, bool isBinary, const sNodeFile &nodeFile)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 2010 );
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
void visualprogram::s2w_Protocol::ReqLogin(netid targetId, bool isBinary, const string &header, const string &id)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 1956887904 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, header);
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
			put(props, "header", header);
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
// Protocol: ReqVisProgData
//------------------------------------------------------------------------
void visualprogram::s2w_Protocol::ReqVisProgData(netid targetId, bool isBinary, const string &header)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 4069273153 );
	packet.SetPacketOption(0x01, (uint)isBinary);
	if (isBinary)
	{
		// marshaling binary
		marshalling::operator<<(packet, header);
		packet.EndPack();
		GetNode()->Send(targetId, packet);
	}
	else
	{
		// marshaling json
		using boost::property_tree::ptree;
		ptree props;
		try {
			put(props, "header", header);
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
// Protocol: AckRun
//------------------------------------------------------------------------
void visualprogram::s2w_Protocol::AckRun(netid targetId, bool isBinary, const int &result)
{
	cPacket packet(m_node->GetPacketHeader());
	packet.SetProtocolId( GetId() );
	packet.SetPacketId( 2011 );
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



