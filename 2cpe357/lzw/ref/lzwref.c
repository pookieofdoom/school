//LZWDecode Reference Code

LZWDecode (LZWExp *exp, Uint bits) {

UInt Code
Code entry

butakedata (&exp->bitunpacker  , &code?)

while(unpack(  ) ,  

   if(EODSeen || code > lastCode 
      return 0 , must be return badcode
      
   if(code == EOD )
      EodSeen = 1
      then do something? his code put return bad_code which can be wrong
   }

   entry = getcode (

    if(lastCode > EOD)
      setsuffix
      
   if(lastCode == ReycleCode) 
      reycle
      
    else {
      lastcode = extendcode
      numbits++
      maxcode <<1
   }
   
   freecode(dict,code);
   
   }
   return 0;





}