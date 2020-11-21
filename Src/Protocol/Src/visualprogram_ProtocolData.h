//------------------------------------------------------------------------
// Name:    visualprogram_ProtocolData.h
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
#pragma once

namespace visualprogram {

using namespace network2;
using namespace marshalling_json;


	struct Welcome_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string msg;
	};

	struct AckLogin_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string id;
		int result;
	};

	struct ReqVisualProgRun_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		webvprog::sNodeFile nodeFile;
	};





	struct ReqLogin_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string id;
	};

	struct AckVisualProgRun_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		int result;
	};



}
