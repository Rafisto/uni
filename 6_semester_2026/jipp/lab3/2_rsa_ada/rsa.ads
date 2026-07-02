with Interfaces; use Interfaces;
with Ring; 
with Libjpp; use Libjpp;

generic
   N_Val : Unsigned_64;
   with package RingInstance is new Ring (N => N_Val);
package RSA is
   type RSASetup is tagged private;

   function Initialize(P : Unsigned_64; Q : Unsigned_64) return RSASetup;
   
   function GetPublicKey(Self : RSASetup) return RingInstance.Value;
   function Encrypt(Self : RSASetup; M : RingInstance.Value) return RingInstance.Value;
   function Decrypt(Self : RSASetup; C : RingInstance.Value) return RingInstance.Value;

private
   type RSASetup is tagged record
      E : RingInstance.Value;
      D : RingInstance.Value;
      M : Unsigned_64;
   end record;
end RSA;