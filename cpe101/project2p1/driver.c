/**
 * Moonlander function driver program.
 *
 * The purpose of this program is to test the functions in landerFuncs.c.
 * I have partially implemented some test cases for you.  Implement many
 * more test cases!  (And flesh out the test cases that I have given you.)
 */
 
/* Project 2
*
* Name: Anthony Dinh
* Instructor: Hatalsky
*/

#include "landerFuncs.h"
#include <stdio.h>

#define GRAVITY 1.62

void testGetFuel();
void testUpdateVelocity();
void testShowWelcome();
void testGetAltitude();
void testDisplayLMState();
void testGetFuelRate();
void testUpdateAcceleration();
void testUpdateAltitude();
void testUpdateFuel();
void testDisplayLMLandingStatus();
int compareDoubles(double d1, double d2, double epsilon);

int main()
{
   testShowWelcome();
   printf("\n");
   testGetFuel();
   printf("\n");
   testGetAltitude();
   printf("\n");
   testDisplayLMState();
   printf("\n");
   testGetFuelRate();
   printf("\n");
   testUpdateAcceleration();
   printf("\n");
   testUpdateAltitude();
   printf("\n");
   testUpdateVelocity();
   printf("\n");
   testUpdateFuel();
   printf("\n");
   testDisplayLMLandingStatus();
   printf("\n");
   return 0;

}


void testShowWelcome()
{
   printf("*** Testing showWelcome... ***\n\n");
   showWelcome();
}

void testGetFuel()
{
   int fuel;

   printf("*** Testing getFuel... ***\n\n");

   /* Test 1: Enter a valid number */
   printf("TEST 1: When prompted, input a number greater than 0.  You should not see an error.\n\n");
   fuel = getFuel();
   printf("\nFuel returned was: %d\n", fuel);

   /* Test 2: First enter 0, then a negative number, then a valid number */
   printf("\nTEST 2: When prompted, input 0.  You should see and error and then be prompted again.\n");
   printf("Then enter a negative number.  You should see the same error message and be \n");
   printf("prompted again.  Finally, enter a number greater than 0.\n\n");
   fuel = getFuel();
   printf("\nFuel returned was: %d\n", fuel);
}

void testGetAltitude()
{
   int alt;
   printf("*** Testing getAltitude... ***\n\n");
   
   /* Test 1: Enter a valid number */
   printf("TEST 1: When prompted, input a number greater than 0 and less than 10,000. You should not see an error.\n\n");
   alt = getAltitude();
   printf("\nAltitude returned was: %d\n", alt);
   
   /*Test 2: First enter 0, then a negative number, then a number greater than 10,000, then valid number*/
   printf("\nTEST 2: When prompted, input 0. You should see and error and then be prompted again.\n");
   printf("Then enter a negative number. You should see the same error message and be \n");
   printf("prompted again. Then, enter a number greater than 10,000. You should see the same error.\n");
   printf("Finally, enter a number greater than 0 and less than 10,000.\n\n");
   alt = getAltitude();
   printf("\nAltitude returned was: %d\n", alt);
}

void testDisplayLMState()
{
   
   printf("*** Testing displayLMState... ***\n\n");
   
   /* Test1: (0, 5, 0, 4.00, 0.00) */
   
   displayLMState(0, 5, 0, 4.00, 0.00);
}

void testGetFuelRate()
{
   int fuelrate;
   printf("*** Testing getFuelRate... ***\n\n");  
   
   /*Test 1: (returning the user input) */
   printf("Test 1: Input the number 3 and you should not see an error and the value returned should be 3.\n\n");
   fuelrate = getFuelRate(10);
   printf("\nFuel Rate returned was: %d\n", fuelrate);
   
   /*Test 2: (returning the parameter) */
   printf("Test 2: Input the number 3 and you should not see an error and the value returned should be 2.\n\n");
   fuelrate = getFuelRate(2);
   printf("\nFuel Rate returned was: %d\n", fuelrate);

   /*Test 3: (error) */
   printf("Test 3: Input a value less than zero and you should see the error and get prompted again.\n");
   printf("Then enter a number greater than 9 and see another error and be promopted yet again.\n");
   printf("Enter any number between 0 and 9\n\n");
   fuelrate = getFuelRate(100);
   printf("\nfuel Rate returned was: %d\n", fuelrate);
}

void testUpdateAcceleration()
{
   double acceleration;
   printf("*** Testing updateAcceleration... ***\n\n");  
   
   /*Test 1: fuelrate = 5 */
   printf("Test 1: Inputing gravity constant and 5\n");
   acceleration = updateAcceleration(GRAVITY, 5);
   printf("      Expect: %f\n", 0.0);
   printf("      Got: %f\n", acceleration);
   if (compareDoubles(acceleration, 0.0, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
   
   /*Test 2: fuelrate = 9 */
   printf("Test 2: Inputing gravity constant and 9\n");
   acceleration = updateAcceleration(GRAVITY, 9);
   printf("      Expect: %f\n", 1.296);
   printf("      Got: %f\n", acceleration);
   if (compareDoubles(acceleration, 1.296, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
   
   /*Test 3: fuelrate = 0 */
    printf("Test 2: Inputing gravity constant and 0\n");
   acceleration = updateAcceleration(GRAVITY, 0);
   printf("      Expect: %f\n", -1.62);
   printf("      Got: %f\n", acceleration);
   if (compareDoubles(acceleration, -1.62, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
}

void testUpdateAltitude()
{
   double altitude;
   
   printf("*** Testing updateAltitude... ***\n\n");
   
   /*Test 1: alt = 100, velocity = -1.5, acceleration = 5 */
   printf("Test 1: Inputing 100.0, -1.5, 5.0\n");
   altitude = updateAltitude(100.0,-1.5,5.0);
   printf("      Expect: %f\n", 101.0);
   printf("      Got: %f\n", altitude);
   if (compareDoubles(altitude, 101.0, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
   
   /*Test 2: alt = -1, velocity = -.4, accelration = -5 */
   printf("Test 2: Inputing -1, -.4, -5\n");
   altitude = updateAltitude(-1,-.4,-5);
   printf("      Expect: %f\n", 0.0);
   printf("      Got: %f\n", altitude);
   if (compareDoubles(altitude, 0, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
   
   /*Test 3: alt = 0, velocity = 99.99, acceleration = 0 */
   printf("Test 3: Inputing 0, 99.99, 0\n");
   altitude = updateAltitude(0,99.99,0);
   printf("      Expect: %f\n", 99.99);
   printf("      Got: %f\n", altitude);
   if (compareDoubles(altitude, 99.99, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
   
   /*Test 4: alt = 20, velocity = -20.1, acceleration = 0 */
   printf("Test 4: Inputing 20, -20.1, 0\n");
   altitude = updateAltitude(20,-20.1,0);
   printf("      Expect: %f\n", 0.0);
   printf("      Got: %f\n", altitude);
   if (compareDoubles(altitude, 0, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
}  
void testUpdateVelocity()
{
   double velocity;

   printf("*** Testing updateVelocity... ***\n\n");
   
   /* Test 1: -1.0 and -0.5 */
   printf("TEST 1: Inputing -1 and -0.5\n");
   velocity = updateVelocity(-1.0, -0.5);
   printf("      Expect: %f\n", -1.5);
   printf("      Got: %f\n", velocity);
   /* Compare to see if output velocity and the expected are equal.
    * See the description of the compareDoubles function below. */
   if (compareDoubles(velocity, -1.5, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }

   /* Test 2: 0.0 and 0.0 */
   printf("TEST 2: Inputing 0.0 and 0.0\n");
   velocity = updateVelocity(0.0, 0.0);
   printf("      Expect: %f\n", 0.0);
   printf("      Got: %f\n", velocity);
   if (compareDoubles(velocity, 0.0, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }

   /* Test 3: -100.23 and 1.1 */
   printf("TEST 3: Inputing -100.23 and 1.1\n");
   velocity = updateVelocity(-100.23, 1.1);
   printf("      Expect: %f\n", -99.13);
   printf("      Got: %f\n", velocity);
   if (compareDoubles(velocity, -99.13, .000001))
   {
      printf("      Pass\n");
   }
   else
   {
      printf("      FAIL\n");
   }
}

void testUpdateFuel()
{
   int fuel;
   
   printf("*** Testing updateFuel... ***\n\n");
	
   /*Test 1 Fuel = 100 fuelrate = 0*/
   printf("Test 1: Inputing 100 and 0\n");
   fuel = updateFuel(100,0);
   printf("      Expect: %d\n", 100);
   printf("      Got: %d\n", fuel);
   if (fuel ==100)
   {
      printf("      Pass\n");
   }
   else 
   {
      printf("      FAIL\n");
   }
   
   /*Test 2 Fuel = 5 fuelrate = 6  In general, this test case wont exist because getfuelrate will return the lowest value so it can only be 5 and 5*/
   printf("Test 2: Inputing 5 and 6\n");
   fuel = updateFuel(5,6);
   printf("      Expect: %d\n", -1);
   printf("      Got: %d\n", fuel);
   if (fuel ==-1)
   {
      printf("      Pass\n");
   }
   else 
   {
      printf("      FAIL\n");
   }
   
   /*Test 3 Fuel = 9 fuelrate = 9 */
   printf("Test 3: Inputing 9 and 9\n");
   fuel = updateFuel(9,9);
   printf("      Expect: %d\n", 0);
   printf("      Got: %d\n", fuel);
   if (fuel ==-0)
   {
      printf("      Pass\n");
   }
   else 
   {
      printf("      FAIL\n");
   }
}

void testDisplayLMLandingStatus()
{
   printf("*** Testing displayLMLandingStatus... ***\n\n");
   /*Test first option parameters*/
   printf("Testing first message\n");
   displayLMLandingStatus(1.);
   displayLMLandingStatus(0.);
   displayLMLandingStatus(-1.);
   
   /*Test second */
   printf("Testing second message\n");
   displayLMLandingStatus(-1.1);
   displayLMLandingStatus(-9.99);
   
   /*Test third */
   printf("Testing third message\n");
   displayLMLandingStatus(-10.);
   displayLMLandingStatus(-50);
}
   
/* You cannot compare two doubles using == because they are not stored exactly.
 * Use this function to compare doubles to see if they are equivalent to a certain
 * "close enough" epsilon.
 * 
 * For example to compare two doubles (x and y) and see if there are equivalent to
 * 0.000001, you would call the function like this: 
 * compareDoubles(x, y, 0.000001);
 *
 * Return Value: 0 or 1 (a boolean value)
 */
int compareDoubles(double d1, double d2, double epsilon)
{
   return (d1-d2 > -epsilon && d1-d2 < epsilon);
}
   

