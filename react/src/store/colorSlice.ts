import { TColor } from "@/types";
import { createSlice } from "@reduxjs/toolkit";

interface ColorState {
  selected: TColor | undefined;
  available: TColor[];
}

const initialState: ColorState = {
  selected: undefined,
  available: [
    { id: 1, name: "black", code: "#000000" },
    { id: 2, name: "white", code: "#ffffff" },
  ],
};

const colorSlice = createSlice({
  name: "color",
  initialState,
  reducers: {
    setSelectedColor: (state: ColorState, { payload }: { payload: TColor }) => {
      state.selected = payload;
    },
  },
});

export const { setSelectedColor } = colorSlice.actions;

export default colorSlice.reducer;
