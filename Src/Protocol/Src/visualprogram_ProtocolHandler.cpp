#include "stdafx.h"
#include "visualprogram_ProtocolHandler.h"

using namespace visualprogram;


visualprogram::s2r_Dispatcher::s2r_Dispatcher()
	: cProtocolDispatcher(visualprogram::s2r_Dispatcher_ID, ePacketFormat::JSON)
{
	cProtocolDispatcher::GetDispatcherMap()->insert({s2r_Dispatcher_ID, this });
}

//------------------------------------------------------------------------
// 패킷의 프로토콜에 따라 해당하는 핸들러를 호출한다.
//------------------------------------------------------------------------
bool visualprogram::s2r_Dispatcher::Dispatch(cPacket &packet, const ProtocolHandlers &handlers)
{
	const int protocolId = packet.GetProtocolId();
	const int packetId = packet.GetPacketId();
	switch (packetId)
	{
	case 1281093745:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2r_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				Welcome_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.msg);
				SEND_HANDLER(s2r_ProtocolHandler, prtHandler, Welcome(data));
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

					Welcome_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "msg", data.msg);
					SEND_HANDLER(s2r_ProtocolHandler, prtHandler, Welcome(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 851424104:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2r_ProtocolHandler>(handlers, prtHandler))
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
				SEND_HANDLER(s2r_ProtocolHandler, prtHandler, AckLogin(data));
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
					SEND_HANDLER(s2r_ProtocolHandler, prtHandler, AckLogin(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 1974715764:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2r_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqVisualProgRun_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.nodeFile);
				SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqVisualProgRun(data));
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

					ReqVisualProgRun_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "nodeFile", data.nodeFile);
					SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqVisualProgRun(data));
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




visualprogram::r2s_Dispatcher::r2s_Dispatcher()
	: cProtocolDispatcher(visualprogram::r2s_Dispatcher_ID, ePacketFormat::JSON)
{
	cProtocolDispatcher::GetDispatcherMap()->insert({r2s_Dispatcher_ID, this });
}

//------------------------------------------------------------------------
// 패킷의 프로토콜에 따라 해당하는 핸들러를 호출한다.
//------------------------------------------------------------------------
bool visualprogram::r2s_Dispatcher::Dispatch(cPacket &packet, const ProtocolHandlers &handlers)
{
	const int protocolId = packet.GetProtocolId();
	const int packetId = packet.GetPacketId();
	switch (packetId)
	{
	case 1956887904:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<r2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqLogin_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.id);
				SEND_HANDLER(r2s_ProtocolHandler, prtHandler, ReqLogin(data));
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
					get(props, "id", data.id);
					SEND_HANDLER(r2s_ProtocolHandler, prtHandler, ReqLogin(data));
				} catch (...) {
					dbg::Logp("json packet parsing error\n");
				}
			}
		}
		break;

	case 1923274341:
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<r2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				AckVisualProgRun_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				marshalling::operator>>(packet, data.result);
				SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckVisualProgRun(data));
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

					AckVisualProgRun_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "result", data.result);
					SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckVisualProgRun(data));
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



