import "./App.css";
import BackdropControl from "./components/backdropControl";
import { WebSocketEvent } from "./lib/webSocketEvent";
import { ws } from "./lib/websocket";

function App() {
  const onUpPressed = () => {
    ws.send(new WebSocketEvent("MOVE_UP"));
  };
  const onDownPressed = () => {
    ws.send(new WebSocketEvent("MOVE_DOWN"));
  };
  const onStopPressed = () => {
    ws.send(new WebSocketEvent("MOVE_STOP"));
  };

  ws.addEventListener(
    "POSITION_INIT",
    (payload: { motor: number; position: number }) => {
      console.log("Motor", payload.motor, "ist auf position", payload.position);
    }
  );

  return (
    <>
      <BackdropControl
        onDownPressed={onDownPressed}
        onStopPressed={onStopPressed}
        onUpPressed={onUpPressed}
      />
    </>
  );
}

export default App;
