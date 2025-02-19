import { TWebSocketEventPayload } from "@/types";
import { TMotorId } from "@/types/TWebsocketCommands";

export class WebSocketEvent<
  TEventName extends keyof TWebSocketEventPayload = keyof TWebSocketEventPayload,
  TPayload = TWebSocketEventPayload[TEventName]
> {
  constructor(
    public readonly motorId: TMotorId,
    public readonly eventName: TEventName,
    public readonly payload: TPayload
  ) {}
}
