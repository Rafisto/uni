with Ada.Text_IO; use Ada.Text_IO;
with Interfaces;  use Interfaces;
with Ring;
with DH;

procedure Main is
   N_Val : constant Unsigned_64 := 1234567891;
   package InstanceRing is new Ring (N => N_Val);
   package InstanceDH is new DH (N_Val => N_Val, RingInstance => InstanceRing);

   use InstanceDH.Setup;
   use InstanceDH.User;
   use InstanceRing;

   Domain : aliased DH_Setup := Initialize;

   Alice : User := Create_User (Domain'Access);
   Bob   : User := Create_User (Domain'Access);

   Alice_Pub : constant InstanceDH.T := Get_Public_Key (Alice);
   Bob_Pub   : constant InstanceDH.T := Get_Public_Key (Bob);

   Secret_Msg : constant InstanceDH.T := InstanceRing.Initialize (12345);
   Encrypted  : InstanceDH.T;
   Decrypted  : InstanceDH.T;
begin
   Set_Key (Alice, Bob_Pub);
   Set_Key (Bob, Alice_Pub);

   Encrypted := Encrypt (Alice, Secret_Msg);
   Decrypted := Decrypt (Bob, Encrypted);

   Put_Line("Original: "& Unsigned_64'Image (InstanceRing.repr (Secret_Msg)));
   Put_Line("Encrypted: "& Unsigned_64'Image (InstanceRing.repr (Encrypted)));
   Put_Line("Decrypted: "& Unsigned_64'Image (InstanceRing.repr (Decrypted)));

   if Secret_Msg = Decrypted then
      Put_Line ("DH Works");
   else
      Put_Line ("DH Fails");
   end if;
end Main;
