package body Libjpp is

   function GCD (X, Y : Unsigned_64) return Unsigned_64 is
      Temp_X : Unsigned_64 := X;
      Temp_Y : Unsigned_64 := Y;
      T      : Unsigned_64;
   begin
      while Temp_Y /= 0 loop
         T := Temp_Y;
         Temp_Y := Temp_X mod Temp_Y;
         Temp_X := T;
      end loop;
      return Temp_X;
   end GCD;

   function First_Prime_Div (N : Unsigned_64) return Unsigned_64 is
      I : Unsigned_64 := 2;
   begin
      if N <= 1 then return 0; end if;
      
      while I * I <= N loop
         if N mod I = 0 then
            return I;
         end if;
         I := I + 1;
      end loop;
      return N;
   end First_Prime_Div;

   function Phi (N : Unsigned_64) return Unsigned_64 is
      Res : Unsigned_64 := 0;
   begin
      for I in 1 .. N loop
         if GCD(I, N) = 1 then
            Res := Res + 1;
         end if;
      end loop;
      return Res;
   end Phi;

   function Diophantine (A, B, C : Unsigned_64) return Diophantine_Result is
      UA : Unsigned_64 := A;
      UB : Unsigned_64 := B;
      X : Unsigned_64 := 1;
      Y : Unsigned_64 := 0;
      R : Unsigned_64 := B;
      S : Unsigned_64 := A - 1;
      
      RR, SS, Tmp, Q : Unsigned_64;
   begin
      if C mod GCD(A, B) /= 0 then
         return (X => 0, Y => 0, Err => True);
      end if;

      while UB > 0 loop
         Q := UA / UB;
         UA := UA mod UB;
         exit; 
      end loop;

      return (X => X * C, Y => Y * C, Err => False);
   end Diophantine;

end Libjpp;