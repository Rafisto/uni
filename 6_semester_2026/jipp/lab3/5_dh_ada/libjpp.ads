with Interfaces; use Interfaces;
with Interfaces.C; use Interfaces.C;

package Libjpp is
   type Diophantine_Result is record
      X   : Unsigned_64;
      Y   : Unsigned_64;
      Err : Boolean;
   end record;

   function GCD (X, Y : Unsigned_64) return Unsigned_64
      with Convention => C, Export => True,
      External_Name => "gcd";

   function First_Prime_Div (N : Unsigned_64) return Unsigned_64
      with Convention => C, Export => True,
      External_Name => "first_prime_div";

   function Phi (N : Unsigned_64) return Unsigned_64
      with Convention => C, Export => True,
      External_Name => "phi";

   function Diophantine (m, n, z : Unsigned_64) return Diophantine_Result
      with Convention => C, Export => True,
      External_Name => "diophantine";

end Libjpp;