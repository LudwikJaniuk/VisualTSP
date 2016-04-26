# Visual TSP

Solving and visualizing the [Travelling Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) in three dimensions.

# Project plan

![project plan](http://i.imgur.com/bu50eBY.png)

The project consists of several parts: A server that solves the TSP problem and broadcasts solutions, a client that visualizes the solutions, and a homemade 3d-renderer that uses only the cpu. 

## Server

The problem is broadcast with a request to the server, specifying several options (eg. problem size), the server generates some data (if it was not sent) and solves a problem, and then sends the solution to the client asking.

## Client

Has a GUI where the user first selects the problem size and maybe other options. Then sends the problem request to the server. Then receives the solution and visualizes it.

### Optional: Interactivity

Lets the user drag dots around and (live updates|waits for button press). 

## 3D-renderer

The renderer has a general interface that the client uses. I think we'll start by implementing a simple renderer that uses existing libraries, and if we have the time, we write our own cpy 3d-renderer. We structure the program so that interchanging these works without effort.
