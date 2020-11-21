//
// 2020-11-17, jjuiddong
// web visual program definition
//	- webserver, webclient visual program node data definition
//	- this node data different to vprog::~
//
#pragma once


namespace webvprog 
{

	// virtual machine register information
	struct sRegister {
		uint idx; // instruction command index
		bool cmp; // compare output flag
		variant_t val[10]; // register

		sRegister() {}
		sRegister(const sRegister &rhs) {
			operator=(rhs);
		}
		~sRegister() {
			for (uint i = 0; i < ARRAYSIZE(val); ++i)
				common::clearvariant(val[i]);
		}
		sRegister& operator=(const sRegister &rhs) {
			if (this != &rhs) {
				idx = rhs.idx;
				cmp = rhs.cmp;
				for (uint i = 0; i < ARRAYSIZE(rhs.val); ++i)
					val[i] = common::copyvariant(rhs.val[i]);
			}
			return *this;
		}
	};

	// symbol table symbol information
	struct sSymbol {
		vprog::eSymbolType::Enum stype;
		string name;
		_variant_t val;
		vector<string> values;

		sSymbol() {}
		sSymbol(const sSymbol &rhs) {
			operator=(rhs);
		}
		~sSymbol() {
			common::clearvariant(val);
		}
		sSymbol& operator=(const sSymbol &rhs) {
			if (this != &rhs) {
				stype = rhs.stype;
				name = rhs.name;
				val = common::copyvariant(rhs.val);
				values = rhs.values;
			}
			return *this;
		}
	};

	// node widget
	struct sWidget {
		int id;
		Str32 name;
	};

	// node slot
	struct sSlot {
		int id;
		string name;
		string varName; // variable slot? variable symbol name
		vprog::ePinKind::Enum kind;
		vprog::ePinType::Enum type;
	};

	// node link
	struct sLink {
		int id;
		int from;
		int to;
	};

	// visual program node
	struct sNode {
		int id;
		vprog::eNodeType::Enum nodeType;
		string name;
		string varName; // if variable node, variable symbol name
		vector<sSlot> inputs;
		vector<sSlot> outputs;
		vector<sWidget> widgets;
	};

	// visual program node data file information
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

}
