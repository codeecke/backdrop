import { handleClientCommand } from "@/classes/ClientCommands";
import { PropsWithChildren, useEffect } from "react";
import { useDispatch } from "react-redux";

export function WebsocketProvider({ children }: PropsWithChildren) {
  const dispatch = useDispatch();

  useEffect(() => {
    const ws = new WebSocket(`ws://192.168.178.46/ws`);
    ws.addEventListener("message", (ev: MessageEvent<string>) => {
      handleClientCommand(JSON.parse(ev.data), ws, dispatch);
    });
    return () => ws.close();
  }, []);

  return <>{children}</>;
}
