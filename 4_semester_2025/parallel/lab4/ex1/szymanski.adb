with Ada.Text_IO;               use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Random_Seeds;              use Random_Seeds;
with Ada.Real_Time;             use Ada.Real_Time;

procedure Szymanski is

   -- Constants
   Nr_Of_Processes : constant := 15;
   Min_Steps       : constant := 50;
   Max_Steps       : constant := 100;
   Min_Delay       : constant Duration := 0.01;
   Max_Delay       : constant Duration := 0.05;

   -- Process states
   type Process_State is
     (Local_Section,
      Entry_Protocol_1,
      Entry_Protocol_2,
      Entry_Protocol_3,
      Entry_Protocol_4,
      Critical_Section,
      Exit_Protocol);

   -- Shared flags
   type Flag_Type is range 0 .. 4;
   Flags : array (0 .. Nr_Of_Processes - 1) of Flag_Type := (others => 0);

   -- Display board
   Board_Width  : constant := Nr_Of_Processes;
   Board_Height : constant := Process_State'Pos (Process_State'Last) + 1;

   -- Timing
   Start_Time : Time := Clock;

   -- Random seeds
   Seeds : Seed_Array_Type (1 .. Nr_Of_Processes) :=
     Make_Seeds (Nr_Of_Processes);

   -- Trace logging
   type Position_Type is record
      X : Integer range 0 .. Board_Width - 1;
      Y : Integer range 0 .. Board_Height - 1;
   end record;

   type Trace_Type is record
      Time_Stamp : Duration;
      Id         : Integer;
      Position   : Position_Type;
      Symbol     : Character;
   end record;

   type Trace_Array_Type is array (Natural range <>) of Trace_Type;
   subtype Max_Trace_Index is Natural range 0 .. Max_Steps;
   type Traces_Sequence_Type is record
      Last        : Integer := -1;
      Trace_Array : Trace_Array_Type (Max_Trace_Index);
   end record;

   procedure Print_Trace (Trace : Trace_Type) is
   begin
      Put_Line
        (Duration'Image (Trace.Time_Stamp)
         & " "
         & Integer'Image (Trace.Id)
         & " "
         & Integer'Image (Trace.Position.X)
         & " "
         & Integer'Image (Trace.Position.Y)
         & " "
         & Trace.Symbol);
   end Print_Trace;

   procedure Print_Traces (Traces : Traces_Sequence_Type) is
   begin
      for I in 0 .. Traces.Last loop
         Print_Trace (Traces.Trace_Array (I));
      end loop;
   end Print_Traces;

   -- Printer task
   task Printer is
      entry Report (Traces : Traces_Sequence_Type);
   end Printer;

   task body Printer is
   begin
      for I in 1 .. Nr_Of_Processes loop
         accept Report (Traces : Traces_Sequence_Type) do
            Print_Traces (Traces);
         end Report;
      end loop;

      -- Print metadata line
      Put
        ("-1 "
         & Integer'Image (Nr_Of_Processes)
         & " "
         & Integer'Image (Board_Width)
         & " "
         & Integer'Image (Board_Height)
         & " ");
      for State in Process_State'Range loop
         Put (State'Image & ";");
      end loop;
      Put_Line ("EXTRA_LABEL;");
   end Printer;

   -- Process task definition
   type Process_Type is record
      Id       : Integer;
      Symbol   : Character;
      Position : Position_Type;
   end record;

   task type Process_Task_Type is
      entry Init (Id : Integer; Seed : Integer; Symbol : Character);
      entry Start;
   end Process_Task_Type;

   task body Process_Task_Type is
      G           : Generator;
      Process     : Process_Type;
      Time_Stamp  : Duration;
      Nr_Of_Steps : Integer;
      Traces      : Traces_Sequence_Type;

      procedure Store_Trace is
      begin
         Traces.Last := Traces.Last + 1;
         Traces.Trace_Array (Traces.Last) :=
           (Time_Stamp => Time_Stamp,
            Id         => Process.Id,
            Position   => Process.Position,
            Symbol     => Process.Symbol);
      end Store_Trace;

      procedure Change_State (State : Process_State) is
      begin
         Time_Stamp := To_Duration (Clock - Start_Time);
         Process.Position.Y := Process_State'Pos (State);
         Store_Trace;
      end Change_State;

      function Uniform_Duration return Duration is
      begin
         return Min_Delay + (Max_Delay - Min_Delay) * Duration (Random (G));
      end Uniform_Duration;

   begin
      accept Init (Id : Integer; Seed : Integer; Symbol : Character) do
         Reset (G, Seed);
         Process.Id := Id;
         Process.Symbol := Symbol;
         Process.Position := (X => Id, Y => Process_State'Pos (Local_Section));
         Nr_Of_Steps :=
           Min_Steps + Integer (Float (Max_Steps - Min_Steps) * Random (G));
         Time_Stamp := To_Duration (Clock - Start_Time);
         Store_Trace;
      end Init;

      accept Start;

      for Step in 1 .. Nr_Of_Steps / 7 loop
         delay Uniform_Duration;

         -- ENTRY_PROTOCOL_1
         Change_State (Entry_Protocol_1);
         Flags (Process.Id) := 1;

         loop
            exit when (for all I in Flags'Range => Flags (I) <= 2);
         end loop;

         -- ENTRY_PROTOCOL_2
         Flags (Process.Id) := 3;
         Change_State (Entry_Protocol_2);

         for I in Flags'Range loop
            if Flags (I) = 1 then
               Flags (Process.Id) := 2;
               Change_State (Entry_Protocol_3);

               declare
                  Found_Flag_4 : Boolean := False;
               begin
                  for I in Flags'Range loop
                     if Flags (I) = 4 then
                        Found_Flag_4 := True;
                        exit;
                     end if;
                  end loop;
                  exit when Found_Flag_4;
               end;
               exit;
            end if;
         end loop;

         -- ENTRY_PROTOCOL_4
         Flags (Process.Id) := 4;
         Change_State (Entry_Protocol_4);

         if Process.Id > 0 then
            loop
               exit when (for all I in 0 .. Process.Id - 1 => Flags (I) <= 1);
            end loop;
         end if;

         -- CRITICAL_SECTION
         Change_State (Critical_Section);
         delay Uniform_Duration;

         -- EXIT_PROTOCOL
         Change_State (Exit_Protocol);
         loop
            exit when
              (for all I in Process.Id + 1 .. Nr_Of_Processes - 1
               => Flags (I) /= 2 and then Flags (I) /= 3);
         end loop;

         Flags (Process.Id) := 0;
         Change_State (Local_Section);
      end loop;

      Printer.Report (Traces);
   end Process_Task_Type;

   Process_Tasks : array (0 .. Nr_Of_Processes - 1) of Process_Task_Type;
   Symbol        : Character := 'A';

begin
   for I in Process_Tasks'Range loop
      Process_Tasks (I).Init (I, Seeds (I + 1), Symbol);
      Symbol := Character'Succ (Symbol);
   end loop;

   for I in Process_Tasks'Range loop
      Process_Tasks (I).Start;
   end loop;
end Szymanski;
