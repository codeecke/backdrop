import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import "./index.css";
import App from "./App.tsx";

if (screen.orientation && screen.orientation.lock) {
  screen.orientation.lock("portrait").catch((err) => {
    console.error("Ausrichtungssperre fehlgeschlagen:", err);
  });
} else {
  console.warn("Ausrichtungssperre nicht unterstützt.");
}

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <App />
  </StrictMode>
);
