import { directionValidator } from "@/validators/directionValidator";
import { motorIdValidator } from "@/validators/motorIdValidator";
import { z } from "zod";

export type TMotorId = z.infer<typeof motorIdValidator>;
export type TDirection = z.infer<typeof directionValidator>;

type TWebSocketCommand = {
  move: (direction: TDirection) => WebSocketCommand<"move", TDirection>;
  stop: () => WebSocketCommand<"stop">;
  calibrate: () => WebSocketCommand<"calibrate">;
  positionUpdate: (
    position: number
  ) => WebSocketCommand<"positionUpdate", number>;
};

export class WebSocketCommand<TCommand extends string, TPayload = undefined> {
  constructor(
    public readonly motorId: TMotorId,
    public readonly command: TCommand,
    public readonly payload: TPayload
  ) {}

  toString() {
    return JSON.stringify(this);
  }
}

export function createWebsocketCommand(motorId: TMotorId): TWebSocketCommand {
  return {
    move: (direction: TDirection) =>
      new WebSocketCommand(motorId, "move", direction),
    stop: () => new WebSocketCommand(motorId, "stop", undefined),
    calibrate: () => new WebSocketCommand(motorId, "calibrate", undefined),
    positionUpdate: (position: number) =>
      new WebSocketCommand(motorId, "positionUpdate", position),
  };
}
