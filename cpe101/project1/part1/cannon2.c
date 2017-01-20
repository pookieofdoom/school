/* Project 1
 *
 * Name: Anthony Dinh
 * Instructor: Hatalsky 
 * Section: 03
 */

#include <stdio.h>
#include <math.h>
#define GRAVITY 9.8
#define CHINA 500 
#define LOOKOUT 5

double calcTime(double height);
double calcShotDistance(double time, double velocity);
int isHit(double shotDistance, double shipWidth, double shipDistance);

int main()
{
   double height, distance_of_ship, width_of_ship, velocity, distance_of_ball, time;
   
   printf("Enter the height of the cliff (meters): ");
   scanf("%lf", &height);
   
   printf("Enter the distance of the ship from the cliff (meters): ");
   scanf("%lf", &distance_of_ship);
   
   printf("Enter the width of the ship (meters): ");
   scanf("%lf", &width_of_ship);
   
   printf("Enter the velocity of the cannon ball (meters/second): ");
   scanf("%lf", &velocity);
   
   
   
   time = calcTime(height);
   distance_of_ball = calcShotDistance(time, velocity);
   
   if(distance_of_ball > CHINA)
   {
      printf("I think you hit China!!!\n");
   }
   else if(time > LOOKOUT)
   {
      printf("Look out beloooooooooooooooooooooooooooow!\n");
   }
   printf("Distance of ball: %f meters\n", distance_of_ball);
   
   isHit(distance_of_ball, width_of_ship, distance_of_ship);
   
  
   return 0;
}

double calcTime(double height)
{
   double time;
   time = sqrt(height/(GRAVITY/2));
   return time;
}
double calcShotDistance(double time, double velocity)
{
   return velocity * time;
}
int isHit(double shotDistance, double shipWidth, double shipDistance)
{
   if ((shotDistance <= shipDistance + shipWidth/2) &&
      (shotDistance >= (shipDistance - shipWidth/2)))
   {
      printf("Direct hit!!!\n");
	  return 1;
   }
   else
   {
       printf("You missed!\n");
	   return 0;
   }
}
