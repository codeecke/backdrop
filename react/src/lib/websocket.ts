import { Motor } from "./Motor";
import { WebSocketEvent } from "./webSocketEvent";

type TEventListener<T = unknown> = (data: T) => void;

class WebSocketClient {
  private sock: WebSocket;
  private listeners: Record<string, TEventListener[]> = {};
  public readonly motor1 = new Motor(1, 0);
  public readonly motor2 = new Motor(2, 0);

  constructor() {
    this.sock = this.reconnect();
  }

  public reconnect() {
    this.sock = new WebSocket(`ws://${location.hostname}/ws`);
    this.sock.addEventListener("close", () => this.reconnect());
    this.sock.addEventListener("message", (event: MessageEvent) => {
      const data = JSON.parse(event.data);
      const eventData = new WebSocketEvent(data.eventName, data.payload);

      if (
        eventData.eventName === "POSITION_INIT" ||
        eventData.eventName === "POSITION_UPDATE"
      ) {
        const payload: { motor: number; positon: number } = eventData.payload;
        if (payload.motor == 1) {
          this.motor1.position = payload.positon;
          console.log("motor1 initialized", payload.positon);
        }
        if (payload.motor == 2) {
          this.motor2.position = payload.positon;
          console.log("motor2 initialized", payload.positon);
        }
      }
      this.listeners[eventData.eventName]?.forEach((listener) =>
        listener(eventData.payload)
      );
    });
    return this.sock;
  }

  public addEventListener(eventName: string, cb: (data: any) => void) {
    if (!this.listeners[eventName]) {
      this.listeners[eventName] = [];
    }

    this.listeners[eventName].push(cb);
  }

  public send(event: WebSocketEvent) {
    const resend = this.send.bind(this, event);

    if (this.sock.OPEN) {
      this.sock.send(JSON.stringify(event));
    }
    return this.reconnect().addEventListener("open", () => resend);
  }
}

export const ws = new WebSocketClient();
