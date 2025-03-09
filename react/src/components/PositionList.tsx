import { TPosition } from "@/classes/ClientCommands/PositionListCommand";
import { Motor } from "@/classes/socketClients/Motor";
import { RootState } from "@/store";
import { FC } from "react";
import { useSelector } from "react-redux";

interface PositionListParams {
  motor: Motor;
}

export const PositionList: FC<PositionListParams> = ({ motor }) => {
  const positionList: TPosition[] =
    useSelector((state: RootState) => state.positionListReducer.positions) ||
    [];
  return (
    <ul>
      {positionList.map((position: TPosition, index: number) => (
        <li
          key={index}
          className="flex bg-white p-4 cursor-pointer"
          onClick={() => motor.moveTo(position.position)}
        >
          {position.name}
        </li>
      ))}
    </ul>
  );
};
