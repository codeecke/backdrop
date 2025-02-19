import { webSocketConnectedEvent } from "@/validators/webSocketConnectedEvent";
import { z } from "zod";

export type TWebSocketConnectedEvent = z.infer<typeof webSocketConnectedEvent>;
