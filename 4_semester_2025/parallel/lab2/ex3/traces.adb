with Ada.Text_IO;               use Ada.Text_IO;
with Ada.Characters.Handling;    use Ada.Characters.Handling;
with Ada.Wide_Characters.Handling;
package body Traces is

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
         & (' ', Trace.Symbol)); -- To avoid ' ' issues
   end Print_Trace;

   procedure Print_Traces (Traces : Traces_Sequence_Type) is
   begin
      for I in 0 .. Traces.Last loop
         Print_Trace (Traces.Trace_Array (I));
      end loop;
   end Print_Traces;

end Traces;
