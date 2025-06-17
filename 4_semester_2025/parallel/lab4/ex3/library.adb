with Ada.Text_IO;               use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Random_Seeds;              use Random_Seeds;
with Ada.Real_Time;             use Ada.Real_Time;
with RW_Monitor;                use RW_Monitor;

procedure Library is
   Nr_Of_Readers   : constant Integer := 10;
   Nr_Of_Writers   : constant Integer := 5;
   Nr_Of_Processes : constant Integer := Nr_Of_Readers + Nr_Of_Writers;

   Min_Steps : constant Integer := 50;
   Max_Steps : constant Integer := 100;

   Min_Delay : constant Duration := 0.01;
   Max_Delay : constant Duration := 0.05;

   type Process_Kind is (Reader, Writer);
   type Process_State is (Local_Section, Start, Reading_Room, Stop);

   Board_Width  : constant Integer := Nr_Of_Processes;
   Board_Height : constant Integer :=
     Process_State'Pos (Process_State'Last) + 1;

   Start_Time : Time := Clock;
   Seeds      : Seed_Array_Type (1 .. Nr_Of_Processes) :=
     Make_Seeds (Nr_Of_Processes);

   -- Trace types
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

   Max_Steps_Trace : constant Integer := Max_Steps;
   type Trace_Array_Type is array (0 .. Max_Steps_Trace) of Trace_Type;
   type Traces_Sequence_Type is record
      Last        : Integer := -1;
      Trace_Array : Trace_Array_Type;
   end record;

   procedure Print_Trace (Trace : Trace_Type) is
      Symbol : String := (' ', Trace.Symbol);
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
         & (' ', Trace.Symbol) -- print as string to avoid: '
        );
   end Print_Trace;

   procedure Print_Traces (Traces : Traces_Sequence_Type) is
   begin
      for I in 0 .. Traces.Last loop
         Print_Trace (Traces.Trace_Array (I));
      end loop;
   end Print_Traces;

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

      Put
        ("-1 "
         & Integer'Image (Nr_Of_Processes)
         & " "
         & Integer'Image (Board_Width)
         & " "
         & Integer'Image (Board_Height)
         & " ");
      for I in Process_State'Range loop
         Put (I'Image & ";");
      end loop;
      Put_Line ("EXTRA_LABEL;");
   end Printer;

   type Process_Type is record
      Id       : Integer;
      Symbol   : Character;
      Position : Position_Type;
   end record;

   task type Process_Task_Type is
      entry Init (Id : Integer; K : Process_Kind; Seed : Integer);
      entry Start;
   end Process_Task_Type;

   task body Process_Task_Type is
      G          : Generator;
      Trace_Buf  : Traces_Sequence_Type;
      Proc       : Process_Type :=
        (Id => 0, Symbol => ' ', Position => (X => 0, Y => 0));
      Kind       : Process_Kind;
      Steps      : Integer;
      TS         : Duration;
      Seed_Value : Integer;

      procedure Record_Trace is
      begin
         Trace_Buf.Last := Trace_Buf.Last + 1;
         Trace_Buf.Trace_Array (Trace_Buf.Last) :=
           (Time_Stamp => TS,
            Id         => Proc.Id,
            Position   => Proc.Position,
            Symbol     => Proc.Symbol);
      end Record_Trace;

      procedure State_Change (New_State : Process_State) is
      begin
         TS := To_Duration (Clock - Start_Time);
         Proc.Position.Y := Process_State'Pos (New_State);
         Record_Trace;
      end State_Change;

   begin
      accept Init (Id : Integer; K : Process_Kind; Seed : Integer) do
         Proc.Id := Id;
         Kind := K;
         Seed_Value := Seed;
      end Init;

      Reset (G, Seed_Value);
      Proc.Symbol := (if Kind = Reader then 'R' else 'W');
      Proc.Position := (X => Proc.Id, Y => Process_State'Pos (Local_Section));
      Steps :=
        Min_Steps + Integer (Float (Max_Steps - Min_Steps) * Random (G));
      TS := To_Duration (Clock - Start_Time);
      Record_Trace;

      accept Start do
         null;
      end Start;

      for Step in 0 .. Steps / 4 - 1 loop
         -- LOCAL_SECTION - start
         delay Min_Delay + (Max_Delay - Min_Delay) * Duration (Random (G));
         -- LOCAL_SECTION - end

         State_Change (Start);
         if Kind = Reader then
            Start_Read;
         else
            Start_Write;
         end if;

         State_Change (Reading_Room);

         -- CRITICAL_SECTION - start
         delay Min_Delay + (Max_Delay - Min_Delay) * Duration (Random (G));
         -- CRITICAL_SECTION - end

         State_Change (Stop);
         if Kind = Reader then
            Stop_Read;
         else
            Stop_Write;
         end if;

         State_Change (Local_Section);
      end loop;

      Printer.Report (Traces => Trace_Buf);
   end Process_Task_Type;

   Reader_Tasks : array (0 .. Nr_Of_Readers - 1) of Process_Task_Type;
   Writer_Tasks : array (0 .. Nr_Of_Writers - 1) of Process_Task_Type;

begin
   for I in Reader_Tasks'Range loop
      Reader_Tasks (I).Init (Id => I, K => Reader, Seed => Seeds (I + 1));
   end loop;

   for I in Writer_Tasks'Range loop
      Writer_Tasks (I).Init
        (Id   => I + Nr_Of_Readers,
         K    => Writer,
         Seed => Seeds (I + Nr_Of_Readers + 1));
   end loop;

   for I in Reader_Tasks'Range loop
      Reader_Tasks (I).Start;
   end loop;

   for I in Writer_Tasks'Range loop
      Writer_Tasks (I).Start;
   end loop;
end Library;
