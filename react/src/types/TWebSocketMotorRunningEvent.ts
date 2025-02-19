import { webSocketMotorRunningEvent } from "@/validators/webSocketMotorRunningEvent";
import { z } from "zod";

export type TWebSocketMotorRunningEvent = z.infer<
  typeof webSocketMotorRunningEvent
>;
