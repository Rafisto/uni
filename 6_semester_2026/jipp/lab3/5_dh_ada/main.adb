with Ada.Text_IO;     use Ada.Text_IO;
with Ada.Assertions;  use Ada.Assertions;
with Interfaces;      use Interfaces;
with Ring;
with DH;

procedure Main is
   package RingInstance is new Ring (N => 1234567891);
   package DHInstance is new DH (N_Val => 1234567891, RingInstance => RingInstance);

   use RingInstance;
   use DHInstance;

   Setup : aliased DH_Setup := Initialize;
   A_SK : User (Setup => Setup'Access) := Create_User (Setup'Access);
   B_SK   : User (Setup => Setup'Access) := Create_User (Setup'Access);

   A_PK : T := Get_Public_Key (A_SK);
   B_PK   : T := Get_Public_Key (B_SK);

   Msg      : T := Get_Generator (Setup);
   Cipher   : T;
   Decoded  : T;
begin
   Set_Key (A_SK, B_PK);
   Set_Key (B_SK, A_PK);

   Cipher  := Encrypt (A_SK, Msg);
   Decoded := Decrypt (B_SK, Cipher);

   Assert (Decoded = Msg);
   Put_Line ("DH test passed.");
end Main;