import { webSocketPositionListUpdateEvent } from "@/validators/webSocketPositionListUpdatedEvent";
import { z } from "zod";

export type TWebSocketPositionListUpdateEvent = z.infer<
  typeof webSocketPositionListUpdateEvent
>;
