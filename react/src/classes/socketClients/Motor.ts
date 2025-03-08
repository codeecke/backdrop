import {
  createWebsocketCommand,
  TDirection,
  TMotorId,
  TWebSocketEvent,
  TWebSocketMotorRunningEvent,
  TWebSocketPositionUpdateEvent,
} from "@/types";
import { AbstractSocketClient } from "./AbstractSocketClient";
import { WebSocketEvent } from "../WebSocketEvent";
import { WebSocketEventName, webSocketEventValidator } from "@/validators";

export enum MotorEvents {
  opened = "MOTOR_EVENT_OPENED",
  closed = "MOTOR_EVENT_CLOSED",
  running = "MOTOR_EVENT_RUNNING",
  positionUpdate = "MOTOR_EVENT_POSITION_UPDATE",
}

export class Motor extends AbstractSocketClient {
  private position: number = 0;
  private running: boolean = false;

  constructor(socket: WebSocket, public readonly motorId: TMotorId) {
    super(socket);
  }

  getPosition() {
    return this.position;
  }

  isRunning() {
    return this.running;
  }

  onOpen(): void {
    this.dispatchEvent(MotorEvents.opened);
  }

  onClosed(): void {
    this.dispatchEvent(MotorEvents.closed);
  }

  private isRunningEvent(
    event: TWebSocketEvent
  ): event is TWebSocketMotorRunningEvent {
    return event.eventName === WebSocketEventName.MotorRunning;
  }

  private isPositionUpdateEvent(
    event: TWebSocketEvent
  ): event is TWebSocketPositionUpdateEvent {
    return event.eventName === WebSocketEventName.PositionUpdate;
  }
  private parseMessageEvent(event: MessageEvent): TWebSocketEvent | null {
    try {
      const eventData = JSON.parse(event.data);
      if (webSocketEventValidator.parse(eventData)) {
        const sockEvent: TWebSocketEvent = new WebSocketEvent(
          eventData.motorId,
          eventData.eventName,
          eventData.payload
        );
        return sockEvent;
      }
      return null;
    } catch (e) {
      console.error(e);
      return null;
    }
  }

  onMessage(event: MessageEvent): void {
    const sockEvent = this.parseMessageEvent(event);
    if (!sockEvent || sockEvent.motorId !== this.motorId) return;

    if (this.isRunningEvent(sockEvent)) {
      this.running = sockEvent.payload.running;
      this.dispatchEvent(MotorEvents.running, sockEvent.payload);
    }

    if (this.isPositionUpdateEvent(sockEvent)) {
      this.position = sockEvent.payload;
      this.dispatchEvent(MotorEvents.positionUpdate, sockEvent.payload);
    }
  }

  private createWebsocketCommand() {
    return createWebsocketCommand(this.motorId);
  }

  move(direction: TDirection) {
    const command = this.createWebsocketCommand().move(direction);
    this.send(command);
  }

  moveUp() {
    this.move("up");
  }

  moveDown() {
    this.move("down");
  }

  stop() {
    const command = this.createWebsocketCommand().stop();
    this.send(command);
  }

  moveTo(position: number) {
    const command = this.createWebsocketCommand().moveTo(position);
    this.send(command);
  }

  calibrate() {
    const command = this.createWebsocketCommand().calibrate();
    this.send(command);
  }

  savePosition(name: string) {
    const command = this.createWebsocketCommand().savePosition(name);
    this.send(command);
  }
}
