//
// 2020-11-17, jjuiddong
// web visual program definition
//	- webserver, webclient visual program node data definition
//	- this node data different to vprog::~
//
#pragma once


namespace webvprog 
{

	// todo: variant type, bstr memory leak bug
	// variant bst copy, clean code needed
	struct sSymbol {
		vprog::eSymbolType::Enum stype;
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
		string varName; // variable slot? variable symbol name
		vprog::ePinKind::Enum kind;
		vprog::ePinType::Enum type;
	};

	struct sLink {
		int id;
		int from;
		int to;
	};

	struct sNode {
		int id;
		vprog::eNodeType::Enum nodeType;
		string name;
		string varName; // if variable node, variable symbol name
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

}
