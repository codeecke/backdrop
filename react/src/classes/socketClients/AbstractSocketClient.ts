import { WebSocketCommand } from "@/types";
import { EventDispatcher } from "../EventDispatcher";

export abstract class AbstractSocketClient extends EventDispatcher {
  constructor(protected socket: WebSocket) {
    super();
    socket.addEventListener("close", () => this.onClosed());
    socket.addEventListener("open", () => this.onOpen());
    socket.addEventListener("message", (event: MessageEvent) =>
      this.onMessage(event)
    );
  }

  send(command: WebSocketCommand<string, unknown>) {
    this.socket.send(command.toString());
  }

  abstract onOpen(): void;
  abstract onClosed(): void;
  abstract onMessage(event: MessageEvent): void;
}
