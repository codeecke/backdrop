import { Motor } from "@/classes/socketClients/Motor";
import { RootState } from "@/store";
import {
  TWebSocketPositionListUpdateEventPayload,
  TWebSocketPositionListUpdateEventPayloadItem,
} from "@/types";
import { FC } from "react";
import { useSelector } from "react-redux";

interface PositionListParams {
  motor: Motor;
}

export const PositionList: FC<PositionListParams> = ({ motor }) => {
  const positionList: TWebSocketPositionListUpdateEventPayload =
    useSelector((state: RootState) => {
      console.log(state);
      return state.positionListReducer.positions;
    }) || [];
  return (
    <ul>
      {positionList.map(
        (position: TWebSocketPositionListUpdateEventPayloadItem) => (
          <li
            key={position.position}
            className="flex bg-white p-4 cursor-pointer"
            onClick={() => motor.moveTo(position.position)}
          >
            {position.name}
          </li>
        )
      )}
    </ul>
  );
};
