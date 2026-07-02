with Ada.Text_IO; use Ada.Text_IO;
with Interfaces;  use Interfaces;
with Wrapper;

procedure Test is
   procedure Test_Gcd is
      Max_Val : constant Unsigned_64 := 16#FFFF_FFFF_FFFF_FFFF#;
   begin
      -- Zero case
      pragma Assert (Wrapper.GCD (0, 0) = 0);

      -- Base cases
      pragma Assert (Wrapper.GCD (48, 18) = 6);
      pragma Assert (Wrapper.GCD (101, 103) = 1);

      -- One is a zero
      pragma Assert (Wrapper.GCD (0, 5) = 5);
      pragma Assert (Wrapper.GCD (5, 0) = 5);
      pragma Assert (Wrapper.GCD (0, 0) = 0);

      -- Max value
      pragma Assert (Wrapper.GCD (Max_Val, Max_Val) = Max_Val);
      pragma Assert (Wrapper.GCD (Max_Val, 1) = 1);

      -- Large co-prime numbers
      pragma
        Assert (Wrapper.GCD (7540113804746346429, 4660046610375530309) = 1);

      Put_Line ("test_gcd pass");
   end Test_Gcd;
   procedure Test_First_Prime_Div is
   begin
      -- Zero case
      pragma Assert (Wrapper.First_Prime_Div (0) = 0);

      -- Base cases
      pragma Assert (Wrapper.First_Prime_Div (31) = 31);
      pragma Assert (Wrapper.First_Prime_Div (29) = 29);
      pragma Assert (Wrapper.First_Prime_Div (4) = 2);

      -- Large primes
      pragma Assert (Wrapper.First_Prime_Div (104729) = 104729);

      -- Square factors
      pragma Assert (Wrapper.First_Prime_Div (121) = 11);
      pragma Assert (Wrapper.First_Prime_Div (961) = 31);

      Put_Line ("test_first_prime_div pass");
   end Test_First_Prime_Div;

   procedure Test_Phi is
   begin
      -- Zero case
      pragma Assert (Wrapper.Phi (0) = 0);

      -- Base cases
      pragma Assert (Wrapper.Phi (1) = 1);
      pragma Assert (Wrapper.Phi (2) = 1);
      pragma Assert (Wrapper.Phi (3) = 2);
      pragma Assert (Wrapper.Phi (9) = 6);
      pragma Assert (Wrapper.Phi (10) = 4);

      -- Larger composites
      pragma Assert (Wrapper.Phi (100) = 40);
      pragma Assert (Wrapper.Phi (1000) = 400);

      -- Co-prime property: phi(pq) = phi(p) * phi(q)
      pragma
        Assert (Wrapper.Phi (37) * Wrapper.Phi (39) = Wrapper.Phi (37 * 39));
      pragma Assert (Wrapper.Phi (101) * Wrapper.Phi (103) = 100 * 102);

      Put_Line ("test_phi pass");
   end Test_Phi;

   procedure Test_Diophantine is
      Res : Wrapper.Diophantine_Result;
   begin
      -- 15x - 10y = 5
      Res := Wrapper.Diophantine (15, 10, 5);
      pragma Assert (not Res.Err);
      pragma Assert (15 * Res.X - 10 * Res.Y = 5);

      -- 29x - 10y = gcd(29, 10)
      Res := Wrapper.Diophantine (29, 10, Wrapper.GCD (29, 10));
      pragma Assert (not Res.Err);
      pragma Assert (29 * Res.X - 10 * Res.Y = Wrapper.GCD (29, 10));

      -- Error case: c is not divisible by gcd(a, b)
      Res := Wrapper.Diophantine (29, 10, Wrapper.GCD (29, 10) + 1);
      pragma Assert (Res.Err);

      -- A is zero
      Res := Wrapper.Diophantine (0, 10, 10);
      pragma Assert (Res.Err);

      -- B is zero
      Res := Wrapper.Diophantine (10, 0, 10);
      pragma Assert (not Res.Err);
      pragma Assert (Res.X = 1);

      -- C is zero
      Res := Wrapper.Diophantine (10, 10, 0);
      -- Note: Based on your C code, this expected Err to be true
      pragma Assert (Res.Err);
      pragma Assert (10 * Res.X - 10 * Res.Y = 0);

      Put_Line ("test_diophantine pass");
   end Test_Diophantine;

begin
   Test_Gcd;
   Test_First_Prime_Div;
   Test_Phi;
   Test_Diophantine;
end Test;
