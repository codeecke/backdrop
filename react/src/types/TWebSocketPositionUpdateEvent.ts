import { webSocketPositionUpdateEvent } from "@/validators/webSocketPositionUpdateEvent";
import { z } from "zod";

export type TWebSocketPositionUpdateEvent = z.infer<
  typeof webSocketPositionUpdateEvent
>;
