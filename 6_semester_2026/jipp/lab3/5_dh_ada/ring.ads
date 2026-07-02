with Libjpp; use Libjpp;
with Interfaces; use Interfaces;

generic
   N : Unsigned_64;
package Ring is
   type Value is new Unsigned_64 range Unsigned_64'(0) .. Unsigned_64(N) - 1;

   function Initialize(V : Unsigned_64) return Value;

   function repr(V : Value) return Unsigned_64;
   function To_String(V : Value) return String;
   function g return Unsigned_64;

   function "+" (L, R : Value) return Value;
   function "-" (L, R : Value) return Value;
   function "*" (L, R : Value) return Value; 
   function "/" (L, R : Value) return Value;
   function "**" (L : Value; R : Unsigned_64) return Value;

   function "=" (L, R : Value) return Boolean;
   function "<=" (L, R : Value) return Boolean;
   function ">=" (L, R : Value) return Boolean;
   function "<" (L, R : Value) return Boolean;
   function ">" (L, R : Value) return Boolean;

end;