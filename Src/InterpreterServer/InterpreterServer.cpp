
#include "stdafx.h"
#include "interpreterserver.h"


cInterpreterServer::cInterpreterServer()
{
}

cInterpreterServer::~cInterpreterServer()
{
	Clear();
}


// initialize interpreter server
// url: interpreter web server url
// port: interpreter web server port
bool cInterpreterServer::Init(const string &url, const int port)
{
	Clear();

	m_timer.Create();
	m_client.AddProtocolHandler(this);
	m_client.RegisterProtocol(&m_protocol);

	if (!m_netController.StartWebClient(&m_client, url, port))
	{
		dbg::Logc(2, "Error WebClient Connection url:%s, port:%d\n", url.c_str(), port);
		return false;
	}

	return true;
}


// process
bool cInterpreterServer::Update()
{
	const float dt = (float)m_timer.GetDeltaSeconds();
	m_netController.Process(dt);
	m_interpreter.Process(dt);

	return m_client.IsFailConnection()? false : true;
}


// wirte *.vprog file from sNodeFile
bool cInterpreterServer::WriteVisProgFile(const StrPath &fileName
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
			ofs << tab << "kind " << vprog::ePinKind::ToString(slot.kind) << endl;
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
			ofs << tab << "kind " << vprog::ePinKind::ToString(slot.kind) << endl;
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
bool cInterpreterServer::RecvVisProgData(visualprogram::RecvVisProgData_Packet &packet)
{
	m_protocol.ReqLogin(network2::SERVER_NETID, false, "ReqLogin", "InterpreterServer");
	return true;
}


bool cInterpreterServer::AckLogin(visualprogram::AckLogin_Packet &packet)
{
	return true;
}


bool cInterpreterServer::ReqRun(visualprogram::ReqRun_Packet &packet)
{
	// nodeFile convert to visual programming file *.vprog
	WriteVisProgFile("test.vprog", packet.nodeFile);

	// generate intermediate code and write file
	vprog::cVProgFile vprogFile;
	if (!vprogFile.Read("test.vprog"))
		return true;

	common::script::cIntermediateCode icode;
	vprogFile.GenerateIntermediateCode(icode);
	if (!icode.Write("test.icode"))
		return true;

	// send icode to webserver
	m_protocol.AckRun(network2::SERVER_NETID, true, 1, icode);

	//m_interpreter.Init("test.icode", this, this);
	//m_interpreter.Run();

	//script::cEvent evt("Tick Event");
	//m_interpreter.PushEvent(evt);

	return true;
}


// iFunctionCallback overriding
int cInterpreterServer::Function(script::cSymbolTable &symbolTable
	, const string &scopeName
	, const string &funcName
	, void *arg)
{

	return 0;
}


void cInterpreterServer::Clear()
{
	m_client.Close();
	m_netController.Clear();
}
