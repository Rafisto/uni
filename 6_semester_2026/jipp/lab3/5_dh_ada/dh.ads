with Interfaces; use Interfaces;
with Ring;
with Libjpp;     use Libjpp;

generic
   N_Val : Unsigned_64;
   with package RingInstance is new Ring (N => N_Val);
package DH is
   subtype T is RingInstance.Value;

   package Setup is
      type DH_Setup is private;
      type DH_Setup_Access is access constant DH_Setup;

      function Initialize return DH_Setup;
      function Get_Generator (Self : DH_Setup) return T;
      function Power (Self : DH_Setup; A : T; B : Unsigned_64) return T;

   private
      type DH_Setup is record
         Generator : T;
      end record;
   end Setup;

   package External_User is
      type User (Domain : Setup.DH_Setup_Access) is tagged private;

      function Create_User (Domain : Setup.DH_Setup_Access) return User;

      function Get_Public_Key (Self : User) return T;
      procedure Set_Key (Self : in out User; A : T);
      function Encrypt (Self : User; M : T) return T;
      function Decrypt (Self : User; C : T) return T;

   private
      type User (Domain : Setup.DH_Setup_Access) is tagged record
         Secret  : Unsigned_64;
         Key     : T;
         Has_Key : Boolean := False;
      end record;
   end External_User;

end DH;