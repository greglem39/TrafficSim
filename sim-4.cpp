#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctime>


using namespace std;


bool carArrival() //this is my global bool for coinflip
{


  int coinFlip; //storing the value to determine chance of car arrival
  coinFlip = rand() % 2 + 1; //random gen number from 1 to 2 

 if (coinFlip == 2) //I've chosen 2 to be my instance where a car is added
    {
      return true;
    } else {
    return false;
    }
}

class IntersectionController //setting up a controller for the lights in our intersection
{
private:
  enum streetlight {red, green}; // enumerating lights to be red and green to set up for boolean

  streetlight streetlights[4]; //creating an array of streetlights  

  const int  maxCycles = 400000; //in 1 million seconds, I've calculated that the lights will cycle this number of times (1mil/3)
  int cycleCount = 0; //this will store the number of times my lights cycle for control
public:
  void cycle(int array[4], int carCounter[4], double& intersectionTimer); //declaring a function in the class
 
};

void IntersectionController::cycle(int array[4], int carCounter[4], double& intersectionTimer)
{
  int count = 0; //creating an int to count the ticks
  int i; //placeholder for i  

  while (cycleCount < maxCycles) {
    cycleCount++; 
   for (i = 0; i < 3; i++)
	{
	  if (array[i] > 0) //sensor for the light
	    {
             streetlights[i] = green; //the light is green!
	      if (carArrival() == true) //if the carArrival bool returns true, we will add cars
		{
		  array[0]++; //add to the array
		  carCounter[0]++; //add to carCounter each time a car arrives
		}
	      if (carArrival() == true) //if the carArrival bool returns true, we will add cars
		{
		  array[1]++; //add to the array
		  carCounter[1]++; //add to carCounter each time a car arrives
		}
	      if (carArrival() == true) //if the carArrival bool returns true, we will add cars
		{
		  array[2]++; //add to the array
		  carCounter[2]++; //add to carCounter each time a car arrives
		}
	      if (carArrival() == true) //if the carArrival bool returns true, we will add cars
		{
		  array[3]++; //add to the array
		  carCounter[3]++; //add to carCounter each time a car arrives
		}    
	  if (array[i] > 0) //this will serve to ensure that cars go when their light and street is called
	    {
	      array[i] -= 1; //decriment the array by 1 if there is a car present at the light
	    }
	  // cout << "The light is: " << s << endl; //display the light
	  for (double j = 0; j <= 1.5; j++)
	    {
	      //this is counting out my seconds the light will be green
	     for (int k = 0; k <= 1; k++)
		{
		  //this is counting out the seconds the car will be in the intersection
		  intersectionTimer++; 
		}
	    }
	    }
	  streetlights[i] = red; //turn the light red	  
	}
  }
}

int main()
{

  IntersectionController intersectionController; //creating Intersection Controller object

  double intersectionTimer; //counter to track time in intersection

  srand(time(NULL)); //seeding my random generator so it reseeds with each loop

  enum road {top, right, bottom, left}; //enumerating types for each road that will be used
 
  int lanes[4]; //creating an array for the roads

  int carCounter[4]; //creating an array to store the number of cars arriving each time

  road streetName; //initiating an object to make use of the roads class

  //initiate each road into the array[4]
   lanes[top] = 30;
   lanes[right] = 40;
   lanes[bottom] = 50;
   lanes[left] = 60;
  

   //initiate each carCounter with the same enumeration as the lanes
   carCounter[top] = 30;
   carCounter[right] = 40;
   carCounter[bottom] = 50;
   carCounter[left] = 60;

  //building the roads
  for (streetName = top; streetName <= left; streetName =road(streetName + (road)1)) //while we're less than the highest value, keep building the array
    {
      cout << "There are " << lanes[streetName] << " cars waiting at " << streetName << " at the start of the simulation." << endl;
      cout << "**********" << endl;
    }

  intersectionController.cycle(lanes, carCounter, intersectionTimer); //calling the cycle function


  for (streetName = top; streetName <= left; streetName =road(streetName + (road)1)) //while we're less than the highest value, keep building the array
    {
      cout << "There were " << carCounter[streetName] << " total cars waiting at " << streetName << " during the simulation." << endl;
      }
 cout << "Cars were in the intersection for " << intersectionTimer << " seconds." << endl;
 cout << "*********" << endl;

  for (streetName = top; streetName <= left; streetName =road(streetName + (road)1)) //while we're less than the highest value, keep building the array
    {
      cout << "The average number of cars waiting to enter " << streetName << " is " << double(carCounter[streetName]) / 83333 << endl;
      //83333 is equal to the total number of COMPLETE cycles divided by the number of roads (333333/4)
    }

  cout << "The percent of time spent in the intersection was " <<(intersectionTimer / 10000000) * 100 << "%" << endl;
}


