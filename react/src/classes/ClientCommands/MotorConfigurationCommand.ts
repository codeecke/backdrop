import { motorIdValidator } from "@/validators/motorIdValidator";
import { z } from "zod";
import {
  AbstractClientCommand,
  TClientCommandExecuteParam,
} from "./AbstractClientCommand";
import { setAvailableColors, setSelectedColor } from "@/store/colorSlice";
import { setActiveMotorId, setMotors } from "@/store/motorSlice";
import { Motor } from "@/classes/socketClients/Motor";

export const motorConfigurationCommandPayloadItem = z.object({
  motorId: motorIdValidator,
  name: z.string(),
  colorCode: z.string().regex(/#[0-9a-fA-F]{6}/),
  isRunning: z.boolean(),
  direction: z.literal("up").or(z.literal("down")),
});

export const motorConfigurationCommand = z.object({
  command: z.literal("motorConfiguration"),
  payload: z.array(motorConfigurationCommandPayloadItem),
});

export type TMotorConfigurationItem = z.infer<
  typeof motorConfigurationCommandPayloadItem
>;

export type TMotorConfigurationCommand = z.infer<
  typeof motorConfigurationCommand
>;

export class MotorConfigurationCommand extends AbstractClientCommand<TMotorConfigurationCommand> {
  execute({
    payload,
    dispatch,
    ws,
  }: TClientCommandExecuteParam<TMotorConfigurationCommand>) {
    if (payload.length < 1) return;
    dispatch(setAvailableColors(payload));
    dispatch(setSelectedColor(payload[0]));
    dispatch(setMotors(payload.map((config) => new Motor(ws, config))));
    dispatch(setActiveMotorId(payload[0].motorId));
    console.log("MotorConfigurationCommand::execute()", payload);
  }
}
