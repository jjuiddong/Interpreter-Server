
#include "stdafx.h"
#include "remoteinterpreter.h"


cRemoteInterpreter::cRemoteInterpreter()
{
}

cRemoteInterpreter::~cRemoteInterpreter()
{
	Clear();
}


// initialize interpreter server
// url: interpreter web server url
// port: interpreter web server port
bool cRemoteInterpreter::Init(const string &url, const int port)
{
	Clear();

	m_remoteDebugger.m_client.AddProtocolHandler(this);
	m_remoteDebugger.m_client.RegisterProtocol(&m_protocol);

	if (!m_remoteDebugger.InitHost(url, port, this, this))
	{
		return false;
	}

	return true;
}


// process
bool cRemoteInterpreter::Update()
{
	const bool result = m_remoteDebugger.Process();
	return result;
}


// wirte *.vprog file from sNodeFile
bool cRemoteInterpreter::WriteVisProgFile(const StrPath &fileName
	, const webvprog::sNodeFile &nodeFile)
{
	using namespace std;
	using namespace webvprog;

	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
		return false; // error occurred!!

	string tab = "\t";

	// symbol table, enum write
	for (auto &symbol : nodeFile.symbolTable)
	{
		if (vprog::eSymbolType::Enums == symbol.stype)
		{
			ofs << "define" << endl;
			tab = "\t";
			ofs << tab << "type Enum" << endl;
			ofs << tab << "name \"" << symbol.name << "\"" << endl;
			for (uint i = 0; i < symbol.values.size(); ++i) 
			{
				auto &item = symbol.values[i];
				ofs << tab << "attr" << endl;
				ofs << tab << "\tname \"" << item << "\"" << endl;
				ofs << tab << "\tvalue " << i << endl;
			}
			tab = "\t";
		}
	}

	for (auto &node : nodeFile.nodes)
	{
		ofs << "node\n";

		ofs << tab << "type " << vprog::eNodeType::ToString(node.nodeType) << endl;
		ofs << tab << "id " << node.id << endl;
		ofs << tab << "name \"" << node.name << "\"" << endl;
		ofs << tab << "rect 0 0 100 100" << endl;
		ofs << tab << "color 1 1 1 1" << endl;

		// input slot
		for (auto &slot : node.inputs)
		{
			ofs << tab << "input" << endl;
			tab = "\t\t";
			ofs << tab << "type " << vprog::ePinType::ToString(slot.type) << endl;
			//ofs << tab << "kind " << vprog::ePinKind::ToString(slot.kind) << endl;
			ofs << tab << "id " << slot.id << endl;
			ofs << tab << "name \"" << slot.name << "\"" << endl;

			// links
			set<int> links;
			for (auto &link : nodeFile.links)
				if (link.to == slot.id)
					links.insert(link.from);
			if (!links.empty())
			{
				ofs << tab << "links ";
				for (auto to : links)
					ofs << to;
				ofs << endl;
			}
			tab = "\t";
		}

		// output slot
		for (auto &slot : node.outputs)
		{
			ofs << tab << "output" << endl;
			tab = "\t\t";
			ofs << tab << "type " << vprog::ePinType::ToString(slot.type) << endl;
			//ofs << tab << "kind " << vprog::ePinKind::ToString(slot.kind) << endl;
			ofs << tab << "id " << slot.id << endl;
			ofs << tab << "name \"" << slot.name << "\"" << endl;

			// variable slot?
			if (!slot.varName.empty())
				ofs << tab << "varname \"" << slot.varName << "\"" << endl;

			// links
			set<int> links;
			for (auto &link : nodeFile.links)
				if (link.from == slot.id)
					links.insert(link.to);
			if (!links.empty())
			{
				ofs << tab << "links ";
				for (auto to : links)
					ofs << to << " ";
				ofs << endl;
			}
			tab = "\t";
		}
	}

	// symbol table, variable write
	for (auto &symbol : nodeFile.symbolTable)
	{
		if (vprog::IsVariable(symbol.stype))
		{
			ofs << "initvar" << endl;
			tab = "\t";
			ofs << tab << "scopename " << symbol.name << endl;
			ofs << tab << "name " << "out" << endl;
			string valueStr = common::variant2str(symbol.val);
			ofs << tab << "value \"" << valueStr << "\"" << endl;
			ofs << tab << "type " << vprog::eSymbolType::ToString(symbol.stype) << endl;
			tab = "\t";
		}
	}

	return true;
}


// receive from webserver
bool cRemoteInterpreter::Welcome(visualprogram::Welcome_Packet &packet)
{
	m_protocol.ReqLogin(network2::SERVER_NETID, false, "InterpreterServer");
	return true;
}


bool cRemoteInterpreter::AckLogin(visualprogram::AckLogin_Packet &packet)
{
	return true;
}


bool cRemoteInterpreter::ReqVisualProgRun(visualprogram::ReqVisualProgRun_Packet &packet)
{ 
	// nodeFile convert to visual programming file *.vprog
	WriteVisProgFile("test.vprog", packet.nodeFile);

	// generate intermediate code and write file
	vprog::cVProgFile vprogFile;
	common::script::cIntermediateCode icode;

	if (!vprogFile.Read("test.vprog"))
		goto $error;

	vprogFile.GenerateIntermediateCode(icode);
	if (!icode.Write("test.icode"))
		goto $error;

	if (!m_remoteDebugger.LoadIntermediateCode("test.icode"))
		goto $error;

	//// send icode to webserver
	//m_protocol.AckRun(network2::SERVER_NETID, true, 1, icode);

	//m_interpreter.Init("test.icode", this, this);
	//m_interpreter.Run();
	//script::cEvent evt("Tick Event");
	//m_interpreter.PushEvent(evt);

	//for (auto &vm : m_interpreter.m_vms)
	//{
	//	webvprog::sRegister reg;
	//	reg.idx = vm->m_reg.idx;
	//	reg.cmp = vm->m_reg.cmp;
	//	for (uint i = 0; i < ARRAYSIZE(vm->m_reg.val); ++i)
	//		reg.val[i] = common::copyvariant(vm->m_reg.val[i]);
	//	m_protocol.SyncRegister(network2::SERVER_NETID, true, 0, reg);
	//	break;
	//}
	m_protocol.AckVisualProgRun(network2::SERVER_NETID, false, 1);
	return true;


$error:
	m_protocol.AckVisualProgRun(network2::SERVER_NETID, false, 0);
	return true; 
}


//// ReqEvent packet handling
//bool cRemoteInterpreter::ReqEvent(visualprogram::ReqEvent_Packet &packet) 
//{
//	//script::cEvent evt(packet.eventName);
//	//m_interpreter.PushEvent(evt);
//	return true; 
//}


// cInterpreter::iFunctionCallback overriding
int cRemoteInterpreter::Function(script::cSymbolTable &symbolTable
	, const string &scopeName
	, const string &funcName
	, void *arg)
{

	return 0;
}


void cRemoteInterpreter::Clear()
{
	m_remoteDebugger.Clear();
}
