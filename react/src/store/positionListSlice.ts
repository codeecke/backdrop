import { TWebSocketPositionListUpdateEventPayload } from "@/types";
import { createSlice } from "@reduxjs/toolkit";

interface PositionListState {
  positions: TWebSocketPositionListUpdateEventPayload;
}

const initialState: PositionListState = {
  positions: [],
};

const positionListSlice = createSlice({
  name: "positionList",
  initialState,
  reducers: {
    setPositionList(
      state: PositionListState,
      { payload }: { payload: TWebSocketPositionListUpdateEventPayload }
    ) {
      console.log("set state", payload);
      state.positions = payload;
      return state;
    },
  },
});

export const { setPositionList } = positionListSlice.actions;
export default positionListSlice.reducer;
