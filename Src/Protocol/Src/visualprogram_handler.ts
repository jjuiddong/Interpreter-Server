//------------------------------------------------------------------------
// Name:    visualprogram
// Author:  ProtocolGenerator (by jjuiddong)
// Date:    
//------------------------------------------------------------------------
import TypeVariant from "../common/variant";
import { Network } from "../network/network";

export namespace visualprogram {

	// s2r Protocol Packet Data
	export type Welcome_Packet = {
		msg: string, 
	}
	export type AckLogin_Packet = {
		id: string, 
		result: number, 
	}
	export type ReqRunVisualProg_Packet = {
		nodeFile: notdef, 
	}
	export type ReqRunVisualProgStream_Packet = {
		count: number, 
		index: number, 
		data: Uint8Array | null, 
	}
	export type ReqStopVisualProg_Packet = {
	}


	// r2s Protocol Packet Data
	export type ReqLogin_Packet = {
		id: string, 
	}
	export type AckRunVisualProg_Packet = {
		result: number, 
	}
	export type AckRunVisualProgStream_Packet = {
		result: number, 
	}
	export type AckStopVisualProg_Packet = {
		result: number, 
	}


//------------------------------------------------------------------------
// visualprogram s2r Protocol Dispatcher
//------------------------------------------------------------------------
export class s2r_Dispatcher extends Network.Dispatcher {
	 constructor() {
		super(1000)
	}
	dispatch(ws: WebSocket, packet: Network.Packet, handlers: Network.Handler[]) {
		if (!packet.buff) return
		packet.init()
		// packet format
		// | protocol id (4) | packet id (4) | packet length (4) | option (4) |
		const protocolId = packet.getUint32()
		const packetId = packet.getUint32()
		const packetLength = packet.getUint32()
		const option = packet.getUint32()

		switch (packetId) {
			case 1281093745: // Welcome
				{
					if (option == 1) { // binary?
						const msg = packet.getStr()
						const parsePacket: Welcome_Packet = {
							msg,
						}
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.Welcome(parsePacket)
						})
					} else { // json?
						const parsePacket: Welcome_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.Welcome(parsePacket)
						})
					}
				}
				break;

			case 851424104: // AckLogin
				{
					if (option == 1) { // binary?
						const id = packet.getStr()
						const result = packet.getInt32()
						const parsePacket: AckLogin_Packet = {
							id,
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.AckLogin(parsePacket)
						})
					} else { // json?
						const parsePacket: AckLogin_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.AckLogin(parsePacket)
						})
					}
				}
				break;

			case 2250021743: // ReqRunVisualProg
				{
					if (option == 1) { // binary?
						const nodeFile = 0
						const parsePacket: ReqRunVisualProg_Packet = {
							nodeFile,
						}
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.ReqRunVisualProg(parsePacket)
						})
					} else { // json?
						const parsePacket: ReqRunVisualProg_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.ReqRunVisualProg(parsePacket)
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
						const parsePacket: ReqRunVisualProgStream_Packet = {
							count,
							index,
							data,
						}
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.ReqRunVisualProgStream(parsePacket)
						})
					} else { // json?
						const parsePacket: ReqRunVisualProgStream_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.ReqRunVisualProgStream(parsePacket)
						})
					}
				}
				break;

			case 4258374867: // ReqStopVisualProg
				{
					if (option == 1) { // binary?
						const parsePacket: ReqStopVisualProg_Packet = {
						}
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.ReqStopVisualProg(parsePacket)
						})
					} else { // json?
						const parsePacket: ReqStopVisualProg_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof s2r_ProtocolHandler)
								handler.ReqStopVisualProg(parsePacket)
						})
					}
				}
				break;

			default:
				console.log(`not found packet ${protocolId}, ${packetId}`)
				break;
		}//~switch
	}//~dispatch()
}


//------------------------------------------------------------------------
// visualprogram r2s Protocol Dispatcher
//------------------------------------------------------------------------
export class r2s_Dispatcher extends Network.Dispatcher {
	 constructor() {
		super(2000)
	}
	dispatch(ws: WebSocket, packet: Network.Packet, handlers: Network.Handler[]) {
		if (!packet.buff) return
		packet.init()
		// packet format
		// | protocol id (4) | packet id (4) | packet length (4) | option (4) |
		const protocolId = packet.getUint32()
		const packetId = packet.getUint32()
		const packetLength = packet.getUint32()
		const option = packet.getUint32()

		switch (packetId) {
			case 1956887904: // ReqLogin
				{
					if (option == 1) { // binary?
						const id = packet.getStr()
						const parsePacket: ReqLogin_Packet = {
							id,
						}
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.ReqLogin(parsePacket)
						})
					} else { // json?
						const parsePacket: ReqLogin_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.ReqLogin(parsePacket)
						})
					}
				}
				break;

			case 3863877132: // AckRunVisualProg
				{
					if (option == 1) { // binary?
						const result = packet.getInt32()
						const parsePacket: AckRunVisualProg_Packet = {
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.AckRunVisualProg(parsePacket)
						})
					} else { // json?
						const parsePacket: AckRunVisualProg_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.AckRunVisualProg(parsePacket)
						})
					}
				}
				break;

			case 3454830338: // AckRunVisualProgStream
				{
					if (option == 1) { // binary?
						const result = packet.getInt32()
						const parsePacket: AckRunVisualProgStream_Packet = {
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.AckRunVisualProgStream(parsePacket)
						})
					} else { // json?
						const parsePacket: AckRunVisualProgStream_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.AckRunVisualProgStream(parsePacket)
						})
					}
				}
				break;

			case 1895439953: // AckStopVisualProg
				{
					if (option == 1) { // binary?
						const result = packet.getInt32()
						const parsePacket: AckStopVisualProg_Packet = {
							result,
						}
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.AckStopVisualProg(parsePacket)
						})
					} else { // json?
						const parsePacket: AckStopVisualProg_Packet = 
							JSON.parse(packet.getStr())
						handlers.forEach(handler => {
							if (handler instanceof r2s_ProtocolHandler)
								handler.AckStopVisualProg(parsePacket)
						})
					}
				}
				break;

			default:
				console.log(`not found packet ${protocolId}, ${packetId}`)
				break;
		}//~switch
	}//~dispatch()
}


//------------------------------------------------------------------------
// visualprogram s2r Protocol 
//------------------------------------------------------------------------
export class s2r_Protocol extends Network.Protocol {
	 constructor() { super() }

	// Protocol: Welcome
	Welcome(isBinary: boolean, msg: string, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushStr(msg)
			Network.sendPacketBinary(this.ws, 1000, 1281093745, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				msg,
			}
			Network.sendPacket(this.ws, 1000, 1281093745, packet)
		}
	}
	
	// Protocol: AckLogin
	AckLogin(isBinary: boolean, id: string, result: number, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushStr(id)
			packet.pushInt32(result)
			Network.sendPacketBinary(this.ws, 1000, 851424104, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				id,
				result,
			}
			Network.sendPacket(this.ws, 1000, 851424104, packet)
		}
	}
	
	// Protocol: ReqRunVisualProg
	ReqRunVisualProg(isBinary: boolean, nodeFile: notdef, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			0nodeFile)
			Network.sendPacketBinary(this.ws, 1000, 2250021743, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				nodeFile,
			}
			Network.sendPacket(this.ws, 1000, 2250021743, packet)
		}
	}
	
	// Protocol: ReqRunVisualProgStream
	ReqRunVisualProgStream(isBinary: boolean, count: number, index: number, data: number[], ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushUint32(count)
			packet.pushUint32(index)
			packet.pushUint8Array(data)
			Network.sendPacketBinary(this.ws, 1000, 3686541167, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				count,
				index,
				data,
			}
			Network.sendPacket(this.ws, 1000, 3686541167, packet)
		}
	}
	
	// Protocol: ReqStopVisualProg
	ReqStopVisualProg(isBinary: boolean, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			Network.sendPacketBinary(this.ws, 1000, 4258374867, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
			}
			Network.sendPacket(this.ws, 1000, 4258374867, packet)
		}
	}
	
}


//------------------------------------------------------------------------
// visualprogram r2s Protocol 
//------------------------------------------------------------------------
export class r2s_Protocol extends Network.Protocol {
	 constructor() { super() }

	// Protocol: ReqLogin
	ReqLogin(isBinary: boolean, id: string, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushStr(id)
			Network.sendPacketBinary(this.ws, 2000, 1956887904, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				id,
			}
			Network.sendPacket(this.ws, 2000, 1956887904, packet)
		}
	}
	
	// Protocol: AckRunVisualProg
	AckRunVisualProg(isBinary: boolean, result: number, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushInt32(result)
			Network.sendPacketBinary(this.ws, 2000, 3863877132, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				result,
			}
			Network.sendPacket(this.ws, 2000, 3863877132, packet)
		}
	}
	
	// Protocol: AckRunVisualProgStream
	AckRunVisualProgStream(isBinary: boolean, result: number, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushInt32(result)
			Network.sendPacketBinary(this.ws, 2000, 3454830338, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				result,
			}
			Network.sendPacket(this.ws, 2000, 3454830338, packet)
		}
	}
	
	// Protocol: AckStopVisualProg
	AckStopVisualProg(isBinary: boolean, result: number, ) {
		if (!this.ws)
			return
		if (isBinary) { // binary send?
			let packet = new Network.Packet(512)
			packet.pushInt32(result)
			Network.sendPacketBinary(this.ws, 2000, 1895439953, packet.buff, packet.offset)
		} else { // json string send?
			const packet = {
				result,
			}
			Network.sendPacket(this.ws, 2000, 1895439953, packet)
		}
	}
	
}


//------------------------------------------------------------------------
// visualprogram s2r Protocol Handler
//------------------------------------------------------------------------
export class s2r_ProtocolHandler extends Network.Handler {
	 constructor() { super() } 

	Welcome = (packet: visualprogram.Welcome_Packet) => { }
	AckLogin = (packet: visualprogram.AckLogin_Packet) => { }
	ReqRunVisualProg = (packet: visualprogram.ReqRunVisualProg_Packet) => { }
	ReqRunVisualProgStream = (packet: visualprogram.ReqRunVisualProgStream_Packet) => { }
	ReqStopVisualProg = (packet: visualprogram.ReqStopVisualProg_Packet) => { }
}


//------------------------------------------------------------------------
// visualprogram r2s Protocol Handler
//------------------------------------------------------------------------
export class r2s_ProtocolHandler extends Network.Handler {
	 constructor() { super() } 

	ReqLogin = (packet: visualprogram.ReqLogin_Packet) => { }
	AckRunVisualProg = (packet: visualprogram.AckRunVisualProg_Packet) => { }
	AckRunVisualProgStream = (packet: visualprogram.AckRunVisualProgStream_Packet) => { }
	AckStopVisualProg = (packet: visualprogram.AckStopVisualProg_Packet) => { }
}

}

