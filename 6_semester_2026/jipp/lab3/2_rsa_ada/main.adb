with Ada.Text_IO; use Ada.Text_IO;
with Interfaces; use Interfaces;
with Ada.Assertions; use Ada.Assertions;
with Ring;
with RSA;

procedure Main is
   P : Unsigned_64 := 10007;
   Q : Unsigned_64 := 10009;
   Modulus : Unsigned_64 := P * Q;

   package RingInstance is new Ring (N => Modulus);
   package RSAInstance is new RSA (N_Val => Modulus, RingInstance => RingInstance);

   use RingInstance;
   use RSAInstance;

   Message   : RingInstance.Value;
   Encrypted : RingInstance.Value;
   Decrypted : RingInstance.Value;
   Setup     : RSAInstance.RSASetup; 
begin
   Setup := RSAInstance.Initialize (P => P, Q => Q);

   Message := RingInstance.Initialize (12345);
   
   Encrypted := Setup.Encrypt (Message);
   Decrypted := Setup.Decrypt (Encrypted);

   Put_Line ("Message: " & RingInstance.To_String (Message));
   Put_Line ("Encrypted: " & RingInstance.To_String (Encrypted));
   Put_Line ("Decrypted: " & RingInstance.To_String (Decrypted));

   Assert (Message = Decrypted);
end Main;