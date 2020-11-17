#include "stdafx.h"
#include "visualprogram_ProtocolHandler.h"

using namespace visualprogram;


visualprogram::w2s_Dispatcher::w2s_Dispatcher()
	: cProtocolDispatcher(visualprogram::w2s_Dispatcher_ID, ePacketFormat::JSON)
{
	cProtocolDispatcher::GetDispatcherMap()->insert({w2s_Dispatcher_ID, this });
}

//------------------------------------------------------------------------
// 패킷의 프로토콜에 따라 해당하는 핸들러를 호출한다.
//------------------------------------------------------------------------
bool visualprogram::w2s_Dispatcher::Dispatch(cPacket &packet, const ProtocolHandlers &handlers)
{
	const int protocolId = packet.GetProtocolId();
	const int packetId = packet.GetPacketId();
	switch (packetId)
	{
	case 2000:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<w2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				RecvVisProgData_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.lon);
				marshalling::operator>>(packet, data.lat);
				marshalling::operator>>(packet, data.altitude);
				marshalling::operator>>(packet, data.speed);
				marshalling::operator>>(packet, data.descript);
				SEND_HANDLER(w2s_ProtocolHandler, prtHandler, RecvVisProgData(data));
			}
			else
			{
				// json format packet parsing using property_tree
				using boost::property_tree::ptree;
				ptree root;

				try {
					string str;
					packet >> str;
					stringstream ss(str);
					
					boost::property_tree::read_json(ss, root);
					ptree &props = root.get_child("");

					RecvVisProgData_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "lon", data.lon);
					get(props, "lat", data.lat);
					get(props, "altitude", data.altitude);
					get(props, "speed", data.speed);
					get(props, "descript", data.descript);
					SEND_HANDLER(w2s_ProtocolHandler, prtHandler, RecvVisProgData(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 2001:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<w2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				AckLogin_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.id);
				marshalling::operator>>(packet, data.result);
				SEND_HANDLER(w2s_ProtocolHandler, prtHandler, AckLogin(data));
			}
			else
			{
				// json format packet parsing using property_tree
				using boost::property_tree::ptree;
				ptree root;

				try {
					string str;
					packet >> str;
					stringstream ss(str);
					
					boost::property_tree::read_json(ss, root);
					ptree &props = root.get_child("");

					AckLogin_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "id", data.id);
					get(props, "result", data.result);
					SEND_HANDLER(w2s_ProtocolHandler, prtHandler, AckLogin(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 2010:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<w2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqRun_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.nodeFile);
				SEND_HANDLER(w2s_ProtocolHandler, prtHandler, ReqRun(data));
			}
			else
			{
				// json format packet parsing using property_tree
				using boost::property_tree::ptree;
				ptree root;

				try {
					string str;
					packet >> str;
					stringstream ss(str);
					
					boost::property_tree::read_json(ss, root);
					ptree &props = root.get_child("");

					ReqRun_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "nodeFile", data.nodeFile);
					SEND_HANDLER(w2s_ProtocolHandler, prtHandler, ReqRun(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	default:
		assert(0);
		break;
	}
	return true;
}




visualprogram::s2w_Dispatcher::s2w_Dispatcher()
	: cProtocolDispatcher(visualprogram::s2w_Dispatcher_ID, ePacketFormat::JSON)
{
	cProtocolDispatcher::GetDispatcherMap()->insert({s2w_Dispatcher_ID, this });
}

//------------------------------------------------------------------------
// 패킷의 프로토콜에 따라 해당하는 핸들러를 호출한다.
//------------------------------------------------------------------------
bool visualprogram::s2w_Dispatcher::Dispatch(cPacket &packet, const ProtocolHandlers &handlers)
{
	const int protocolId = packet.GetProtocolId();
	const int packetId = packet.GetPacketId();
	switch (packetId)
	{
	case 1956887904:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2w_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqLogin_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.header);
				marshalling::operator>>(packet, data.id);
				SEND_HANDLER(s2w_ProtocolHandler, prtHandler, ReqLogin(data));
			}
			else
			{
				// json format packet parsing using property_tree
				using boost::property_tree::ptree;
				ptree root;

				try {
					string str;
					packet >> str;
					stringstream ss(str);
					
					boost::property_tree::read_json(ss, root);
					ptree &props = root.get_child("");

					ReqLogin_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "header", data.header);
					get(props, "id", data.id);
					SEND_HANDLER(s2w_ProtocolHandler, prtHandler, ReqLogin(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 4069273153:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2w_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqVisProgData_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.header);
				SEND_HANDLER(s2w_ProtocolHandler, prtHandler, ReqVisProgData(data));
			}
			else
			{
				// json format packet parsing using property_tree
				using boost::property_tree::ptree;
				ptree root;

				try {
					string str;
					packet >> str;
					stringstream ss(str);
					
					boost::property_tree::read_json(ss, root);
					ptree &props = root.get_child("");

					ReqVisProgData_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "header", data.header);
					SEND_HANDLER(s2w_ProtocolHandler, prtHandler, ReqVisProgData(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 2011:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2w_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				AckRun_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.result);
				SEND_HANDLER(s2w_ProtocolHandler, prtHandler, AckRun(data));
			}
			else
			{
				// json format packet parsing using property_tree
				using boost::property_tree::ptree;
				ptree root;

				try {
					string str;
					packet >> str;
					stringstream ss(str);
					
					boost::property_tree::read_json(ss, root);
					ptree &props = root.get_child("");

					AckRun_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "result", data.result);
					SEND_HANDLER(s2w_ProtocolHandler, prtHandler, AckRun(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	default:
		assert(0);
		break;
	}
	return true;
}



