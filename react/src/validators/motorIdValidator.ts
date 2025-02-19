import { z } from "zod";

export const motorIdValidator = z.union([z.literal(1), z.literal(2)]);
