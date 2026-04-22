with Interfaces; use Interfaces;
with Ada.Numerics.Discrete_Random;
with Libjpp; use Libjpp;

package body DH is
   use RingInstance;

   package Rand_U64 is new Ada.Numerics.Discrete_Random (Unsigned_64);

   function Initialize return DH_Setup is
      Gen    : Rand_U64.Generator;
      R      : Unsigned_64;
      G_Val  : Unsigned_64;
      Result : DH_Setup;
      Cand   : T;
   begin
      if N_Val <= 2 then
         raise Program_Error with "N_Val must be > 2";
      end if;

      Rand_U64.Reset (Gen);

      loop
         R := Rand_U64.Random (Gen);
         G_Val := 2 + (R mod (N_Val - 2));
         Cand := RingInstance.Initialize (G_Val);
         exit when GCD (Unsigned_64 (RingInstance.repr (Cand ** (N_Val - 1))), N_Val) = 1;
      end loop;

      Result.Generator := Cand;
      return Result;
   end Initialize;

   function Get_Generator (Self : DH_Setup) return T is
   begin
      return Self.Generator;
   end Get_Generator;

   function Power (Self : DH_Setup; A : T; B : Unsigned_64) return T is
      pragma Unreferenced (Self);
   begin
      return A ** B;
   end Power;

   function Create_User (Setup : DH_Setup_Access) return User is
      Gen    : Rand_U64.Generator;
      R      : Unsigned_64;
      Result : User (Setup);
   begin
      if Setup = null then
         raise Program_Error with "Setup must not be null";
      end if;

      Rand_U64.Reset (Gen);
      R := Rand_U64.Random (Gen);

      if N_Val > 3 then
         Result.Secret := 2 + (R mod (N_Val - 3));
      else
         Result.Secret := 1;
      end if;

      Result.Key := RingInstance.Initialize (1);
      Result.Has_Key := False;
      return Result;
   end Create_User;

   function Get_Public_Key (Self : User) return T is
   begin
      return Self.Setup.all.Generator ** Self.Secret;
   end Get_Public_Key;

   procedure Set_Key (Self : in out User; A : T) is
   begin
      Self.Key := A ** Self.Secret;
      Self.Has_Key := True;
   end Set_Key;

   function Encrypt (Self : User; M : T) return T is
   begin
      if not Self.Has_Key then
         raise Program_Error with "shared key not set";
      end if;
      return M * Self.Key;
   end Encrypt;

   function Decrypt (Self : User; C : T) return T is
   begin
      if not Self.Has_Key then
         raise Program_Error with "shared key not set";
      end if;
      return C / Self.Key;
   end Decrypt;

end DH;