#include "stdafx.h"
#include "visualprogram_ProtocolHandler.h"

using namespace visualprogram;


cPacketHeaderJson visualprogram::s2r_Dispatcher::s_packetHeader;
visualprogram::s2r_Dispatcher::s2r_Dispatcher()
	: cProtocolDispatcher(visualprogram::s2r_Dispatcher_ID, ePacketFormat::JSON)
{
	cProtocolDispatcher::GetDispatcherMap()->insert({s2r_Dispatcher_ID, this});
	cProtocolDispatcher::GetPacketHeaderMap()->insert({s2r_Dispatcher_ID, &s_packetHeader});
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
	case 1281093745: // Welcome
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
				packet.Alignment4(); // set 4byte alignment
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
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 851424104: // AckLogin
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
				packet.Alignment4(); // set 4byte alignment
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
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 2250021743: // ReqRunVisualProg
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2r_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqRunVisualProg_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				packet.Alignment4(); // set 4byte alignment
				marshalling::operator>>(packet, data.nodeFile);
				SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqRunVisualProg(data));
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

					ReqRunVisualProg_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "nodeFile", data.nodeFile);
					SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqRunVisualProg(data));
				} catch (...) {
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 3686541167: // ReqRunVisualProgStream
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2r_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqRunVisualProgStream_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				packet.Alignment4(); // set 4byte alignment
				marshalling::operator>>(packet, data.count);
				marshalling::operator>>(packet, data.index);
				marshalling::operator>>(packet, data.data);
				SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqRunVisualProgStream(data));
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

					ReqRunVisualProgStream_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "count", data.count);
					get(props, "index", data.index);
					get(props, "data", data.data);
					SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqRunVisualProgStream(data));
				} catch (...) {
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 4258374867: // ReqStopVisualProg
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<s2r_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				ReqStopVisualProg_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				packet.Alignment4(); // set 4byte alignment
				SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqStopVisualProg(data));
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

					ReqStopVisualProg_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					SEND_HANDLER(s2r_ProtocolHandler, prtHandler, ReqStopVisualProg(data));
				} catch (...) {
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
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




cPacketHeaderJson visualprogram::r2s_Dispatcher::s_packetHeader;
visualprogram::r2s_Dispatcher::r2s_Dispatcher()
	: cProtocolDispatcher(visualprogram::r2s_Dispatcher_ID, ePacketFormat::JSON)
{
	cProtocolDispatcher::GetDispatcherMap()->insert({r2s_Dispatcher_ID, this});
	cProtocolDispatcher::GetPacketHeaderMap()->insert({r2s_Dispatcher_ID, &s_packetHeader});
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
	case 1956887904: // ReqLogin
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
				packet.Alignment4(); // set 4byte alignment
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
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 3863877132: // AckRunVisualProg
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<r2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				AckRunVisualProg_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				packet.Alignment4(); // set 4byte alignment
				marshalling::operator>>(packet, data.result);
				SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckRunVisualProg(data));
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

					AckRunVisualProg_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "result", data.result);
					SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckRunVisualProg(data));
				} catch (...) {
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 3454830338: // AckRunVisualProgStream
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<r2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				AckRunVisualProgStream_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				packet.Alignment4(); // set 4byte alignment
				marshalling::operator>>(packet, data.result);
				SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckRunVisualProgStream(data));
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

					AckRunVisualProgStream_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "result", data.result);
					SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckRunVisualProgStream(data));
				} catch (...) {
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
				}
			}
		}
		break;

	case 1895439953: // AckStopVisualProg
		{
			ProtocolHandlers prtHandler;
			if (!HandlerMatching<r2s_ProtocolHandler>(handlers, prtHandler))
				return false;

			SetCurrentDispatchPacket( &packet );

			const bool isBinary = packet.GetPacketOption(0x01) > 0;
			if (isBinary)
			{
				// binary parsing
				AckStopVisualProg_Packet data;
				data.pdispatcher = this;
				data.senderId = packet.GetSenderId();
				packet.Alignment4(); // set 4byte alignment
				marshalling::operator>>(packet, data.result);
				SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckStopVisualProg(data));
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

					AckStopVisualProg_Packet data;
					data.pdispatcher = this;
					data.senderId = packet.GetSenderId();
					get(props, "result", data.result);
					SEND_HANDLER(r2s_ProtocolHandler, prtHandler, AckStopVisualProg(data));
				} catch (...) {
					dbg::Logp("json packet parsing error packetid = %lu\n", packetId);
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



