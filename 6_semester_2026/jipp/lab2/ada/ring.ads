with Libjpp; use Libjpp;

generic
   N : Positive;
package Ring is
   type Value is new Integer range 0 .. N - 1;

   function Constructor(V : Integer) return Value;

   function repr(V : Value) return Integer;
   function To_String(V : Value) return String;

   function "+" (L, R : Value) return Value;
   function "-" (L, R : Value) return Value;
   function "*" (L, R : Value) return Value; 
   function "/" (L, R : Value) return Value;

   function "=" (L, R : Value) return Boolean;
   function "<=" (L, R : Value) return Boolean;
   function ">=" (L, R : Value) return Boolean;
   function "<" (L, R : Value) return Boolean;
   function ">" (L, R : Value) return Boolean;

end;