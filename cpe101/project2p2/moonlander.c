/* Project 2
*
* Name(s): Anthony Dinh
* Instructor: Hatalsky
*/


#include "landerFuncs.h"
#include <stdio.h>
#define GRAVITY 1.62

int main()
{
   int fuelAmount, fuelRate, i;
   double velocity = 0.0, accel=0.0, alt=0.0;
   showWelcome();
   alt = getAltitude();
   fuelAmount = getFuel();
   printf("\nLM state at retrorocket cutoff\n");
   displayLMState(0, alt, velocity, fuelAmount, 0);
   printf("\n");
   fuelRate = getFuelRate(fuelAmount);
   accel = updateAcceleration(GRAVITY, fuelRate);
   alt = updateAltitude(alt,  velocity,  accel);
   velocity = updateVelocity (velocity, accel);
      for (i=1; alt > 0.0; i++)
      {
	    
         if (fuelRate == fuelAmount)
         {         
            
            printf("OUT OF FUEL - Elapsed Time: %3d Altitude: %7.2f Velocity: %7.2f\n", i, alt, velocity);
			        
            fuelRate = 0.0;
	    fuelAmount = 0.0;
			       
	  }
         else
         {
	        fuelAmount = updateFuel(fuelAmount,fuelRate);
	        displayLMState(i, alt, velocity, fuelAmount, fuelRate);
	        printf("\n");
	        fuelRate = getFuelRate(fuelAmount);
	 }
	 accel = updateAcceleration(GRAVITY, fuelRate);
       	 alt = updateAltitude(alt,  velocity,  accel);
	 velocity = updateVelocity (velocity, accel);
		
      }
   fuelAmount = updateFuel(fuelAmount,fuelRate);	  
   printf("\nLM state at landing/impact\n");
   displayLMState(i, alt, velocity, fuelAmount, fuelRate);
   printf("\n");
   displayLMLandingStatus(velocity);
   
   return 0;
      
}
