with Ada.Text_IO; use Ada.Text_IO;
with Interfaces;  use Interfaces;
with Ring;
with DH;

procedure Main is
   N_Val : constant Unsigned_64 := 1234567891;
   package InstanceRing is new Ring (N => N_Val);
   package InstanceDH is new DH (N_Val => N_Val, RingInstance => InstanceRing);
   
   use InstanceDH.Setup;
   use InstanceDH.External_User;
   use InstanceRing;

   Domain : aliased DH_Setup := Initialize;

   Alice : User := Create_User (Domain'Access);
   Bob   : User := Create_User (Domain'Access);

   Alice_Pub : constant InstanceDH.T := Get_Public_Key (Alice);
   Bob_Pub   : constant InstanceDH.T := Get_Public_Key (Bob);

   Secret_Msg : constant InstanceDH.T := InstanceRing.Initialize (7);
   Cipher     : InstanceDH.T;
   Recovered  : InstanceDH.T;
begin
   Set_Key (Alice, Bob_Pub);
   Set_Key (Bob, Alice_Pub);

   Cipher    := Encrypt (Alice, Secret_Msg);
   Recovered := Decrypt (Bob, Cipher);

   Put_Line ("--- Diffie-Hellman Key Exchange Demo ---");
   Put_Line ("Original Message:  " & Unsigned_64'Image (InstanceRing.repr (Secret_Msg)));
   Put_Line ("Encrypted Cipher:  " & Unsigned_64'Image (InstanceRing.repr (Cipher)));
   Put_Line ("Decrypted Message: " & Unsigned_64'Image (InstanceRing.repr (Recovered)));
   
   if Secret_Msg = Recovered then
      Put_Line ("Success: Messages match!");
   else
      Put_Line ("Failure: Messages do not match.");
   end if;
end Main;