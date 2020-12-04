//------------------------------------------------------------------------
// Name:    visualprogram_Protocol.h
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
#pragma once

namespace visualprogram {

using namespace network2;
using namespace marshalling_json;
static const int s2r_Protocol_ID = 1000;

class s2r_Protocol : public network2::iProtocol
{
public:
	s2r_Protocol() : iProtocol(s2r_Protocol_ID, ePacketFormat::JSON) {}
	void Welcome(netid targetId, bool isBinary, const string &msg);
	void AckLogin(netid targetId, bool isBinary, const string &id, const int &result);
	void ReqRunVisualProg(netid targetId, bool isBinary, const uint &count, const uint &index, const uint &state, const webvprog::sNodeFile &nodeFile);
	void ReqRunVisualProgStream(netid targetId, bool isBinary, const uint &count, const uint &index, const vector<BYTE> &data);
	void ReqStopVisualProg(netid targetId, bool isBinary);
};
static const int r2s_Protocol_ID = 2000;

class r2s_Protocol : public network2::iProtocol
{
public:
	r2s_Protocol() : iProtocol(r2s_Protocol_ID, ePacketFormat::JSON) {}
	void ReqLogin(netid targetId, bool isBinary, const string &id);
	void AckRunVisualProg(netid targetId, bool isBinary, const int &result);
	void AckRunVisualProgStream(netid targetId, bool isBinary, const int &result);
	void AckStopVisualProg(netid targetId, bool isBinary, const int &result);
};
}
