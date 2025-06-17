package body Position is
   procedure Move_Down (P : in out Position_Type) is
   begin
      P.Y := (P.Y + 1) mod Board_Height;
   end Move_Down;

   procedure Move_Up (P : in out Position_Type) is
   begin
      P.Y := (P.Y + Board_Height - 1) mod Board_Height;
   end Move_Up;

   procedure Move_Right (P : in out Position_Type) is
   begin
      P.X := (P.X + 1) mod Board_Width;
   end Move_Right;

   procedure Move_Left (P : in out Position_Type) is
   begin
      P.X := (P.X + Board_Width - 1) mod Board_Width;
   end Move_Left;

   procedure Move_Direction (P : in out Position_Type; Direction : Integer) is
   begin
      case Direction is
         when 0 =>
            Move_Up (P);

         when 1 =>
            Move_Down (P);

         when 2 =>
            Move_Left (P);

         when 3 =>
            Move_Right (P);

         when others =>
            raise Constraint_Error with "Invalid direction";
      end case;
   end Move_Direction;

end Position;
