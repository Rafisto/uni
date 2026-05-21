with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Ada.Text_IO;               use Ada.Text_IO;

procedure Main is
   NPhilosophers  : constant := 100;
   NIterations    : constant := 100;
   MaxEatingTime : constant := 0.010; -- 10 ms

   protected type WaitGroup is
      procedure Increment;
      entry Wait;
   private
      Count : Integer := 0;
   end WaitGroup;

   protected body WaitGroup is
      procedure Increment is
      begin
         Count := Count + 1;
      end Increment;

      entry Wait when Count = NPhilosophers is
      begin
         null;
      end Wait;
   end WaitGroup;

   Counter : WaitGroup;

   protected type Fork is
      entry Acquire;
      procedure TryAcquire (Success : out Boolean);
      procedure Release;
   private
      Taken : Boolean := False;
   end Fork;

   protected body Fork is
      entry Acquire when not Taken is
      begin
         Taken := True;
      end Acquire;

      procedure TryAcquire (Success : out Boolean) is
      begin
         if not Taken then
            Taken := True;
            Success := True;
         else
            Success := False;
         end if;
      end TryAcquire;

      procedure Release is
      begin
         Taken := False;
      end Release;
   end Fork;

   Forks : array (1 .. NPhilosophers) of Fork;

   task type Philosopher (ID, ForkLeft, ForkRight : Integer) is
      entry GetFailures (Count : out Integer);
   end Philosopher;

   type PhilosopherAccess is access Philosopher;

   task body Philosopher is
      G             : Generator;
      RandomTime   : Float;
      RightSuccess : Boolean;
      Failures      : Integer := 0;
   begin
      Reset (G);
      for i in 1 .. NIterations loop
         RandomTime := Random (G) * MaxEatingTime;
         Put_Line
           ("Philosopher(id"
            & Integer'Image (ID)
            & ", meal"
            & Integer'Image (i)
            & ") thinks for"
            & Float'Image (RandomTime)
            & " sec.");
         delay Duration (RandomTime);

         loop
            Forks (ForkLeft).Acquire;
            Forks (ForkRight).TryAcquire (RightSuccess);

            if RightSuccess then
               exit;
            else
               Forks (ForkLeft).Release;

               Put_Line
                 ("Philosopher(id"
                  & Integer'Image (ID)
                  & ", meal"
                  & Integer'Image (i)
                  & ") failed to pick up forks.");
               Failures := Failures + 1;

               RandomTime := Random (G) * MaxEatingTime;
               delay Duration (RandomTime);
            end if;
         end loop;

         RandomTime := Random (G) * MaxEatingTime;
         Put_Line
           ("Philosopher(id"
            & Integer'Image (ID)
            & ", meal"
            & Integer'Image (i)
            & ") eats for"
            & Float'Image (RandomTime)
            & " sec.");
         delay Duration (RandomTime);

         Forks (ForkRight).Release;
         Forks (ForkLeft).Release;
      end loop;

      Counter.Increment;
      Put_Line
        ("Philosopher(id"
         & Integer'Image (ID)
         & ") finished with"
         & Integer'Image (Failures)
         & " failures.");

      accept GetFailures (Count : out Integer) do
         Count := Failures;
      end GetFailures;
   end Philosopher;

   Philosophers         : array (1 .. NPhilosophers) of PhilosopherAccess;
   TotalFailures       : Integer := 0;
   PhilosopherFailures : Integer;

begin
   Put_Line ("Dining Philosophers Problem");

   for I in 1 .. NPhilosophers loop
      Philosophers (I) := new Philosopher (I, I, (I mod NPhilosophers) + 1);
   end loop;

   Counter.Wait;

   Put_Line ("Philosophers have concluded the feast.");
   for I in 1 .. NPhilosophers loop
      Philosophers (I).GetFailures (PhilosopherFailures);
      TotalFailures := TotalFailures + PhilosopherFailures;
      Put_Line
        ("Philosopher(id"
         & Integer'Image (I)
         & ") had"
         & Integer'Image (PhilosopherFailures)
         & " failures.");
   end loop;

   Put_Line ("Total failures: " & Integer'Image (TotalFailures));
end Main;
