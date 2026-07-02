with Ada.Text_IO; use Ada.Text_IO;
with Ring;
with Libjpp; use Libjpp;

procedure Main is
   package Ring17 is new Ring (N => 17);
   package Ring15 is new Ring (N => 15);

   use Ring17;
   use Ring15;

   procedure Test_Op_Add is
      Op1 : Ring17.Value := Ring17.Initialize (8);
      Op2 : Ring17.Value := Ring17.Initialize (10);
      Oq1 : Ring15.Value := Ring15.Initialize (4);
      Oq2 : Ring15.Value := Ring15.Initialize (9);
   begin
      pragma Assert (Op1 + Op2 = Ring17.Initialize (1));

      pragma Assert (Oq1 + Oq2 = Ring15.Initialize (13));
      pragma Assert (Oq1 + Oq1 + Oq2 = Ring15.Initialize (2));
      
      Put_Line ("Test_Op_Add passed");
   end Test_Op_Add;

   procedure Test_Op_Sub is
      Op1 : Ring17.Value := Ring17.Initialize (9);
      Op2 : Ring17.Value := Ring17.Initialize (13);
      Oq1 : Ring15.Value := Ring15.Initialize (9);
      Oq2 : Ring15.Value := Ring15.Initialize (13);
   begin
      pragma Assert (Op2 - Op1 = Ring17.Initialize (4));
      pragma Assert (Op1 - Op2 = Ring17.Initialize (13));
      
      pragma Assert (Oq2 - Oq1 = Ring15.Initialize (4));
      pragma Assert (Oq1 - Oq2 = Ring15.Initialize (11));
      
      Put_Line ("Test_Op_Sub passed");
   end Test_Op_Sub;

   procedure Test_Op_Mul is
      Op1 : Ring17.Value := Ring17.Initialize (9);
      Op2 : Ring17.Value := Ring17.Initialize (13);
      Oq1 : Ring15.Value := Ring15.Initialize (9);
      Oq2 : Ring15.Value := Ring15.Initialize (13);
   begin
      pragma Assert (Op1 * Op2 = Ring17.Initialize (15));
      pragma Assert (Oq1 * Oq2 = Ring15.Initialize (12));
      
      Put_Line ("Test_Op_Mul passed");
   end Test_Op_Mul;

   procedure Test_Op_Div_Prime is
      Op1 : Ring17.Value := Ring17.Initialize (9);
      Op2 : Ring17.Value := Ring17.Initialize (13);
   begin
      pragma Assert (Op1 / Op2 = Ring17.Initialize (2));
      Put_Line ("Test_Op_Div_Prime passed");
   end Test_Op_Div_Prime;

   procedure Test_Op_Div_Composite is
      Oq1 : Ring15.Value := Ring15.Initialize (9);
      Oq2 : Ring15.Value := Ring15.Initialize (13);
      Thr : Ring15.Value := Ring15.Initialize (12);
      Res : Ring15.Value;
   begin
      pragma Assert (Oq1 / Oq2 = Ring15.Initialize (3));
      
      begin
         Res := Oq1 / Thr;
         raise Program_Error with "Should've thrown inversion error";
      exception
         when Constraint_Error =>
            null; 
      end;

      Put_Line ("Test_Op_Div_Composite passed");
   end Test_Op_Div_Composite;

   procedure Test_Comparisons is
      A : Ring15.Value := Ring15.Initialize (9);
      B : Ring15.Value := Ring15.Initialize (13);
      C : Ring15.Value := Ring15.Initialize (14);
      D : Ring15.Value := Ring15.Initialize (9);
   begin
      pragma Assert ((A = B) = False);
      pragma Assert ((A = D) = True);
      pragma Assert ((A /= B) = True);
      pragma Assert ((A <= B) = True);
      pragma Assert ((A >= B) = False);
      pragma Assert ((A > B) = False);
      pragma Assert ((A < B) = True);
      
      Put_Line ("Test_Comparisons passed");
   end Test_Comparisons;

   procedure Test_Repr is
      A : Ring17.Value := Ring17.Initialize (10);
   begin
      Put_Line ("Repr of A: " & Integer'Image (Ring17.repr (A)));
      Put_Line ("String Repr of A: " & Ring17.To_String (A));
   end Test_Repr;

begin
   Test_Op_Add;
   Test_Op_Sub;
   Test_Op_Mul;
   Test_Op_Div_Prime;
   Test_Op_Div_Composite;
   Test_Comparisons;
   Test_Repr;
   
   Put_Line ("All tests passed successfully.");
end Main;