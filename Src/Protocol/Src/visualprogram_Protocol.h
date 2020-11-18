//------------------------------------------------------------------------
// Name:    visualprogram_Protocol.h
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
#pragma once

namespace visualprogram {

using namespace network2;
using namespace marshalling_json;
static const int w2s_Protocol_ID = 1000;

class w2s_Protocol : public network2::iProtocol
{
public:
	w2s_Protocol() : iProtocol(w2s_Protocol_ID, ePacketFormat::JSON) {}
	void RecvVisProgData(netid targetId, bool isBinary, const double &lon, const double &lat, const double &altitude, const double &speed, const string &descript);
	void AckLogin(netid targetId, bool isBinary, const string &id, const int &result);
	void ReqRun(netid targetId, bool isBinary, const webvprog::sNodeFile &nodeFile);
};
static const int s2w_Protocol_ID = 2000;

class s2w_Protocol : public network2::iProtocol
{
public:
	s2w_Protocol() : iProtocol(s2w_Protocol_ID, ePacketFormat::JSON) {}
	void ReqLogin(netid targetId, bool isBinary, const string &header, const string &id);
	void ReqVisProgData(netid targetId, bool isBinary, const string &header);
	void AckRun(netid targetId, bool isBinary, const int &result, const script::cIntermediateCode &icode);
};
}
