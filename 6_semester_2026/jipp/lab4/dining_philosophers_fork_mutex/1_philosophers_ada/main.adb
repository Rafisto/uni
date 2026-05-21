with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Ada.Text_IO;               use Ada.Text_IO;

procedure Main is
   N_Philosophers  : constant := 100;
   N_Iterations    : constant := 100;
   Time_Constraint : constant := 0.01;

   protected type CountFinished is
      procedure Increment;
      function Get_Count return Integer;
      entry Wait;
   private
      Count : Integer := 0;
   end CountFinished;

   protected body CountFinished is
      procedure Increment is
      begin
         Count := Count + 1;
      end Increment;

      function Get_Count return Integer is
      begin
         return Count;
      end Get_Count;

      entry Wait when Count = N_Philosophers is
      begin
         null;
      end Wait;
   end CountFinished;

   Counter : CountFinished;

   protected type Fork is
      entry Lock;
      procedure Try_Lock (Success : out Boolean);
      procedure Unlock;
   private
      Taken : Boolean := False;
   end Fork;

   protected body Fork is
      entry Lock when not Taken is
      begin
         Taken := True;
      end Lock;

      procedure Try_Lock (Success : out Boolean) is
      begin
         if not Taken then
            Taken   := True;
            Success := True;
         else
            Success := False;
         end if;
      end Try_Lock;

      procedure Unlock is
      begin
         Taken := False;
      end Unlock;
   end Fork;

   Forks : array (1 .. N_Philosophers) of Fork;

   task type Philosopher (ID, ForkLeft, ForkRight : Integer) is
      entry Get_Failures (Count : out Integer);
   end Philosopher;

   type Philosopher_Access is access Philosopher;

   task body Philosopher is
      G             : Generator;
      Random_Time   : Float;
      Right_Success : Boolean;
      Failures      : Integer := 0;
   begin
      Reset (G);
      for i in 1 .. N_Iterations loop
         Random_Time := Random (G) * Time_Constraint;
         Put_Line("Philosopher(id" & Integer'Image (ID) & ", meal" & Integer'Image(i) & ") thinks for" & Float'Image (Random_Time) & " sec.");
         delay Duration (Random_Time);

         loop
            Forks(ForkLeft).Lock;

            Forks(ForkRight).Try_Lock(Right_Success);

            if Right_Success then
               exit; 
            else
               Forks(ForkLeft).Unlock;

               Put_Line("Philosopher(id" & Integer'Image (ID) & ", meal" & Integer'Image(i) & ") failed to pick up forks.");
               Failures := Failures + 1;
               
               Random_Time := Random (G) * Time_Constraint;
               delay Duration (Random_Time);
            end if;
         end loop;

         Random_Time := Random (G) * Time_Constraint;
         Put_Line("Philosopher(id" & Integer'Image (ID) & ", meal" & Integer'Image(i) & ") eats for" & Float'Image (Random_Time) & " sec.");
         delay Duration (Random_Time);

         Forks(ForkRight).Unlock;
         Forks(ForkLeft).Unlock;
      end loop;

      Counter.Increment;
      Put_Line("Philosopher(id" & Integer'Image (ID) & ") finished with" & Integer'Image (Failures) & " failures.");

      accept Get_Failures (Count : out Integer) do
         Count := Failures;
      end Get_Failures;
   end Philosopher;

   Philosophers         : array (1 .. N_Philosophers) of Philosopher_Access;
   Total_Failures       : Integer := 0;
   Philosopher_Failures : Integer;

begin
   Put_Line ("Dining Philosophers Problem");

   for I in 1 .. N_Philosophers loop
      Philosophers (I) := new Philosopher (I, I, (I mod N_Philosophers) + 1);
   end loop;

   Counter.Wait;

   Put_Line("Philosophers have concluded the feast.");
   for I in 1 .. N_Philosophers loop
      Philosophers (I).Get_Failures (Philosopher_Failures);
      Total_Failures := Total_Failures + Philosopher_Failures;
      Put_Line ("Philosopher(id" & Integer'Image (I) & ") had" & Integer'Image (Philosopher_Failures) & " failures.");
   end loop;

   Put_Line ("Total failures: " & Integer'Image (Total_Failures));
end Main;