"use client";

import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { useState } from "react";

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
  const [isMoving, setIsMoving] = useState<"up" | "down" | null>(null);

  const handleMove = (direction: "up" | "down") => {
    setIsMoving(direction);
    if (direction === "down") {
      return onDownPressed();
    }
    if (direction === "up") {
      return onUpPressed();
    }
  };

  const handleStop = () => {
    setIsMoving(null);
    onStopPressed();
  };

  return (
    <div className="bg-background p-4 flex justify-center items-center">
      <Card className="max-w-md mx-auto p-6 relative screen-100">
        <div className="mt-8 flex flex-col items-center gap-4">
          <Button
            className="w-32 h-32 p-0"
            variant={isMoving === "up" ? "default" : "secondary"}
            onClick={() => handleMove("up")}
          >
            <div className="w-0 h-0 border-l-[40px] border-l-transparent border-r-[40px] border-r-transparent border-b-[60px] border-b-current" />
          </Button>

          <Button
            className="w-32 h-32 p-0"
            variant="secondary"
            onClick={handleStop}
          >
            <div className="w-20 h-20 bg-current" />
          </Button>

          <Button
            className="w-32 h-32 p-0"
            variant={isMoving === "down" ? "default" : "secondary"}
            onClick={() => handleMove("down")}
          >
            <div className="w-0 h-0 border-l-[40px] border-l-transparent border-r-[40px] border-r-transparent border-t-[60px] border-t-current" />
          </Button>
        </div>
      </Card>
    </div>
  );
}
