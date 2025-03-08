import { Motor } from "@/classes/socketClients/Motor";
import { WebSocketEventDispatcher } from "@/classes/socketClients/WebSocketEventDispatcher";
import { RootState } from "@/store";
import { setActiveMotorId, setMotors } from "@/store/motorSlice";
import { TColor } from "@/types";
import {
  createContext,
  PropsWithChildren,
  useContext,
  useEffect,
  useState,
} from "react";
import { useDispatch, useSelector } from "react-redux";

type WebSocketContextPayload = {
  event: WebSocketEventDispatcher | null;
};

const WebSocketContext = createContext<WebSocketContextPayload>({
  event: null,
});

export function WebsocketProvider({ children }: PropsWithChildren) {
  // colors
  const selectedColor = useSelector(
    (state: RootState) => state.colorReducer.selected
  );
  const availableColors = useSelector(
    (state: RootState) => state.colorReducer.available
  );
  const [event, setEvent] = useState<WebSocketEventDispatcher | null>(null);
  const dispatch = useDispatch();

  useEffect(() => {
    const ws = new WebSocket(`ws://192.168.178.46/ws`);

    const motors = availableColors.map(
      (color: TColor) => new Motor(ws, color.id)
    );
    dispatch(setMotors(motors));
    setEvent(new WebSocketEventDispatcher(ws));
    return () => ws.close();
  }, [availableColors]);

  useEffect(() => {
    dispatch(setActiveMotorId(selectedColor?.id));
  }, [selectedColor]);

  return (
    <WebSocketContext.Provider value={{ event }}>
      {children}
    </WebSocketContext.Provider>
  );
}

export function useWebSocketEvent(): WebSocketEventDispatcher | null {
  return useContext(WebSocketContext).event;
}
