import { directionValidator } from "@/validators/directionValidator";
import { motorIdValidator } from "@/validators/motorIdValidator";
import { z } from "zod";

export type TMotorId = z.infer<typeof motorIdValidator>;
export type TDirection = z.infer<typeof directionValidator>;
export type TMotorCommandPayload<T = object> = { motorId: TMotorId } & T;

export type TDeviceCommand = {
  move: (
    direction: TDirection
  ) => DeviceCommand<"move", TMotorCommandPayload<{ direction: TDirection }>>;
  stop: () => DeviceCommand<"stop", TMotorCommandPayload>;
  calibrate: () => DeviceCommand<"calibrate", TMotorCommandPayload>;
  moveTo: (
    position: number
  ) => DeviceCommand<"moveTo", TMotorCommandPayload<{ position: number }>>;
  savePosition: (
    name: string
  ) => DeviceCommand<"savePosition", TMotorCommandPayload<{ name: string }>>;
};

export class DeviceCommand<TCommand extends string, TPayload = undefined> {
  constructor(
    public readonly command: TCommand,
    public readonly payload: TPayload
  ) {}

  toString() {
    return JSON.stringify(this);
  }
}

export function createDeviceCommand(motorId: TMotorId): TDeviceCommand {
  return {
    move: (direction: TDirection) =>
      new DeviceCommand("move", { motorId, direction }),
    stop: () => new DeviceCommand("stop", { motorId }),
    calibrate: () => new DeviceCommand("calibrate", { motorId }),
    moveTo: (position: number) =>
      new DeviceCommand("moveTo", { motorId, position }),
    savePosition: (name: string) =>
      new DeviceCommand("savePosition", { motorId, name }),
  };
}
