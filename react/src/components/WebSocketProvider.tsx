import { Motor } from "@/classes/socketClients/Motor";
import { RootState } from "@/store";
import { setActiveMotorId, setMotors } from "@/store/motorSlice";
import { TColor } from "@/types";
import { PropsWithChildren, useEffect } from "react";
import { useDispatch, useSelector } from "react-redux";

export function WebsocketProvider({ children }: PropsWithChildren) {
  // colors
  const selectedColor = useSelector(
    (state: RootState) => state.colorReducer.selected
  );
  const availableColors = useSelector(
    (state: RootState) => state.colorReducer.available
  );
  const dispatch = useDispatch();

  useEffect(() => {
    console.log("WebSocketProvider::availableColors", availableColors);
    const ws = new WebSocket(`ws://192.168.178.42/ws`);

    const motors = availableColors.map(
      (color: TColor) => new Motor(ws, color.id)
    );
    dispatch(setMotors(motors));

    return () => ws.close();
  }, [availableColors]);

  useEffect(() => {
    dispatch(setActiveMotorId(selectedColor?.id));
  }, [selectedColor]);

  return <>{children}</>;
}
