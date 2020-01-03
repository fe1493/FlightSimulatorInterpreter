# FlySimulatorProject

FlySimulator is a project, where we were given a text file with different commands (in essence a made up language). We interpret the commands to interact with a flight simulator, in order to enable the plane in the simulator, to fly. 

# Downloads/Files

In order to work with the simulator, we need to install the application "FlightGear". We will also be working with a text file of all the commands, with which we will be able to communicate with the simulator

# Installation of FlightGear

Instructions for installation are on the following website
  https://www.flightgear.org/download/main-program/
 
 # How To Compile
 
In order for the code to compile, the program needs to be provided with a text file that list all of the commands of the flight simulator. This file should be provided as a program argument. 

To compile from the command line: use 
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread 

 # How To Run the Program
 
 In order for the program to run and work correctly, after compiling and running the program  
run the FlightGear application, in order to make a connection with the program. Once a successful connection is obtained, after a few moments, the plane should start to move, and soon thereafter, takeoff and fly. 
 



  
