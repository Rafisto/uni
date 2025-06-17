package body Printer is
   task body Printer is
   begin
      for I in 1 .. Nr_Of_Travelers + Nr_Of_Squatters loop
         accept Report (Traces : Traces_Sequence_Type) do
            Print_Traces (Traces);
         end Report;
      end loop;

      Finish := True;

      for I in 1 .. Nr_Of_Traps loop
         accept Report (Traces : Traces_Sequence_Type) do
            Print_Traces (Traces);
         end Report;
      end loop;
   end Printer;
end Printer;
