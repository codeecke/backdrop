import { TWebSocketMotorRunningEvent } from "./TWebSocketMotorRunningEvent";
import { TWebSocketPositionUpdateEvent } from "./TWebSocketPositionUpdateEvent";

export type TWebSocketEvent =
  | TWebSocketMotorRunningEvent
  | TWebSocketPositionUpdateEvent;
