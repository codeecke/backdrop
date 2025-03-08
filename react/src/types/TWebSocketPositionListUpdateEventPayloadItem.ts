import { webSocketPositionListUpdateEventPayloadItem } from "@/validators/webSocketPositionListUpdatedEvent";
import { z } from "zod";

export type TWebSocketPositionListUpdateEventPayloadItem = z.infer<
  typeof webSocketPositionListUpdateEventPayloadItem
>;
