/* Project 2
*
* Name: Anthony Dinh
* Instructor: Hatalsky
*/
#include <stdio.h>

void showWelcome()
{
   printf("\nWelcome aboard the Lunar Module Flight Simulator\n");
   printf("\n   To begin you must specify the LM's initial altitude\n");
   printf("   and fuel level.  To simulate the actual LM use\n");
   printf("   values of 1300 meters and 500 liters, respectively.\n");
   printf("\n   Good luck and may the force be with you!\n\n");
}

int getFuel()
{
   int fuel;
   printf("Enter the initial amount of fuel on board the LM (in liters): ");
   scanf("%d", &fuel);
   while (fuel <= 0)
   {
      printf("ERROR: Amount of fuel must be positive, please try again\n");
	  printf("Enter the initial amount of fuel on board the LM (in liters): ");
      scanf("%d", &fuel);
   }
   return fuel;
}

int getAltitude ()
{
   int alt;
   printf("Enter the initial altitude of the LM (in meters): ");
   scanf("%d", &alt);
   while (alt < 1 || alt > 9999)
   {
      printf("ERROR: Altitude must be between 1 and 9999, inclusive, please try again\n");
	  printf("Enter the initial altitude of the LM (in meters): ");
      scanf("%d", &alt);
   }
   return alt;
}

void displayLMState(int elapsedTime, double altitude, double velocity, int fuelAmount, int fuelRate)
{
   
   printf("Elapsed Time: %4d s\n", elapsedTime);
   printf("        Fuel: %4d l\n", fuelAmount);
   printf("        Rate: %4d l/s\n", fuelRate);
   printf("    Altitude: %7.2f m\n", altitude);
   printf("    Velocity: %7.2f m/s\n", velocity);
   

}

int getFuelRate(int currentFuel)
{
   int fuelrate;
   printf("Enter fuel rate (0-9, 0=freefall, 5=constant velocity, 9=max thrust): ");
   scanf("%d", &fuelrate);
   while (fuelrate< 0 || fuelrate > 9)
   {
      printf("ERROR: Fuel rate must be between 0 and 9, inclusive\n\n");
      printf("Enter fuel rate (0-9, 0=freefall, 5=constant velocity, 9=max thrust): ");
   scanf("%d", &fuelrate);
   }
   if (currentFuel > fuelrate)
   {
      return fuelrate;
   }
   else
   {
      return currentFuel;
   }
}

double updateAcceleration(double gravity, int fuelRate)
{
   double newAccel;
   newAccel = gravity * ((fuelRate/5.0) -1);
   return newAccel;
}
   
double updateAltitude(double altitude, double velocity, double acceleration)
{
   double newAlt;
   newAlt = altitude + velocity + (acceleration/2);
   if (newAlt >= 0)
   {
      return newAlt;
   }
   else
   {
      return 0;
   }
}

double updateVelocity(double velocity, double acceleration)
{
   double newVel;
   newVel = velocity + acceleration;
   return newVel;
}

int updateFuel(int fuel, int fuelRate)
{
   int newFuel;
   newFuel = fuel - fuelRate;
   return newFuel;
}

void displayLMLandingStatus(double velocity)
{
   if (velocity <= 0.0 && velocity >= -1.0)
   {
      printf("Status at landing - The eagle has landed!\n");
   }
   if (velocity < -1.0 && velocity > -10.0)
   {
      printf("Status at landing - Enjoy your oxygen while it lasts!\n");
   }
   if (velocity <= -10.0 || velocity >0 )
	{
	   printf("Status at landing - Ouch - that hurt!\n");
	}


}

