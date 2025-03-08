import { z } from "zod";
import { WebSocketEventName } from "./webSocketEventNameValidator";

export const webSocketPositionListUpdateEventPayloadItem = z.object({
  name: z.string().max(20).min(1),
  position: z.number().min(0),
});

export const webSocketPositionListUpdateEventPayload = z.array(
  webSocketPositionListUpdateEventPayloadItem
);

export const webSocketPositionListUpdateEvent = z.object({
  motorId: z.number().min(1).max(2),
  eventName: z.literal(WebSocketEventName.PositionListUpdate),
  payload: webSocketPositionListUpdateEventPayload,
});
