import { z } from "zod";
import { WebSocketEventName } from "./webSocketEventNameValidator";

export const webSocketDisconnectedEvent = z.object({
  eventName: z.literal(WebSocketEventName.Connected),
});
