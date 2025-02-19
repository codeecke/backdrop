"use client";

import { MotorEvents } from "@/classes/socketClients/Motor";
import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { useActiveMotor } from "@/store/motorSlice";
import { TWebSocketMotorRunningEventPayload } from "@/types";
import { useEffect, useState } from "react";

type TParams = {
  onUpPressed: () => void;
  onDownPressed: () => void;
  onStopPressed: () => void;
};

export default function BackdropControl({
  onDownPressed,
  onStopPressed,
  onUpPressed,
}: TParams) {
  const [isMoving, setIsMoving] = useState<boolean>(false);
  const [direction, setDirection] = useState<"up" | "down" | null>(null);
  const motor = useActiveMotor();

  motor?.addEventListener(
    MotorEvents.running,
    (payload: TWebSocketMotorRunningEventPayload) => {
      setIsMoving(payload.running);
      setDirection(payload.direction);
    }
  );

  const handleMove = (direction: "up" | "down") => {
    setDirection(direction);
    if (direction === "down") {
      return onDownPressed();
    }
    if (direction === "up") {
      return onUpPressed();
    }
  };

  const handleStop = () => {
    setDirection(null);
    onStopPressed();
  };

  const handleCalibration = () => {
    if (!motor) return;
    const result = confirm("Aktuelle Position als Nullpunkt speichern?");
    if (result) {
      motor.calibrate();
    }
  };

  useEffect(() => {}, [motor]);

  return (
    <div className="p-4 flex justify-center items-center">
      <Card className="max-w-md mx-auto p-6 relative screen-100">
        <div className="mt-8 flex flex-col items-center gap-4">
          <Button
            className="w-24 h-24 p-0"
            variant={direction === "up" && isMoving ? "default" : "secondary"}
            onClick={() => handleMove("up")}
          >
            <div className="w-0 h-0 border-l-[40px] border-l-transparent border-r-[40px] border-r-transparent border-b-[60px] border-b-current" />
          </Button>

          <Button
            className="w-24 h-24 p-0"
            variant="secondary"
            onClick={handleStop}
          >
            <div className="w-20 h-20 bg-current" />
          </Button>

          <Button
            className="w-24 h-24 p-0"
            variant={direction === "down" && isMoving ? "default" : "secondary"}
            onClick={() => handleMove("down")}
          >
            <div className="w-0 h-0 border-l-[40px] border-l-transparent border-r-[40px] border-r-transparent border-t-[60px] border-t-current" />
          </Button>
        </div>
        <div className="flex flex-col gap-4 mt-8">
          <Button onClick={() => handleCalibration()}>
            Als Nullpunkt definieren
          </Button>
          <Button>Position speichern</Button>
        </div>
      </Card>
    </div>
  );
}
