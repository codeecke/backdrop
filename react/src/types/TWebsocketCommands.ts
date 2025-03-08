import { directionValidator } from "@/validators/directionValidator";
import { motorIdValidator } from "@/validators/motorIdValidator";
import { z } from "zod";

export type TMotorId = z.infer<typeof motorIdValidator>;
export type TDirection = z.infer<typeof directionValidator>;
export type TMotorCommandPayload<T = object> = { motorId: TMotorId } & T;

type TWebSocketCommand = {
  move: (
    direction: TDirection
  ) => WebSocketCommand<
    "move",
    TMotorCommandPayload<{ direction: TDirection }>
  >;
  stop: () => WebSocketCommand<"stop", TMotorCommandPayload>;
  calibrate: () => WebSocketCommand<"calibrate", TMotorCommandPayload>;
  moveTo: (
    position: number
  ) => WebSocketCommand<"moveTo", TMotorCommandPayload<{ position: number }>>;
  savePosition: (
    name: string
  ) => WebSocketCommand<"savePosition", TMotorCommandPayload<{ name: string }>>;
};

export class WebSocketCommand<TCommand extends string, TPayload = undefined> {
  constructor(
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
      new WebSocketCommand("move", { motorId, direction }),
    stop: () => new WebSocketCommand("stop", { motorId }),
    calibrate: () => new WebSocketCommand("calibrate", { motorId }),
    moveTo: (position: number) =>
      new WebSocketCommand("moveTo", { motorId, position }),
    savePosition: (name: string) =>
      new WebSocketCommand("savePosition", { motorId, name }),
  };
}
