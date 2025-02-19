import { z } from "zod";
import { WebSocketEventName } from "./webSocketEventNameValidator";

export const webSocketPositionUpdateEventPayload = z.number();

export const webSocketPositionUpdateEvent = z.object({
  motorId: z.number().min(1).max(2),
  eventName: z.literal(WebSocketEventName.PositionUpdate),
  payload: webSocketPositionUpdateEventPayload,
});
