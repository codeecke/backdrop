import { webSocketDisconnectedEvent } from "@/validators/webSocketDisconnectedEvent";
import { z } from "zod";

export type TWebSocketDisconnectedEvent = z.infer<
  typeof webSocketDisconnectedEvent
>;
