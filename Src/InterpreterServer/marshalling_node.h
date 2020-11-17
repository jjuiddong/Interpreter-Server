//
// 2020-11-13, jjuiddong
// NodeFile marshalling
//
#pragma once


enum class eSymbolType {
	None, Bool, Int, Float, Enum, String
};


struct sSymbol {
	eSymbolType stype;
	string name;
	_variant_t val;
	vector<string> values;
};

struct sWidget {
	int id;
	Str32 name;
};

struct sSlot {
	int id;
	string name;
	BYTE kind;
	BYTE type;
};

struct sLink {
	int id;
	int from;
	int to;
};

struct sNode {
	int id;
	BYTE nodeType;
	string name;
	vector<sSlot> inputs;
	vector<sSlot> outputs;
	vector<sWidget> widgets;
};

struct sNodeFile {
	string version;
	string title;
	int offsetX;
	int offsetY;
	float scale;
	vector<sNode> nodes;
	vector<sLink> links;
	vector<sSymbol> symbolTable;
};


// json marshalling
namespace network2 {
	namespace marshalling_json
	{

		inline ptree& get(ptree &props, OUT sSymbol &rhs) {
			rhs.stype = (eSymbolType)props.get<BYTE>("stype", 0);
			rhs.name = props.get<string>("name", "name");
			return props;
		}

		inline ptree& get(ptree &props, OUT sLink &rhs) {
			rhs.id = props.get<int>("id", 0);
			rhs.from = props.get<int>("from", 0);
			rhs.to = props.get<int>("to", 0);
			return props;
		}

		inline ptree& get(ptree &props, OUT sWidget &rhs) {
			rhs.id = props.get<int>("id", 0);
			rhs.name = props.get<string>("name", "name");
			return props;
		}

		inline ptree& get(ptree &props, OUT sSlot &rhs) {
			rhs.id = props.get<int>("id", 0);
			rhs.name = props.get<string>("name", "name");
			rhs.kind = props.get<int>("kind", 0);
			rhs.type = props.get<int>("type", 0);
			return props;
		}

		inline ptree& get(ptree &props, OUT sNode &rhs) {
			ptree &inputs = props.get_child("inputs");
			for (auto it : inputs) {
				sSlot slot;
				get(it.second, slot);
				rhs.inputs.push_back(slot);
			}
			ptree &outputs = props.get_child("outputs");
			for (auto it : outputs) {
				sSlot slot;
				get(it.second, slot);
				rhs.outputs.push_back(slot);
			}
			ptree &widgets = props.get_child("widgets");
			for (auto it : widgets) {
				sWidget widget;
				get(it.second, widget);
				rhs.widgets.push_back(widget);
			}
			return props;
		}

		inline ptree& put(ptree &props, const char *typeName, const sNodeFile &rhs) {
			// nothing~
			return props;
		}

		inline ptree& get(ptree &props, const char *typeName, OUT sNodeFile &rhs) {

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
	}
}


// binary marshalling
namespace network2 {
	namespace marshalling {
		cPacket& operator<<(cPacket& packet, const sNodeFile& rhs);
		cPacket& operator>>(cPacket& packet, OUT sSymbol& rhs);
		cPacket& operator>>(cPacket& packet, OUT sLink& rhs);
		cPacket& operator>>(cPacket& packet, OUT sSlot& rhs);
		cPacket& operator>>(cPacket& packet, OUT sNode& rhs);
		cPacket& operator>>(cPacket& packet, OUT sNodeFile& rhs);
	}

	//------------------------------------------------------------------------------
	// implements

	inline cPacket& marshalling::operator<<(cPacket& packet, const sNodeFile& rhs) {
		return packet; // nothing~
	}

	inline cPacket& marshalling::operator>>(cPacket& packet, OUT sSymbol& rhs) {
		BYTE stype;
		packet >> stype;
		rhs.stype = (eSymbolType)stype;
		packet >> rhs.name;
		packet.Read4ByteAlign(); // after string parsing

		// parse value
		switch (rhs.stype) {
		case eSymbolType::Bool: rhs.val.vt = VT_BOOL; break;
		case eSymbolType::Int: rhs.val.vt = VT_INT; break;
		case eSymbolType::Float: rhs.val.vt = VT_R4; break;
		case eSymbolType::String: rhs.val.vt = VT_BSTR; break;
		case eSymbolType::Enum:
		case eSymbolType::None:
		default: rhs.val.vt = VT_EMPTY; break;
		}

		if (rhs.stype == eSymbolType::Enum)
		{
			MARSHALLING_BIN_GET_SEQ(packet, vector<string>, rhs.values);
			packet.Read4ByteAlign();
		}
		else if (rhs.val.vt != VT_EMPTY)
		{
			packet >> rhs.val;
		}

		return packet;
	}

	inline cPacket& marshalling::operator>>(cPacket& packet, OUT sLink& rhs) {
		packet >> rhs.id;
		packet >> rhs.from;
		packet >> rhs.to;
		return packet;
	}

	inline cPacket& marshalling::operator>>(cPacket& packet, OUT sSlot& rhs) {
		packet >> rhs.id;
		packet >> rhs.kind;
		packet >> rhs.type;
		packet >> rhs.name;
		packet.Read4ByteAlign(); // after string parsing
		return packet;
	}

	inline cPacket& marshalling::operator>>(cPacket& packet, OUT sNode& rhs) {
		packet >> rhs.id;
		packet >> rhs.nodeType;
		packet >> rhs.name;
		packet.Read4ByteAlign(); // after string parsing
		MARSHALLING_BIN_GET_SEQ(packet, vector<sSlot>, rhs.inputs);
		MARSHALLING_BIN_GET_SEQ(packet, vector<sSlot>, rhs.outputs);
		return packet;
	}

	inline cPacket& marshalling::operator>>(cPacket& packet, OUT sNodeFile& rhs) {

		packet >> rhs.version;
		packet.Read4ByteAlign(); // after string parsing
		packet >> rhs.title;
		packet.Read4ByteAlign(); // after string parsing
		packet >> rhs.offsetX;
		packet >> rhs.offsetY;
		packet >> rhs.scale;
		MARSHALLING_BIN_GET_SEQ(packet, vector<sNode>, rhs.nodes);
		MARSHALLING_BIN_GET_SEQ(packet, vector<sLink>, rhs.links);
		MARSHALLING_BIN_GET_SEQ(packet, vector<sSymbol>, rhs.symbolTable);

		return packet;
	}
}
