with Ada.Real_Time; use Ada.Real_Time;

with Position; use Position;

package Traces is

   type Trace_Type is record
      Time_Stamp : Duration;
      Id         : Integer;
      Position   : Position_Type;
      Symbol     : Character;
   end record;

   type Trace_Array_Type is array (Natural range <>) of Trace_Type;

   type Traces_Sequence_Type is record
      Last        : Integer := -1;
      Trace_Array :
        Trace_Array_Type (0 .. 100);  -- You can adjust 100 if needed
   end record;

   procedure Print_Trace (Trace : Trace_Type);
   procedure Print_Traces (Traces : Traces_Sequence_Type);

end Traces;
