import { EventDispatcher } from "../EventDispatcher";
import { WebSocketEvent } from "../WebSocketEvent";

export class WebSocketEventDispatcher extends EventDispatcher {
  constructor(ws: WebSocket) {
    super();
    ws.addEventListener("message", (e: MessageEvent) => this.onMessage(e));
  }

  private onMessage(e: MessageEvent) {
    const data: WebSocketEvent = JSON.parse(e.data);
    console.log("ws-msg:", data);
    this.dispatchEvent(data.eventName, data.payload);
  }
}
