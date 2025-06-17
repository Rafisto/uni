with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;

package body Random_Seeds is
   
   function Make_Seeds(Size : Positive) return Seed_Array_Type is
      GG : Generator ; -- random generator
      Seed_Array :  Seed_Array_Type(1 .. Size);
   begin
      Reset(GG); -- Start the generator in a unique state in each run
      for I in Seed_Array'Range loop
	 Seed_Array(I) := Integer( Seed_Range * Random(GG)) ;
      end loop;
      return Seed_Array;
   end;
end Random_Seeds;

