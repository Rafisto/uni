with Libjpp; use Libjpp;

generic
   N : Positive;
package Ring is
   type Value is new Integer range 0 .. N - 1;

   function Constructor(V : Integer) return Value;

   function repr(X : Value) return Integer;
   function To_String(X : Value) return String;

   function "+" (X, Y : Value) return Value;
   function "-" (X, Y : Value) return Value;
   function "*" (X, Y : Value) return Value; 
   function "/" (X, Y : Value) return Value;

   function "=" (X, Y : Value) return Boolean;
   function "<=" (X, Y : Value) return Boolean;
   function ">=" (X, Y : Value) return Boolean;
   function "<" (X, Y : Value) return Boolean;
   function ">" (X, Y : Value) return Boolean;

end;