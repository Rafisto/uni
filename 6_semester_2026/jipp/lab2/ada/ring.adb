with Ada.Strings.Fixed;
with Interfaces; use Interfaces;
with Libjpp; use Libjpp;

package body Ring is
   function Constructor (V : Integer) return Value is
   begin
      return Value (V mod N);
   end Constructor;

   function repr (V : Value) return Integer is
   begin
      return Integer (V);
   end repr;

   function To_String (V : Value) return String is
      Val_Str : constant String := Ada.Strings.Fixed.Trim (Integer'Image (Integer (V)), Ada.Strings.Both);
      N_Str   : constant String := Ada.Strings.Fixed.Trim (Integer'Image (N), Ada.Strings.Both);
   begin
      return "Ring<" & N_Str & ">(" & Val_Str & ")";
   end To_String;

   function "+" (L, R : Value) return Value is
   begin
      return Value ((Integer (L) + Integer (R)) mod N);
   end "+";

   function "-" (L, R : Value) return Value is
   begin
      return Value ((Integer (L) - Integer (R)) mod N);
   end "-";

   function "*" (L, R : Value) return Value is
   begin
      return Value ((Integer (L) * Integer (R)) mod N);
   end "*";

   function "/" (L, R : Value) return Value is
      Res : Diophantine_Result;
   begin
      Res := Diophantine (Unsigned_64 (R), Unsigned_64 (N), 1);

      if Res.Err /= False then
         raise Constraint_Error with "Divisor is not invertible";
      end if;

      return Value ((Integer (L) * Integer (Res.X)) mod N);
   end "/";

   function "=" (L, R : Value) return Boolean is
   begin
      return Integer (L) = Integer (R);
   end "=";

   function "<=" (L, R : Value) return Boolean is
   begin
      return Integer (L) <= Integer (R);
   end "<=";

   function ">=" (L, R : Value) return Boolean is
   begin
      return Integer (L) >= Integer (R);
   end ">=";

   function "<" (L, R : Value) return Boolean is
   begin
      return Integer (L) < Integer (R);
   end "<";

   function ">" (L, R : Value) return Boolean is
   begin
      return Integer (L) > Integer (R);
   end ">";

end Ring;
