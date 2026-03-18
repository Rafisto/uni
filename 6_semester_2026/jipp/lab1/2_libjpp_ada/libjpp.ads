with Interfaces; use Interfaces;

package Libjpp is
   type Diophantine_Result is record
      X   : Unsigned_64;
      Y   : Unsigned_64;
      Err : Boolean;
   end record;

   function GCD (X, Y : Unsigned_64) return Unsigned_64;
   function First_Prime_Div (N : Unsigned_64) return Unsigned_64;
   function Phi (N : Unsigned_64) return Unsigned_64;
   function Diophantine (A, B, C : Unsigned_64) return Diophantine_Result;

end Libjpp;