import { createRoot } from "react-dom/client";
import "./index.css";
import App from "./App.tsx";
import { Provider } from "react-redux";
import { WebsocketProvider } from "./components/WebSocketProvider.tsx";
import { store } from "./store/index.ts";

createRoot(document.getElementById("root")!).render(
  <Provider store={store}>
    <WebsocketProvider>
      <App />
    </WebsocketProvider>
  </Provider>
);
