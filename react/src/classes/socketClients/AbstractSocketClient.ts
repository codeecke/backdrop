import { DeviceCommand } from "../DeviceCommands";

export abstract class AbstractSocketClient {
  constructor(protected socket: WebSocket) {
    socket.addEventListener("close", () => this.onClosed());
    socket.addEventListener("open", () => this.onOpen());
    socket.addEventListener("message", (event: MessageEvent) =>
      this.onMessage(event)
    );
  }

  send(command: DeviceCommand<string, unknown>) {
    this.socket.send(command.toString());
  }

  abstract onOpen(): void;
  abstract onClosed(): void;
  abstract onMessage(event: MessageEvent): void;
}
