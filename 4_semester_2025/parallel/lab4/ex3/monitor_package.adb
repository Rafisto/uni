-- Copyright (C) 2006 M. Ben-Ari. See copyright.txt

package body Monitor_Package is

   task body Monitor is
   begin
      loop
         select
            accept Enter;
         or
            terminate;
         end select;

         select
            accept Leave;
         or
            terminate;
         end select;
      end loop;
   end Monitor;

   task body Condition is
      My_Count : Integer := 0;
   begin
      loop
         select
            when My_Count = 0
            =>accept Signal do
               Monitor.Leave;
            end Signal;
         or
            accept Pre_Wait do
               My_Count := My_Count + 1;
            end Pre_Wait;
         or
            accept Wait do
               loop
                  select
                     accept Signal;
                     My_Count := My_Count - 1;
                     exit;
                  or
                     accept Waiting (B : out Boolean) do
                        B := True;
                     end Waiting;
                  or
                     accept Pre_Wait do
                        My_Count := My_Count + 1;
                     end Pre_Wait;
                  or
                     terminate;
                  end select;
               end loop;
            end Wait;
         or
            accept Waiting (B : out Boolean) do
               B := My_Count /= 0;
            end Waiting;
         or
            terminate;
         end select;
      end loop;
   end Condition;

   function Non_Empty (C : Condition) return Boolean is
      B : Boolean;
   begin
      C.Waiting (B);
      return B;
   end Non_Empty;

   procedure Wait (C : in out Condition) is
   begin
      C.Pre_Wait;
      Monitor.Leave;
      C.Wait;
   end Wait;

end Monitor_Package;
