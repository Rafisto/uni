with Interfaces; use Interfaces;
with Interfaces.C; use Interfaces.C;

package Wrapper is
   pragma Pure;
   type Diophantine_Result is record
      X   : Unsigned_64;
      Y   : Unsigned_64;
      Err : Boolean;
   end record;
   pragma Convention (C, Diophantine_Result);

   function GCD (A, B : Unsigned_64) return Unsigned_64;
   pragma Import (C, GCD, "gcd");

   function First_Prime_Div (N : Unsigned_64) return Unsigned_64;
   pragma Import (C, First_Prime_Div, "first_prime_div");

   function Phi (N : Unsigned_64) return Unsigned_64;
   pragma Import (C, Phi, "phi");

   function Diophantine (A, B, C : Unsigned_64) return Diophantine_Result;
   pragma Import (C, Diophantine, "diophantine");

end Wrapper;