import { z } from "zod";
import { WebSocketEventName } from "./webSocketEventNameValidator";
import { directionValidator } from "./directionValidator";

export const webSocketMotorRunningEventPayload = z.object({
  running: z.boolean(),
  direction: directionValidator,
});

export const webSocketMotorRunningEvent = z.object({
  motorId: z.number().min(1).max(2),
  eventName: z.literal(WebSocketEventName.MotorRunning),
  payload: webSocketMotorRunningEventPayload,
});
