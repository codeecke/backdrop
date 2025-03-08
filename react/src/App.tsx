import "./App.css";
import BackdropControl from "./components/backdropControl";
import ColorSelector from "./components/colorSelector";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "./components/ui/tabs";
import { RootState } from "./store";
import { setSelectedColor } from "./store/colorSlice";
import { TColor, TWebSocketPositionListUpdateEventPayload } from "./types";
import { useDispatch, useSelector } from "react-redux";
import { useActiveMotor } from "./store/motorSlice";
import { useWebSocketEvent } from "./components/WebSocketProvider";
import { WebSocketEventName } from "./validators";
import { useEffect } from "react";
import { setPositionList } from "./store/positionListSlice";
import { PositionList } from "./components/PositionList";

function App() {
  const availableColors = useSelector(
    (state: RootState) => state.colorReducer.available
  );
  const motor = useActiveMotor();
  const dispatch = useDispatch();
  const event = useWebSocketEvent();

  useEffect(() => {
    if (!event) return;
    console.log("eventlistener initialized");
    event.addEventListener(WebSocketEventName.PositionListUpdate, (payload) => {
      console.log("positions loeded", payload);
      dispatch(
        setPositionList(payload as TWebSocketPositionListUpdateEventPayload)
      );
    });
  }, [event]);

  return (
    <>
      <h1>Backdrop RC</h1>
      <ColorSelector
        colors={availableColors}
        onChange={(selected: TColor) => {
          dispatch(setSelectedColor(selected));
        }}
      />

      <Tabs defaultValue="automatic" className="w-screen mt-4">
        <TabsList className="bg-white w-screen">
          <TabsTrigger value="manuel">Manuell</TabsTrigger>
          <TabsTrigger value="automatic">Automatisch</TabsTrigger>
        </TabsList>
        <TabsContent value="manuel">
          {!motor && <p>Bitte wähle eine Farbe</p>}
          {motor && (
            <BackdropControl
              onDownPressed={() => motor.moveDown()}
              onUpPressed={() => motor.moveUp()}
              onStopPressed={() => motor.stop()}
            />
          )}
        </TabsContent>
        <TabsContent value="automatic">
          {motor && <PositionList motor={motor} />}
        </TabsContent>
      </Tabs>
    </>
  );
}

export default App;
