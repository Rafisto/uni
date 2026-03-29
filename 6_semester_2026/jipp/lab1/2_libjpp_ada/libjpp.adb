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
      
      for I in 2 .. Unsigned_64'Last loop
         exit when I * I > N;
         if N mod I = 0 then
         return I;
         end if;
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

   function Diophantine (m, n, z : Unsigned_64) return Diophantine_Result is
      A : Unsigned_64 := m;
      B : Unsigned_64 := n;
      X : Unsigned_64 := 1;
      Y : Unsigned_64 := 0;
      R : Unsigned_64 := b;
      S : Unsigned_64 := a - 1;
      
      RR, SS, REMA, QUOT, TMP : Unsigned_64;
   begin
      if m = 0 and n = 0 then
         return (X => 0, Y => 0, Err => z /= 0);
      end if;

      if n = 0 then
         if z mod m /= 0 then
            return (X => 0, Y => 0, Err => True);
         end if;
         return (X => z / m, Y => 0, Err => False);
      end if;

      if m = 0 then
         return (X => 0, Y => 0, Err => True);
      end if;

      if GCD(A, B) /= z then
         return (X => 0, Y => 0, Err => True);
      end if;

      while b > 0 loop
         REMA := A mod B;
         QUOT := A / B;
         A := B;
         B := REMA;
         RR := R;
         TMP := QUOT * R;
         if X < TMP then
            R := n * QUOT;
         else
            R := 0;
         end if;

         R := R + X;
         R := R - TMP;
         SS := S;
         TMP := QUOT * S;
         if Y < TMP then
            S := m * QUOT;
         else
            S := 0;
         end if;

         S := S + Y;
         S := S - TMP;
         X := RR;
         Y := SS;        
      end loop;

      return (X => X, Y => Y, Err => False);
   end Diophantine;

end Libjpp;