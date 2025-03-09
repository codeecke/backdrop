import {
  createDeviceCommand,
  DeviceCommand,
  TDirection,
  TMotorId,
} from "@/classes/DeviceCommands";
import { AbstractSocketClient } from "./AbstractSocketClient";
import { TClientCommandData } from "../ClientCommands";
import {
  TMotorConfigurationCommand,
  TMotorConfigurationItem,
} from "../ClientCommands/MotorConfigurationCommand";
import { Observable } from "../Observable";

export enum MotorEvents {
  opened = "MOTOR_EVENT_OPENED",
  closed = "MOTOR_EVENT_CLOSED",
  running = "MOTOR_EVENT_RUNNING",
  positionUpdate = "MOTOR_EVENT_POSITION_UPDATE",
}

export class Motor extends AbstractSocketClient {
  private position: number = 0;
  private running: TMotorConfigurationItem["isRunning"];
  private direction: TMotorConfigurationItem["direction"];
  public onRunningChanged: Observable = new Observable();
  public readonly motorId: TMotorId;

  constructor(socket: WebSocket, config: TMotorConfigurationItem) {
    super(socket);
    this.motorId = config.motorId;
    this.running = config.isRunning;
    this.direction = config.direction;
  }

  send(command: DeviceCommand<string, unknown>) {
    this.socket.send(command.toString());
  }

  getPosition() {
    return this.position;
  }

  isRunning() {
    return this.running;
  }

  getDirection(): TMotorConfigurationItem["direction"] {
    return this.direction;
  }

  private createWebsocketCommand() {
    return createDeviceCommand(this.motorId);
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

  onOpen(): void {
    throw new Error("Method not implemented.");
  }
  onClosed(): void {
    throw new Error("Method not implemented.");
  }

  private isMotorConfigurationCommand(
    command: TClientCommandData
  ): command is TMotorConfigurationCommand {
    return command.command === "motorConfiguration";
  }

  onMessage(event: MessageEvent): void {
    const data: TClientCommandData = JSON.parse(event.data);
    if (this.isMotorConfigurationCommand(data)) {
      const config = data.payload.find(
        (motor) => motor.motorId === this.motorId
      );
      if (!config) return;
      this.running = config.isRunning;
      this.direction = config.direction;
      this.onRunningChanged.notify();
    }
  }
}
