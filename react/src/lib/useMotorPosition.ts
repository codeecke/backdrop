import { useMemo, useState } from "react";
import { ws } from "./websocket";

export function useMotorPosition(motorId: number) {
  const defaultValue = useMemo(() => {
    if (motorId === 1) {
      return ws.motor1.position;
    }
    if (motorId === 2) {
      return ws.motor2.position;
    }
  }, [motorId]);
  const [position, setPosition] = useState(defaultValue);
  ws.addEventListener(
    "POSITION_UPDATE",
    (data: { motor: number; position: number }) => {
      if (data.motor === motorId) {
        setPosition(data.position);
      }
    }
  );
  ws.addEventListener(
    "POSITION_INIT",
    (data: { motor: number; position: number }) => {
      if (data.motor === motorId) {
        setPosition(data.position);
      }
    }
  );

  return position;
}
