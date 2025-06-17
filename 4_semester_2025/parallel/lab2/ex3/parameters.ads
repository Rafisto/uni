with Ada.Real_Time; use Ada.Real_Time;

with Random_Seeds; use Random_Seeds;

package Parameters is
   Nr_Of_Travelers : constant Integer := 15;
   Nr_Of_Squatters : constant Integer := 10;
   Nr_Of_Traps     : constant Integer := 10;
   Nr_Total        : constant Integer := Nr_Of_Travelers + Nr_Of_Squatters;
   Min_Steps       : constant Integer := 10;
   Max_Steps       : constant Integer := 100;
   Min_Delay       : constant Duration := 0.01;
   Max_Delay       : constant Duration := 0.05;
   Board_Width     : constant Integer := 15;
   Board_Height    : constant Integer := 15;
   Start_Time      : Time := Clock;
   Seeds           : Seed_Array_Type (1 .. Nr_Total + Nr_Of_Traps) := Make_Seeds (Nr_Total + Nr_Of_Traps);
   Finish : Boolean := False;


end Parameters;
