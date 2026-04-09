with Ada.Strings.Fixed;
with Interfaces; use Interfaces;
with Libjpp; use Libjpp;

package body Ring is
   function Constructor (V : Integer) return Value is
   begin
      return Value (V mod N);
   end Constructor;

   function repr (X : Value) return Integer is
   begin
      return Integer (X);
   end repr;

   function To_String (X : Value) return String is
      Val_Str : constant String := Ada.Strings.Fixed.Trim (Integer'Image (Integer (X)), Ada.Strings.Both);
      N_Str   : constant String := Ada.Strings.Fixed.Trim (Integer'Image (N), Ada.Strings.Both);
   begin
      return "Ring<" & N_Str & ">(" & Val_Str & ")";
   end To_String;

   function "+" (X, Y : Value) return Value is
   begin
      return Value ((Integer (X) + Integer (Y)) mod N);
   end "+";

   function "-" (X, Y : Value) return Value is
   begin
      return Value ((Integer (X) - Integer (Y)) mod N);
   end "-";

   function "*" (X, Y : Value) return Value is
   begin
      return Value ((Integer (X) * Integer (Y)) mod N);
   end "*";

   function "/" (X, Y : Value) return Value is
      Res : Diophantine_Result;
   begin
      Res := Diophantine (Unsigned_64 (Y), Unsigned_64 (N), 1);

      if Res.Err /= False then
         raise Constraint_Error with "Divisor is not invertible";
      end if;

      return Value ((Integer (X) * Integer (Res.X)) mod N);
   end "/";

   function "=" (X, Y : Value) return Boolean is
   begin
      return Integer (X) = Integer (Y);
   end "=";

   function "<=" (X, Y : Value) return Boolean is
   begin
      return Integer (X) <= Integer (Y);
   end "<=";

   function ">=" (X, Y : Value) return Boolean is
   begin
      return Integer (X) >= Integer (Y);
   end ">=";

   function "<" (X, Y : Value) return Boolean is
   begin
      return Integer (X) < Integer (Y);
   end "<";

   function ">" (X, Y : Value) return Boolean is
   begin
      return Integer (X) > Integer (Y);
   end ">";

end Ring;
