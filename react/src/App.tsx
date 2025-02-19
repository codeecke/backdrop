import "./App.css";
import BackdropControl from "./components/backdropControl";
import ColorSelector from "./components/colorSelector";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "./components/ui/tabs";
import { RootState } from "./store";
import { setSelectedColor } from "./store/colorSlice";
import { TColor } from "./types";
import { useDispatch, useSelector } from "react-redux";
import { useActiveMotor } from "./store/motorSlice";

function App() {
  const availableColors = useSelector(
    (state: RootState) => state.colorReducer.available
  );
  const motor = useActiveMotor();
  const dispatch = useDispatch();

  return (
    <>
      <h1>Backdrop RC</h1>
      <ColorSelector
        colors={availableColors}
        onChange={(selected: TColor) => {
          dispatch(setSelectedColor(selected));
        }}
      />

      <Tabs defaultValue="account" className="w-screen mt-4">
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
        <TabsContent value="automatic">Change your password here.</TabsContent>
      </Tabs>
    </>
  );
}

export default App;
