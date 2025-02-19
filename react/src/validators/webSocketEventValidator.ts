import { z } from "zod";
import { webSocketConnectedEvent } from "./webSocketConnectedEvent";
import { webSocketMotorRunningEvent } from "./webSocketMotorRunningEvent";
import { webSocketPositionUpdateEvent } from "./webSocketPositionUpdateEvent";

export const webSocketEventValidator = z.union([
  webSocketConnectedEvent,
  webSocketMotorRunningEvent,
  webSocketPositionUpdateEvent,
]);
