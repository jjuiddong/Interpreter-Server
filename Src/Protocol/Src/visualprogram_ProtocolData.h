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

	struct ReqRunVisualProg_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		webvprog::sNodeFile nodeFile;
	};

	struct ReqStopVisualProg_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
	};





	struct ReqLogin_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string id;
	};

	struct AckRunVisualProg_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		int result;
	};

	struct AckStopVisualProg_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		int result;
	};



}
