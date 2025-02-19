import {
  WebSocketEventName,
  webSocketMotorRunningEventPayload,
  webSocketPositionUpdateEventPayload,
} from "@/validators";
import { z } from "zod";

export type TWebSocketEventPayload = {
  [WebSocketEventName.Connected]: undefined;
  [WebSocketEventName.Disconnected]: undefined;
  [WebSocketEventName.PositionUpdate]: z.infer<
    typeof webSocketPositionUpdateEventPayload
  >;
  [WebSocketEventName.MotorRunning]: z.infer<
    typeof webSocketMotorRunningEventPayload
  >;
};
