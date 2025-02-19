import { webSocketEventNameValidator } from "@/validators/webSocketEventNameValidator";
import { z } from "zod";

export type TWebSocketEventName = z.infer<typeof webSocketEventNameValidator>;
