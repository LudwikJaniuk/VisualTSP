# Visual TSP

Solving and visualizing the [Travelling Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) in three dimensions.

# Project plan

![project plan](http://i.imgur.com/bu50eBY.png)

The project consists of several parts: A server that solves the TSP problem and broadcasts solutions, a client that visualizes the solutions, and a homemade 3D-renderer that uses only the CPU. 

## Server

The problem is broadcast with a request to the server, specifying several options (eg. problem size), the server generates some data (if it was not sent) and solves a problem, and then sends the solution to the client asking.

## Client

Has a GUI where the user first selects the problem size and maybe other options. Then sends the problem request to the server. Then receives the solution and visualizes it.

### 3D-renderer

The renderer has a general interface that the client uses. We'll start this by implementing a simple renderer that uses existing libraries, and if we have the time, we will write our own cpy 3d-renderer. We will structure the program so that interchanging these works without much effort.

### Optional: Interactivity

Lets the user drag dots around and (live updates|waits for button press).

# useful links

https://github.com/dhbaird/eeasywsclient

Chat client: http://www.taywils.me/2014/11/15/boostchatclient.html

Boost tcp tutorials: http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/tutorial.html
