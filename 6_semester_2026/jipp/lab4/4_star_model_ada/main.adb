with Ada.Text_IO;
with Ada.Float_Text_IO;
with Ada.Numerics.Float_Random;
with Ada.Strings.Unbounded;

with Frame; use Frame;

procedure Main is
   NUsers         : constant := 100;
   NFrames        : constant := 100;
   BaseBackoff    : constant Duration := 0.002; -- 2ms
   MaxBackoff     : constant Duration := 2.000; -- 2s
   ProcessingTime : constant Duration := 0.001; -- 1ms
   ThinkTime      : constant Duration := 0.020; -- 20ms

   protected type User is
      procedure IncrementIngress;
      procedure IncrementFail;
      function GetIngressCount return Integer;
      function GetFailCount return Integer;
   private
      IngressCount : Integer := 0;
      FailCount    : Integer := 0;
   end User;

   protected body User is
      procedure IncrementIngress is
      begin
         IngressCount := IngressCount + 1;
      end IncrementIngress;

      procedure IncrementFail is
      begin
         FailCount := FailCount + 1;
      end IncrementFail;

      function GetIngressCount return Integer is
      begin
         return IngressCount;
      end GetIngressCount;

      function GetFailCount return Integer is
      begin
         return FailCount;
      end GetFailCount;
   end User;

   type UserArray is array (1 .. NUsers) of User;
   Users : UserArray;

   -- just an L2 switch, with no buffering though
   protected Switch is
      entry Lock;
      procedure Unlock;
      entry PutFrame (M : FrameType);
      entry TakeFrame (M : out FrameType; TerminateLoop : out Boolean);
      entry WaitForForward;
      procedure SignalForwardDone;
      procedure Stop;
   private
      Busy        : Boolean := False;
      HasFrame    : Boolean := False;
      Frame       : FrameType;
      ForwardDone : Boolean := False;
      ShouldStop  : Boolean := False;
   end Switch;

   protected body Switch is
      entry Lock when not Busy is
      begin
         Busy := True;
      end Lock;

      procedure Unlock is
      begin
         Busy := False;
      end Unlock;

      entry PutFrame (M : FrameType) when not HasFrame is
      begin
         Frame := M;
         HasFrame := True;
         ForwardDone := False;
      end PutFrame;

      entry TakeFrame (M : out FrameType; TerminateLoop : out Boolean)
        when HasFrame or ShouldStop
      is
      begin
         if ShouldStop and not HasFrame then
            TerminateLoop := True;
         else
            M := Frame;
            HasFrame := False;
            TerminateLoop := False;
         end if;
      end TakeFrame;

      entry WaitForForward when ForwardDone is
      begin
         null;
      end WaitForForward;

      procedure SignalForwardDone is
      begin
         ForwardDone := True;
      end SignalForwardDone;

      procedure Stop is
      begin
         ShouldStop := True;
      end Stop;
   end Switch;

   task SwitchTask;

   task body SwitchTask is
      CurrentFrame : FrameType;
      CheckDone    : Boolean;
   begin
      loop
         Switch.TakeFrame (CurrentFrame, CheckDone);
         exit when CheckDone;

         Ada.Text_IO.Put_Line
           ("Switch: Received Frame from User"
            & Integer'Image (CurrentFrame.From)
            & " destined for User"
            & Integer'Image (CurrentFrame.To)
            & ". Forwarding...");

         delay ProcessingTime;
         Users (CurrentFrame.To).IncrementIngress;

         Ada.Text_IO.Put_Line
           ("Switch: Successfully delivered Frame from User"
            & Integer'Image (CurrentFrame.From)
            & " to User"
            & Integer'Image (CurrentFrame.To)
            & ".");

         Switch.SignalForwardDone;
      end loop;
   end SwitchTask;

   task type UserWorker (Id : Integer);

   task body UserWorker is
      use Ada.Numerics.Float_Random;
      Gen         : Generator;
      TargetID    : Integer;
      Frame       : FrameType;
      Acquired    : Boolean;
      Attempt     : Integer;
      BackoffTime : Duration;
      WaitBackoff : Duration;
   begin
      Reset (Gen, Initiator => Id);

      delay Duration (Random (Gen) * Float (BaseBackoff));

      for I in 1 .. NFrames loop

         TargetID := Integer (Float'Floor (Random (Gen) * Float (NUsers))) + 1;
         if TargetID > NUsers then
            TargetID := NUsers;
         end if;

         Frame.From := Id;
         Frame.To := TargetID;

         Attempt := 1;

         loop
            select
               Switch.Lock;
               Acquired := True;
            else
               Acquired := False;
            end select;

            if Acquired then
               Ada.Text_IO.Put_Line
                 ("User(id"
                  & Integer'Image (Id)
                  & ") successfully acquired Switch Lock for transfer"
                  & Integer'Image (I)
                  & ".");
               exit;
            end if;

            Users (Id).IncrementFail;

            WaitBackoff := Duration (2 ** Attempt) * BaseBackoff;
            if WaitBackoff > MaxBackoff then
               WaitBackoff := MaxBackoff;
            end if;
            BackoffTime := Duration (Random (Gen) * Float (WaitBackoff));

            Ada.Text_IO.Put_Line
              ("User(id"
               & Integer'Image (Id)
               & ", transfer"
               & Integer'Image (I)
               & ") found switch busy. Backing off for"
               & Duration'Image (BackoffTime)
               & " seconds (attempt"
               & Integer'Image (Attempt)
               & ").");

            delay BackoffTime;

            if Attempt < 30 then
               Attempt := Attempt + 1;
            end if;
         end loop;

         Switch.PutFrame (Frame);
         Switch.WaitForForward;
         Switch.Unlock;

         delay Duration (Random (Gen) * Float (ThinkTime));
      end loop;

      Ada.Text_IO.Put_Line
        ("User(id"
         & Integer'Image (Id)
         & ") finished sending all"
         & Integer'Image (NFrames)
         & " Frames.");
   end UserWorker;

   TotalReceived : Integer := 0;
   TotalFailed   : Integer := 0;

begin
   Ada.Text_IO.Put_Line ("Star Topology Communication.");

   declare
      type WorkerAccess is access UserWorker;
      Workers : array (1 .. NUsers) of WorkerAccess;
   begin
      for I in 1 .. NUsers loop
         Workers (I) := new UserWorker (Id => I);
      end loop;
   end;

   Switch.Stop;

   Ada.Text_IO.New_Line;
   Ada.Text_IO.Put_Line ("Star Topology Communication finished.");
   for I in 1 .. NUsers loop
      declare
         Recv : constant Integer := Users (I).GetIngressCount;
         Fail : constant Integer := Users (I).GetFailCount;
      begin
         TotalFailed := TotalFailed + Fail;
         TotalReceived := TotalReceived + Recv;

         Ada.Text_IO.Put_Line
           ("User(id"
            & Integer'Image (I)
            & ") received"
            & Integer'Image (Recv)
            & " Frames ("
            & Integer'Image (Fail)
            & " failed attempts).");
      end;
   end loop;

   Ada.Text_IO.New_Line;
   Ada.Text_IO.Put_Line
     ("Total Frames sent across system: " & Integer'Image (NUsers * NFrames));
   Ada.Text_IO.Put_Line
     ("Total Frames verified delivered: " & Integer'Image (TotalReceived));
   Ada.Text_IO.Put_Line
     ("Total failed send attempts across all users: "
      & Integer'Image (TotalFailed));

end Main;
