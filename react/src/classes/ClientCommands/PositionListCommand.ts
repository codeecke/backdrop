import { motorIdValidator } from "@/validators/motorIdValidator";
import { z } from "zod";
import {
  AbstractClientCommand,
  TClientCommandExecuteParam,
} from "./AbstractClientCommand";
import { setPositionList } from "@/store/positionListSlice";

const posiitionListItem = z.object({
  motorId: motorIdValidator,
  name: z.string(),
  position: z.number(),
});

export const positionListCommand = z.object({
  command: z.literal("positionList"),
  payload: z.array(posiitionListItem),
});

export type TPosition = z.infer<typeof posiitionListItem>;
export type TPositionListCommand = z.infer<typeof positionListCommand>;

export class PositionListCommand extends AbstractClientCommand<TPositionListCommand> {
  execute({
    payload,
    dispatch,
  }: TClientCommandExecuteParam<TPositionListCommand>): void {
    dispatch(setPositionList(payload));
  }
}
