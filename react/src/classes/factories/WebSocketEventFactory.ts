import {
  webSocketConnectedEvent,
  webSocketDisconnectedEvent,
  WebSocketEventName,
  webSocketMotorRunningEvent,
  webSocketPositionUpdateEvent,
} from "@/types/TWebSocketEvent";
import { WebSocketEvent } from "../WebSocketEvent";
import { TMotorId } from "@/types/TWebsocketCommands";

export class WebSocketEventFactory {
  static createByJSON(json: string) {
    const jsonData = JSON.parse(json);
    if (webSocketConnectedEvent.safeParse(jsonData)) {
      WebSocketEventFactory.createConnectedEvent(jsonData.motorId);
    }
    if (webSocketDisconnectedEvent.safeParse(jsonData)) {
      WebSocketEventFactory.createDisconnectedEvent(jsonData.motorId);
    }
    if (webSocketMotorRunningEvent.safeParse(jsonData)) {
      return WebSocketEventFactory.createMotorRunningEvent(
        jsonData.motorId,
        jsonData.payload
      );
    }
    if (webSocketPositionUpdateEvent.safeParse(jsonData)) {
      return WebSocketEventFactory.createPositionUpdateEvent(
        jsonData.motorId,
        jsonData.payload
      );
    }
    throw new Error("invalid json data");
  }

  private static createConnectedEvent(motorId: TMotorId) {
    return new WebSocketEvent(motorId, WebSocketEventName.Connected);
  }

  private static createDisconnectedEvent(motorId: TMotorId) {
    return new WebSocketEvent(motorId, WebSocketEventName.Disconnected);
  }

  private static createMotorRunningEvent(motorId: TMotorId, running: boolean) {
    return new WebSocketEvent<WebSocketEventName.MotorRunning, boolean>(
      motorId,
      WebSocketEventName.MotorRunning,
      running
    );
  }

  private static createPositionUpdateEvent(
    motorId: TMotorId,
    position: number
  ) {
    return new WebSocketEvent<WebSocketEventName.PositionUpdate, number>(
      motorId,
      WebSocketEventName.PositionUpdate,
      position
    );
  }
}
