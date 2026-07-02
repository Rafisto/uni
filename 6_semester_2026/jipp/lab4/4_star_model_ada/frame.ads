with Ada.Strings.Unbounded;

package Frame is

   -- Like an ethernet frame.
   type FrameType is record
      From     : Integer;
      To       : Integer;
   end record;

end Frame;