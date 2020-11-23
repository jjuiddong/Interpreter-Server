//
// 2020-11-13, jjuiddong
// NodeFile marshalling
//
#pragma once


// json marshalling
namespace network2 {
	namespace marshalling_json
	{
		inline ptree& get(ptree &props, OUT webvprog::sSymbol &rhs) 
		{
			rhs.stype = (vprog::eSymbolType::Enum)props.get<BYTE>("stype", 0);
			rhs.name = props.get<string>("name", "name");
			return props;
		}

		inline ptree& get(ptree &props, OUT webvprog::sLink &rhs) 
		{
			rhs.id = props.get<int>("id", 0);
			rhs.from = props.get<int>("from", 0);
			rhs.to = props.get<int>("to", 0);
			return props;
		}

		inline ptree& get(ptree &props, OUT webvprog::sWidget &rhs) 
		{
			rhs.id = props.get<int>("id", 0);
			rhs.name = props.get<string>("name", "name");
			return props;
		}

		inline ptree& get(ptree &props, OUT webvprog::sSlot &rhs) 
		{
			rhs.id = props.get<int>("id", 0);
			rhs.name = props.get<string>("name", "name");
			rhs.kind = (vprog::ePinKind::Enum)props.get<int>("kind", 0);
			rhs.type = (vprog::ePinType::Enum)props.get<int>("type", 0);
			return props;
		}

		inline ptree& get(ptree &props, OUT webvprog::sNode &rhs) 
		{
			ptree &inputs = props.get_child("inputs");
			for (auto it : inputs) {
				webvprog::sSlot slot;
				get(it.second, slot);
				rhs.inputs.push_back(slot);
			}
			ptree &outputs = props.get_child("outputs");
			for (auto it : outputs) {
				webvprog::sSlot slot;
				get(it.second, slot);
				rhs.outputs.push_back(slot);
			}
			ptree &widgets = props.get_child("widgets");
			for (auto it : widgets) {
				webvprog::sWidget widget;
				get(it.second, widget);
				rhs.widgets.push_back(widget);
			}
			return props;
		}

		inline ptree& put(ptree &props, const char *typeName, const webvprog::sNodeFile &rhs) 
		{
			// nothing~
			return props;
		}

		inline ptree& get(ptree &props, const char *typeName, OUT webvprog::sNodeFile &rhs) 
		{
			using namespace webvprog;

			ptree &child = props.get_child(typeName);
			rhs.version = child.get<string>("version", "v1.0");
			rhs.title = child.get<string>("title", "title");
			rhs.offsetX = child.get<int>("offsetX", 0);
			rhs.offsetY = child.get<int>("offsetY", 0);
			rhs.scale = child.get<float>("scale", 0.f);

			// nodes
			ptree &nodes = child.get_child("nodes");
			for (auto it : nodes) {
				sNode node;
				get(it.second, node);
				rhs.nodes.push_back(node);
			}

			// links
			ptree &links = child.get_child("links");
			for (auto it : links) {
				sLink link;
				get(it.second, link);
				rhs.links.push_back(link);
			}

			// symbols
			ptree &symbols = child.get_child("symbols");
			for (auto it : symbols) {
				sSymbol symbol;
				get(it.second, symbol);
				rhs.symbolTable.push_back(symbol);
			}

			return props;
		}

		//inline ptree& put(ptree &props, const char *typeName, const script::cIntermediateCode &rhs) {return props;} // nothing
		//inline ptree& get(ptree &props, const char *typeName, OUT script::cIntermediateCode &rhs) {return props;} // nothing
		inline ptree& put(ptree &props, const char *typeName, const webvprog::sRegister &rhs) { return props; } // nothing
		inline ptree& get(ptree &props, const char *typeName, OUT webvprog::sRegister &rhs) { return props; } // nothing
	}
}


// binary marshalling
namespace network2 {
	namespace marshalling {

		//---------------------------------------------------------------------------------
		// <<
		inline cPacket& operator<<(cPacket& packet, const webvprog::sNodeFile &rhs) { return packet; } // nothing~

		inline cPacket& operator<<(cPacket& packet, const webvprog::sRegister &rhs)
		{
			packet << rhs.idx;
			packet << rhs.cmp;
			for (uint i = 0; i < ARRAYSIZE(rhs.val); ++i)
				packet << rhs.val[i];
			return packet;
		}

		//---------------------------------------------------------------------------------
		// >>
		inline cPacket& operator>>(cPacket& packet, OUT webvprog::sSymbol& rhs)
		{
			using namespace webvprog;

			BYTE stype;
			packet >> stype;
			rhs.stype = (vprog::eSymbolType::Enum)stype;
			packet >> rhs.name;
			packet.Read4ByteAlign(); // after string parsing

			// parse variant value
			bool b; int i; float f; string s;
			switch (rhs.stype) {
			case vprog::eSymbolType::Bool:
				packet >> b;
				rhs.val = b;
				break;
			case vprog::eSymbolType::Int:
				packet >> i;
				rhs.val = i;
				break;
			case vprog::eSymbolType::Float:
				packet >> f;
				rhs.val = f;
				break;
			case vprog::eSymbolType::String:
				packet >> s;
				rhs.val = (_bstr_t)s.c_str();
				packet.Read4ByteAlign();
				break;
			case vprog::eSymbolType::Enums:
			{
				MARSHALLING_BIN_GET_SEQ(packet, vector<string>, rhs.values);
				packet.Read4ByteAlign();
			}
			break;
			case vprog::eSymbolType::None:
			default: rhs.val.vt = VT_EMPTY; break;
			}

			return packet;
		}

		inline cPacket& operator>>(cPacket& packet, OUT webvprog::sLink& rhs)
		{
			packet >> rhs.id;
			packet >> rhs.from;
			packet >> rhs.to;
			return packet;
		}

		inline cPacket& operator>>(cPacket& packet, OUT webvprog::sSlot& rhs)
		{
			packet >> rhs.id;
			BYTE val;
			packet >> val;
			rhs.kind = (vprog::ePinKind::Enum)val;
			packet >> val;
			rhs.type = (vprog::ePinType::Enum)val;
			packet >> rhs.name;
			packet.Read4ByteAlign(); // after string parsing
			return packet;
		}

		inline cPacket& operator>>(cPacket& packet, OUT webvprog::sNode& rhs)
		{
			packet >> rhs.id;
			BYTE nodeType;
			packet >> nodeType;
			rhs.nodeType = (vprog::eNodeType::Enum) nodeType;
			packet >> rhs.name;
			packet.Read4ByteAlign(); // after string parsing
			packet >> rhs.desc;
			packet.Read4ByteAlign(); // after string parsing
			MARSHALLING_BIN_GET_SEQ(packet, vector<webvprog::sSlot>, rhs.inputs);
			MARSHALLING_BIN_GET_SEQ(packet, vector<webvprog::sSlot>, rhs.outputs);

			// variable type? parse variable symbol name
			if (rhs.nodeType == vprog::eNodeType::Variable)
			{
				// tricky code, variable node output is only one
				if (rhs.outputs.size() > 0)
				{
					packet >> rhs.outputs.back().varName;
				}
				else
				{
					// error occurred!!
					string temp;
					packet >> temp;
				}
				packet.Read4ByteAlign(); // after string parsing
			}

			return packet;
		}

		inline cPacket& operator>>(cPacket& packet
			, OUT webvprog::sNodeFile& rhs)
		{
			packet >> rhs.version;
			packet.Read4ByteAlign(); // after string parsing
			packet >> rhs.title;
			packet.Read4ByteAlign(); // after string parsing
			packet >> rhs.offsetX;
			packet >> rhs.offsetY;
			packet >> rhs.scale;
			MARSHALLING_BIN_GET_SEQ(packet, vector<webvprog::sNode>, rhs.nodes);
			MARSHALLING_BIN_GET_SEQ(packet, vector<webvprog::sLink>, rhs.links);
			MARSHALLING_BIN_GET_SEQ(packet, vector<webvprog::sSymbol>, rhs.symbolTable);
			return packet;
		}

		inline cPacket& operator>>(cPacket& packet, OUT webvprog::sRegister& rhs) { return packet; } // nothing

	}
}
