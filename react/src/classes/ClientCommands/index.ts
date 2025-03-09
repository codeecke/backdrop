import { ZodObject, ZodRawShape } from "zod";
import {
  MotorConfigurationCommand,
  motorConfigurationCommand,
  TMotorConfigurationCommand,
} from "./MotorConfigurationCommand";
import { AbstractClientCommand } from "./AbstractClientCommand";
import { Dispatch } from "@reduxjs/toolkit";
import {
  PositionListCommand,
  positionListCommand,
  TPositionListCommand,
} from "./PositionListCommand";

export type TClientCommandData =
  | TMotorConfigurationCommand
  | TPositionListCommand;

function checkCommand<T extends TClientCommandData>(
  commandData: T,
  validator: ZodObject<ZodRawShape>,
  commandFactory: () => AbstractClientCommand<T>,
  ws: WebSocket,
  dispatch: Dispatch
) {
  const validationResult = validator.safeParse(commandData);
  if (validationResult.success) {
    commandFactory().execute({
      payload: commandData.payload,
      ws,
      dispatch,
    });
  } else {
    console.error("validation failed", validationResult);
  }
}

const clientCommands: Record<
  string,
  {
    validator: ZodObject<ZodRawShape>;
    factory: () => AbstractClientCommand<TClientCommandData>;
  }
> = {
  motorConfiguration: {
    validator: motorConfigurationCommand,
    factory: () => new MotorConfigurationCommand(),
  },
  positionList: {
    validator: positionListCommand,
    factory: () => new PositionListCommand(),
  },
};

export function handleClientCommand(
  command: TClientCommandData,
  ws: WebSocket,
  dispatch: Dispatch
) {
  console.log("clientCommand", command);
  const commandConfig = clientCommands[command.command];
  if (!commandConfig) return;
  checkCommand(
    command,
    commandConfig.validator,
    commandConfig.factory,
    ws,
    dispatch
  );
}
