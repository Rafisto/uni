with Ada.Text_IO;               use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Ada.Real_Time;             use Ada.Real_Time;

with Ada.Wide_Characters.Handling;
with Ada.Characters.Handling; use Ada.Characters.Handling;

with Parameters; use Parameters;
with Random_Seeds; use Random_Seeds;
with Position;     use Position;
with Traces;       use Traces;
with Printer;       use Printer;

procedure Travelers is
   -- Travelers
   type Traveler_Variant is (Basic, Squatter, None);

   type Traveler_Type is record
      Id       : Integer;
      Symbol   : Character;
      Position : Position_Type;
   end record;

   -- Task
   task type Traveler_Task_Type is
      entry Init (Id : Integer; Seed : Integer; Symbol : Character);
      entry Start;
   end Traveler_Task_Type;

   task type Squatter_Task_Type is
      entry Init (Id : Integer; Seed : Integer; Symbol : Character);
      entry Start;
      entry Evict (New_Position : Position_Type);
   end Squatter_Task_Type;

   type All_Traveler_Task_Type (Variant : Traveler_Variant) is record
      case Variant is
         when Basic =>
            Traveler_Task : Traveler_Task_Type;

         when Squatter =>
            Squatter_Task : Squatter_Task_Type;

         when None =>
            null; -- no task
      end case;
   end record;

   protected type Field is
      entry Init (New_Position : Position_Type);
      entry Enter
        (New_Traveler : access All_Traveler_Task_Type; Success : out Boolean);
      entry Move (New_Position : Position_Type; Success : out Boolean);
      entry Leave;
   private
      Initialized : Boolean := False;
      Traveler    : access All_Traveler_Task_Type;
      Position    : Position_Type;
   end Field;

   -- Global Objects
   Board        :
     array (0 .. (Board_Width - 1), 0 .. (Board_Height - 1)) of Field;
   Travel_Tasks : array (0 .. Nr_Total - 1) of access All_Traveler_Task_Type;
   Null_Task    : access All_Traveler_Task_Type :=
     new All_Traveler_Task_Type (Variant => None);

   -- Tasks
   protected body Field is
      entry Init (New_Position : Position_Type) when not Initialized is
      begin
         Position := New_Position;
         Traveler := Null_Task;
         Initialized := True;
      end Init;

      entry Enter
        (New_Traveler : access All_Traveler_Task_Type; Success : out Boolean)
        when Initialized and Traveler.Variant /= Basic
      is
      begin
         if Traveler.Variant = None then
            Traveler := New_Traveler;
            Success := True;
         elsif Traveler.Variant = Squatter and New_Traveler.Variant = Basic
         then
            declare
               New_Position : Position_Type;
            begin
               for N in 0 .. 3 loop
                  New_Position := Position;
                  Move_Direction (New_Position, N);
                  select
                     Board (New_Position.X, New_Position.Y).Enter
                       (Traveler, Success);
                     if Success then
                        exit;
                     end if;
                  else
                     Success := False;
                  end select;
               end loop;

               if Success then
                  Traveler.Squatter_Task.Evict (New_Position);
                  Traveler := New_Traveler;
               end if;
            end;
         else
            Success := False;
         end if;
      end Enter;

      entry Move (New_Position : Position_Type; Success : out Boolean)
        when Initialized and Traveler.Variant = Basic
      is
      begin
         Board (New_Position.X, New_Position.Y).Enter (Traveler, Success);

         if Success then
            Traveler := Null_Task;
         end if;
      end Move;

      entry Leave when Initialized is
      begin
         Traveler := Null_Task;
      end Leave;
   end Field;

   task body Traveler_Task_Type is
      G           : Generator;
      Traveler    : Traveler_Type;
      Time_Stamp  : Duration;
      Nr_of_Steps : Integer;
      Traces      : Traces_Sequence_Type;

      procedure Store_Trace is
      begin
         Traces.Last := Traces.Last + 1;
         Traces.Trace_Array (Traces.Last) :=
           (Time_Stamp => Time_Stamp,
            Id         => Traveler.Id,
            Position   => Traveler.Position,
            Symbol     => Traveler.Symbol);
      end Store_Trace;

      procedure Make_Step (Position : in out Position_Type) is
         N : Integer;
      begin
         N := Integer (Float'Floor (4.0 * Random (G)));
         Move_Direction (Position, N);
      end Make_Step;

      New_Position : Position_Type;
      Success      : Boolean;
      Deadlock     : Boolean;

   begin
      accept Init (Id : Integer; Seed : Integer; Symbol : Character) do
         Reset (G, Seed);
         Nr_of_Steps :=
           Min_Steps + Integer (Float (Max_Steps - Min_Steps) * Random (G));
         Traveler.Id := Id;
         Traveler.Symbol := Symbol;

         Success := False;
         while not Success loop
            Traveler.Position :=
              (X => Integer (Float'Floor (Float (Board_Width) * Random (G))),
               Y => Integer (Float'Floor (Float (Board_Height) * Random (G))));
            select
               Board (Traveler.Position.X, Traveler.Position.Y).Enter
                 (Travel_Tasks (Traveler.Id), Success);
            else
               null;
            end select;
         end loop;
         Time_Stamp := To_Duration (Clock - Start_Time);
         Store_Trace;
      end Init;

      accept Start do
         null;
      end Start;

      Deadlock := False;
      for Step in 0 .. Nr_of_Steps loop
         delay Min_Delay + (Max_Delay - Min_Delay) * Duration (Random (G));

         -- move
         Success := False;
         Deadlock := False;
         while not Success loop
            New_Position := Traveler.Position;
            Make_Step (New_Position);
            select
               Board (New_Position.X, New_Position.Y).Enter
                 (Travel_Tasks (Traveler.Id), Success);
            or
               delay 6 * Max_Delay;
               Deadlock := True;
               exit;
            end select;
         end loop;

         if Deadlock then
            Traveler.Symbol := To_Lower (Traveler.Symbol);
            Time_Stamp := To_Duration (Clock - Start_Time);
            Store_Trace;
            exit;
         else
            Board (Traveler.Position.X, Traveler.Position.Y).Leave;
            Traveler.Position := New_Position;
            Time_Stamp := To_Duration (Clock - Start_Time);
            Store_Trace;
         end if;
      end loop;

      Printer.Printer.Report (Traces);
   end Traveler_Task_Type;

   task body Squatter_Task_Type is
      G              : Generator;
      Traveler       : Traveler_Type;
      Time_Stamp     : Duration;
      Traces         : Traces_Sequence_Type;
      Time_Begin    : Duration;
      Time_End : Duration;

      procedure Store_Trace is
      begin
         Traces.Last := Traces.Last + 1;
         Traces.Trace_Array (Traces.Last) :=
           (Time_Stamp => Time_Stamp,
            Id         => Traveler.Id,
            Position   => Traveler.Position,
            Symbol     => Traveler.Symbol);
      end Store_Trace;

      Success : Boolean;
   begin
      accept Init (Id : Integer; Seed : Integer; Symbol : Character) do
         Reset (G, Seed);
         Traveler.Id := Id;
         Traveler.Symbol := Symbol;
         Time_Begin := 10 * Max_Delay * Duration (Random (G));
         Time_End := Time_Begin + (Max_Delay * Max_Steps - Time_Begin) * Duration (Random (G));
      end Init;

      accept Start do
         null;
      end Start;

      delay Time_Begin;
      Success := False;

      while not Success loop
         Traveler.Position :=
           (X => Integer (Float'Floor (Float (Board_Width) * Random (G))),
            Y => Integer (Float'Floor (Float (Board_Height) * Random (G))));
         select
            Board (Traveler.Position.X, Traveler.Position.Y).Enter
              (Travel_Tasks (Traveler.Id), Success);
         else
            null;
         end select;
      end loop;

      Time_Stamp := To_Duration (Clock - Start_Time);
      Store_Trace;

      loop
         select
            accept Evict (New_Position : Position_Type) do
               Traveler.Position := New_Position;
               Time_Stamp := To_Duration (Clock - Start_Time);
               Store_Trace;
            end Evict;
         or
            delay Max_Delay;
            if To_Duration (Clock - Start_Time) >= Time_End then
               Board (Traveler.Position.X, Traveler.Position.Y).Leave;
               Traveler.Position := (X => Board_Width, Y => Board_Height);
               Time_Stamp := To_Duration (Clock - Start_Time);
               Store_Trace;
               exit;
            end if;
         end select;
      end loop;

      Printer.Printer.Report (Traces);
   end Squatter_Task_Type;

   -- Main
   Symbol : Character;
   Id     : Integer;
begin
   Put_Line
     ("-1 "
      & Integer'Image (Nr_Total)
      & " "
      & Integer'Image (Board_Width)
      & " "
      & Integer'Image (Board_Height));

   for I in 0 .. Board_Width - 1 loop
      for J in 0 .. Board_Height - 1 loop
         Board (I, J).Init ((X => I, Y => J));
      end loop;
   end loop;

   Id := 0;
   Symbol := 'A';
   for I in 0 .. Nr_Of_Travelers - 1 loop
      Travel_Tasks (Id) := new All_Traveler_Task_Type (Variant => Basic);
      Travel_Tasks (Id).Traveler_Task.Init (Id, Seeds (Id + 1), Symbol);
      Symbol := Character'Succ (Symbol);
      Id := Id + 1;
   end loop;

   Symbol := '0';
   for I in 0 .. Nr_Of_Squatters - 1 loop
      Travel_Tasks (Id) := new All_Traveler_Task_Type (Variant => Squatter);
      Travel_Tasks (Id).Squatter_Task.Init (Id, Seeds (Id + 1), Symbol);
      Symbol := Character'Succ (Symbol);
      Id := Id + 1;
   end loop;

   Id := 0;
   for I in 0 .. Nr_Of_Travelers - 1 loop
      Travel_Tasks (Id).Traveler_Task.Start;
      Id := Id + 1;
   end loop;

   for I in 0 .. Nr_Of_Squatters - 1 loop
      Travel_Tasks (Id).Squatter_Task.Start;
      Id := Id + 1;
   end loop;

end Travelers;
