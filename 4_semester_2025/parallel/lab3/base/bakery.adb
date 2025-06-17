with Text_IO; use Text_IO;

procedure Bakery is
   pragma Time_Slice (0.01);
   type Node_Count is range 0 .. 15;
   subtype Node_ID is Node_Count range 1 .. Node_Count'Last;
   Choosing : array (Node_ID) of Integer range 0 .. 1 := (others => 0);
   Number   : array (Node_ID) of Integer := (others => 0);
   pragma Volatile (Choosing);
   pragma Volatile (Number);

   task type Nodes is
      entry Init (ID : Node_ID);
   end Nodes;
   Node : array (Node_ID) of Nodes;

   function Max return Integer is
      Current : Integer := 0;
   begin
      for N in Number'Range loop
         if Number (N) > Current then
            Current := Number (N);
         end if;
      end loop;
      return Current;
   end Max;

   task body Nodes is
      I : Node_ID;
   begin
      accept Init (ID : Node_ID) do
         I := ID;
      end Init;
      for M in 1 .. 5 loop
         -- Sekcja_lokalna_I;
         Choosing (I) := 1;
         Number (I) := 1 + Max;
         Choosing (I) := 0;
         for J in Node_ID loop
            if J /= I then
               loop
                  exit when Choosing (J) = 0;
               end loop;

               loop
                  exit when
                    (Number (J) = 0)
                    or (Number (I) < Number (J))
                    or (Number (I) = Number (J) and I < J);
               end loop;
            end if;
         end loop;
         -- Sekcja_krytyczna_I;
         Put_Line
           ("Node " & Node_Count'Image (I) & " is in the critical section");
         delay 0.01;
         -- Sekcja_wyjscia_I;
         Number (I) := 0;
      end loop;
   end Nodes;
begin
   -- Bakery
   for J in Node_ID loop
      Node (J).Init (J);
   end loop;
end Bakery;
