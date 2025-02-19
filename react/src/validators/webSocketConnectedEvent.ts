import { z } from "zod";
import { WebSocketEventName } from "./webSocketEventNameValidator";

export const webSocketConnectedEvent = z.object({
  eventName: z.literal(WebSocketEventName.Connected),
});
