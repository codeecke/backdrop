import { z } from "zod";
import { TMotorId } from "./TWebsocketCommands";

export const colorValidator = z.object({
  id: z.number(),
  name: z.string(),
  code: z.string().regex(/#[0-9A-Fa-f]{6}/),
});

export type TColor = z.infer<typeof colorValidator> & {
  id: TMotorId;
};
