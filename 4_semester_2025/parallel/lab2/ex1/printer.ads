with Parameters; use Parameters;
with Traces; use Traces;

package Printer is
   task Printer is
      entry Report (Traces : Traces_Sequence_Type);
   end Printer;
end Printer;