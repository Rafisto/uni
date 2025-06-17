with Parameters; use Parameters;

package Position is
   type Position_Type is record
      X : Integer range 0 .. Board_Width;
      Y : Integer range 0 .. Board_Height;
   end record;

   procedure Move_Up (P : in out Position_Type);
   procedure Move_Down (P : in out Position_Type);
   procedure Move_Left (P : in out Position_Type);
   procedure Move_Right (P : in out Position_Type);
   procedure Move_Direction (P : in out Position_Type; Direction : Integer);

end Position;
