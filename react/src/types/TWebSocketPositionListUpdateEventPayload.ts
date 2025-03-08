import { z } from "zod";
import { webSocketPositionListUpdateEventPayload } from "@/validators/webSocketPositionListUpdatedEvent";
export type TWebSocketPositionListUpdateEventPayload = z.infer<
  typeof webSocketPositionListUpdateEventPayload
>;
