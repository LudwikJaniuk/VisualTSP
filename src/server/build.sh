#!/bin/sh

g++ -std=c++11 -I /usr/include/boost server.cpp -o server -lboost_system -lboost_thread -lpthread
