import { Dispatch } from "@reduxjs/toolkit";
import { TClientCommandData } from ".";

export type TClientCommandExecuteParam<T extends TClientCommandData> = {
  payload: T["payload"];
  ws: WebSocket;
  dispatch: Dispatch;
};

export abstract class AbstractClientCommand<T extends TClientCommandData> {
  abstract execute(data: TClientCommandExecuteParam<T>): void;
}
