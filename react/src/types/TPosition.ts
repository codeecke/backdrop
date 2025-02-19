import { z } from "zod";

export const positionValidator = z.object({
  id: z.number(),
  name: z.string(),
  motorId: z.number(),
  position: z.number(),
});

export type TPosition = z.infer<typeof positionValidator>;
