//------------------------------------------------------------------------
// Name:    visualprogram
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
import Dbg from "../../dbg/dbg";
import WsSockServer from "../wsserver";
import Packet from "../packet"

export default class visualprogram {}


//------------------------------------------------------------------------
// visualprogram s2r Protocol Dispatcher
//------------------------------------------------------------------------
visualprogram.s2r_Dispatcher = class {
	constructor(isRelay = false) {
		this.protocolId = 1000
		this.isRelay = isRelay
	}
	//------------------------------------------------------------------------------
	// dispatch packet
	// wss: WebSocket Server
	// ws: WebSocket
	// packet: Packet class
	// handlers: array of protocol handler
	dispatch(wss, ws, packet, handlers) {
		if (this.isRelay) {
			handlers.forEach(handler => {
				if (handler instanceof visualprogram.s2r_ProtocolHandler)
					handler.Relay(wss, ws, packet)
			})
			return
		}

		// parse packet header, 16 bytes
		// | protocol id (4) | packet id (4) | packet length (4) | option (4) |
		packet.init()
		const protocolId = packet.getUint32()
		const packetId = packet.getUint32()
		const packetLength = packet.getUint32()
		const option = packet.getUint32()

		// dispatch function
		switch (packetId) {
			case 1281093745: // Welcome
				{
					if (option == 1) { // binary?
						const msg = packet.getStr()
						const parsePacket = {
							msg,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.Welcome(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.Welcome(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 851424104: // AckLogin
				{
					if (option == 1) { // binary?
						const id = packet.getStr()
						const result = packet.getInt32()
						const parsePacket = {
							id,
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.AckLogin(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.AckLogin(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 2250021743: // ReqRunVisualProg
				{
					if (option == 1) { // binary?
						const nodeFile = 0
						const parsePacket = {
							nodeFile,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.ReqRunVisualProg(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.ReqRunVisualProg(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 3686541167: // ReqRunVisualProgStream
				{
					if (option == 1) { // binary?
						const count = packet.getUint32()
						const index = packet.getUint32()
						const data = packet.getUint8Array()
						const parsePacket = {
							count,
							index,
							data,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.ReqRunVisualProgStream(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.ReqRunVisualProgStream(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 4258374867: // ReqStopVisualProg
				{
					if (option == 1) { // binary?
						const parsePacket = {
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.ReqStopVisualProg(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.s2r_ProtocolHandler)
								handler.ReqStopVisualProg(wss, ws, parsePacket)
						})
					}
				}
				break;

		default:
			Dbg.Log(0, 1, `RemoteDbg2 receive not defined packet bin:${option}, ${packetId}`)
			break;
		}//~switch
	}//~dispatch()
}


//------------------------------------------------------------------------
// visualprogram r2s Protocol Dispatcher
//------------------------------------------------------------------------
visualprogram.r2s_Dispatcher = class {
	constructor(isRelay = false) {
		this.protocolId = 2000
		this.isRelay = isRelay
	}
	//------------------------------------------------------------------------------
	// dispatch packet
	// wss: WebSocket Server
	// ws: WebSocket
	// packet: Packet class
	// handlers: array of protocol handler
	dispatch(wss, ws, packet, handlers) {
		if (this.isRelay) {
			handlers.forEach(handler => {
				if (handler instanceof visualprogram.r2s_ProtocolHandler)
					handler.Relay(wss, ws, packet)
			})
			return
		}

		// parse packet header, 16 bytes
		// | protocol id (4) | packet id (4) | packet length (4) | option (4) |
		packet.init()
		const protocolId = packet.getUint32()
		const packetId = packet.getUint32()
		const packetLength = packet.getUint32()
		const option = packet.getUint32()

		// dispatch function
		switch (packetId) {
			case 1956887904: // ReqLogin
				{
					if (option == 1) { // binary?
						const id = packet.getStr()
						const parsePacket = {
							id,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.ReqLogin(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.ReqLogin(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 3863877132: // AckRunVisualProg
				{
					if (option == 1) { // binary?
						const result = packet.getInt32()
						const parsePacket = {
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.AckRunVisualProg(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.AckRunVisualProg(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 3454830338: // AckRunVisualProgStream
				{
					if (option == 1) { // binary?
						const result = packet.getInt32()
						const parsePacket = {
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.AckRunVisualProgStream(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.AckRunVisualProgStream(wss, ws, parsePacket)
						})
					}
				}
				break;

			case 1895439953: // AckStopVisualProg
				{
					if (option == 1) { // binary?
						const result = packet.getInt32()
						const parsePacket = {
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.AckStopVisualProg(wss, ws, parsePacket)
						})
					} else { // json?
						const parsePacket = JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof visualprogram.r2s_ProtocolHandler)
								handler.AckStopVisualProg(wss, ws, parsePacket)
						})
					}
				}
				break;

		default:
			Dbg.Log(0, 1, `RemoteDbg2 receive not defined packet bin:${option}, ${packetId}`)
			break;
		}//~switch
	}//~dispatch()
}


//------------------------------------------------------------------------
// visualprogram s2r Protocol 
//------------------------------------------------------------------------
visualprogram.s2r_Protocol = class {
	constructor() { }

	// Protocol: Welcome
	Welcome(ws, isBinary, msg, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushStr(msg)
			WsSockServer.sendPacketBinary(ws, 1000, 1281093745, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				msg,
			}
			WsSockServer.sendPacket(ws, 1000, 1281093745, packet)
		}
	}
	
	// Protocol: AckLogin
	AckLogin(ws, isBinary, id, result, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushStr(id)
			packet.pushInt32(result)
			WsSockServer.sendPacketBinary(ws, 1000, 851424104, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				id,
				result,
			}
			WsSockServer.sendPacket(ws, 1000, 851424104, packet)
		}
	}
	
	// Protocol: ReqRunVisualProg
	ReqRunVisualProg(ws, isBinary, nodeFile, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			0nodeFile)
			WsSockServer.sendPacketBinary(ws, 1000, 2250021743, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				nodeFile,
			}
			WsSockServer.sendPacket(ws, 1000, 2250021743, packet)
		}
	}
	
	// Protocol: ReqRunVisualProgStream
	ReqRunVisualProgStream(ws, isBinary, count, index, data, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushUint32(count)
			packet.pushUint32(index)
			packet.pushUint8Array(data)
			WsSockServer.sendPacketBinary(ws, 1000, 3686541167, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				count,
				index,
				data,
			}
			WsSockServer.sendPacket(ws, 1000, 3686541167, packet)
		}
	}
	
	// Protocol: ReqStopVisualProg
	ReqStopVisualProg(ws, isBinary, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			WsSockServer.sendPacketBinary(ws, 1000, 4258374867, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
			}
			WsSockServer.sendPacket(ws, 1000, 4258374867, packet)
		}
	}
	
}


//------------------------------------------------------------------------
// visualprogram r2s Protocol 
//------------------------------------------------------------------------
visualprogram.r2s_Protocol = class {
	constructor() { }

	// Protocol: ReqLogin
	ReqLogin(ws, isBinary, id, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushStr(id)
			WsSockServer.sendPacketBinary(ws, 2000, 1956887904, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				id,
			}
			WsSockServer.sendPacket(ws, 2000, 1956887904, packet)
		}
	}
	
	// Protocol: AckRunVisualProg
	AckRunVisualProg(ws, isBinary, result, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushInt32(result)
			WsSockServer.sendPacketBinary(ws, 2000, 3863877132, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				result,
			}
			WsSockServer.sendPacket(ws, 2000, 3863877132, packet)
		}
	}
	
	// Protocol: AckRunVisualProgStream
	AckRunVisualProgStream(ws, isBinary, result, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushInt32(result)
			WsSockServer.sendPacketBinary(ws, 2000, 3454830338, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				result,
			}
			WsSockServer.sendPacket(ws, 2000, 3454830338, packet)
		}
	}
	
	// Protocol: AckStopVisualProg
	AckStopVisualProg(ws, isBinary, result, ) {
		if (isBinary) { // binary send?
			let packet = new Packet(512)
			packet.pushInt32(result)
			WsSockServer.sendPacketBinary(ws, 2000, 1895439953, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				result,
			}
			WsSockServer.sendPacket(ws, 2000, 1895439953, packet)
		}
	}
	
}


//------------------------------------------------------------------------
// visualprogram s2r Protocol Handler
//------------------------------------------------------------------------
visualprogram.s2r_ProtocolHandler = class {
	constructor() {} 
	Relay(wss, ws, packet) {} 
	Welcome(wss, ws, packet) {}
	AckLogin(wss, ws, packet) {}
	ReqRunVisualProg(wss, ws, packet) {}
	ReqRunVisualProgStream(wss, ws, packet) {}
	ReqStopVisualProg(wss, ws, packet) {}
}


//------------------------------------------------------------------------
// visualprogram r2s Protocol Handler
//------------------------------------------------------------------------
visualprogram.r2s_ProtocolHandler = class {
	constructor() {} 
	Relay(wss, ws, packet) {} 
	ReqLogin(wss, ws, packet) {}
	AckRunVisualProg(wss, ws, packet) {}
	AckRunVisualProgStream(wss, ws, packet) {}
	AckStopVisualProg(wss, ws, packet) {}
}

