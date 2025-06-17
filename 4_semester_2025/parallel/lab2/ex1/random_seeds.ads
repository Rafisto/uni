with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;

package Random_Seeds is
   Seed_Range : constant Float := 1.0E6 ;
   type Seed_Array_Type is array (Positive range <>) of Integer;
   function Make_Seeds(Size : Positive) return Seed_Array_Type;
end Random_Seeds;

