import { z } from "zod";

export enum WebSocketEventName {
  MotorRunning = "motorRunning",
  PositionUpdate = "positionUpdate",
  Connected = "connected",
  Disconnected = "disconnected",
}

// Extrahiere die Werte des Enums als Tupel
const eventNames = Object.values(WebSocketEventName) as [
  WebSocketEventName,
  WebSocketEventName,
  ...WebSocketEventName[]
];

export const webSocketEventNameValidator = z.union(
  eventNames.map((eventName) => z.literal(eventName)) as [
    z.ZodLiteral<(typeof eventNames)[number]>,
    z.ZodLiteral<(typeof eventNames)[number]>,
    ...z.ZodLiteral<(typeof eventNames)[number]>[]
  ]
);
