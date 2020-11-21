//------------------------------------------------------------------------
// Name:    visualprogram_ProtocolData.h
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
#pragma once

namespace visualprogram {

using namespace network2;
using namespace marshalling_json;


	struct RecvVisProgData_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		double lon;
		double lat;
		double altitude;
		double speed;
		string descript;
	};

	struct AckLogin_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string id;
		int result;
	};

	struct ReqRun_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		webvprog::sNodeFile nodeFile;
	};

	struct ReqEvent_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string eventName;
	};





	struct ReqLogin_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string header;
		string id;
	};

	struct ReqVisProgData_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string header;
	};

	struct AckRun_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		int result;
		script::cIntermediateCode icode;
	};

	struct AckEvent_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		string eventName;
		int result;
	};

	struct SyncRegister_Packet {
		cProtocolDispatcher *pdispatcher;
		netid senderId;
		int vmIdx;
		webvprog::sRegister reg;
	};



}
