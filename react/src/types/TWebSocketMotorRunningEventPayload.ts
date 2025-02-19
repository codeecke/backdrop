import { z } from "zod";
import { webSocketMotorRunningEventPayload } from "@/validators/webSocketMotorRunningEvent";

export type TWebSocketMotorRunningEventPayload = z.infer<
  typeof webSocketMotorRunningEventPayload
>;
