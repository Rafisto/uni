with Interfaces; use Interfaces;
with Ada.Numerics.Discrete_Random;

package body RSA is
   use RingInstance;

   function Initialize (P : Unsigned_64; Q : Unsigned_64) return RSASetup is
      Phi        : Unsigned_64 := (P - 1) * (Q - 1);
      Temp_E     : Unsigned_64;
      Res        : Diophantine_Result;
      Result_Obj : RSASetup;

      package Rand_U64 is new Ada.Numerics.Discrete_Random (Unsigned_64);
      Gen : Rand_U64.Generator;
      R   : Unsigned_64;
   begin
      Result_Obj.M := P * Q;

      Rand_U64.Reset (Gen);
      loop
         R := Rand_U64.Random (Gen);
         Temp_E := Unsigned_64 (2 + (R mod (Unsigned_64 (Phi) - 2)));
         exit when GCD (Unsigned_64 (Temp_E), Unsigned_64 (Phi)) = 1;
      end loop;

      Result_Obj.E := RingInstance.Initialize (Temp_E);

      Res := Diophantine (Unsigned_64 (Temp_E), Unsigned_64 (Phi), 1);
      if Res.Err then
         raise Program_Error with "unexpected gcd(e, phi) != 1";
      end if;

      Result_Obj.D := RingInstance.Initialize (Unsigned_64 (((Res.X mod Unsigned_64(Phi)) + Unsigned_64(Phi)) mod Unsigned_64(Phi)));

      return Result_Obj;
   end Initialize;

   function GetModulo (Self : RSASetup) return Unsigned_64 is
   begin
      return Self.M;
   end GetModulo;

   function GetPublicKey (Self : RSASetup) return RingInstance.Value is
   begin
      return Self.E;
   end GetPublicKey;

   function Encrypt
     (Self : RSASetup; M : RingInstance.Value) return RingInstance.Value is
   begin
      return M ** Unsigned_64 (RingInstance.repr (Self.E));
   end Encrypt;

   function Decrypt
     (Self : RSASetup; C : RingInstance.Value) return RingInstance.Value is
   begin
      return C ** Unsigned_64 (RingInstance.repr (Self.D));
   end Decrypt;

end RSA;
