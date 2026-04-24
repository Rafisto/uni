with Ada.Strings.Fixed;
with Interfaces; use Interfaces;
with Libjpp;     use Libjpp;

package body Ring is
   function Initialize (V : Unsigned_64) return Value is
   begin
      return Value (V mod N);
   end Initialize;

   function repr (V : Value) return Unsigned_64 is
   begin
      return Unsigned_64 (V);
   end repr;

   function To_String (V : Value) return String is
      Val_Str : constant String :=
        Ada.Strings.Fixed.Trim
          (Unsigned_64'Image (Unsigned_64 (V)), Ada.Strings.Both);
      N_Str   : constant String :=
        Ada.Strings.Fixed.Trim (Unsigned_64'Image (N), Ada.Strings.Both);
   begin
      return "Ring<" & N_Str & ">(" & Val_Str & ")";
   end To_String;

   function g return Unsigned_64 is
      Temp_G : Unsigned_64 := 2;
      Pow       : Unsigned_64;
      Res       : Diophantine_Result;
   begin
      if N <= 2 then
         return 0;
      end if;

      loop
         Pow := Unsigned_64 ((Value (Temp_G)) ** (N - 1));
         Res := Diophantine (Pow, N, 1);

         exit when Res.Err = False;

         if Temp_G + 1 >= N then
            return 2;
         end if;

         Temp_G := Temp_G + 1;
      end loop;

      return Temp_G;
   end g;

   function "+" (L, R : Value) return Value is
   begin
      return Value ((Unsigned_64 (L) + Unsigned_64 (R)) mod N);
   end "+";

   function "-" (L, R : Value) return Value is
   begin
      return Value ((Unsigned_64 (L) - Unsigned_64 (R)) mod N);
   end "-";

   function "*" (L, R : Value) return Value is
   begin
      return Value ((Unsigned_64 (L) * Unsigned_64 (R)) mod N);
   end "*";

   function "/" (L, R : Value) return Value is
      Res : Diophantine_Result;
   begin
      Res := Diophantine (Unsigned_64 (R), Unsigned_64 (N), 1);

      if Res.Err /= False then
         raise Constraint_Error with "Divisor is not invertible";
      end if;

      return Value ((Unsigned_64 (L) * Unsigned_64 (Res.X)) mod N);
   end "/";

   function "**" (L : Value; R : Unsigned_64) return Value is
      Res  : Value := Initialize (1);
      Base : Value := L;
      Exp  : Unsigned_64 := R;
   begin
      while Exp > 0 loop
         if (Exp mod 2) = 1 then
            Res := Res * Base;
         end if;
         Base := Base * Base;
         Exp := Exp / 2;
      end loop;
      return Res;
   end "**";

   function "=" (L, R : Value) return Boolean is
   begin
      return Unsigned_64 (L) = Unsigned_64 (R);
   end "=";

   function "<=" (L, R : Value) return Boolean is
   begin
      return Unsigned_64 (L) <= Unsigned_64 (R);
   end "<=";

   function ">=" (L, R : Value) return Boolean is
   begin
      return Unsigned_64 (L) >= Unsigned_64 (R);
   end ">=";

   function "<" (L, R : Value) return Boolean is
   begin
      return Unsigned_64 (L) < Unsigned_64 (R);
   end "<";

   function ">" (L, R : Value) return Boolean is
   begin
      return Unsigned_64 (L) > Unsigned_64 (R);
   end ">";

end Ring;
