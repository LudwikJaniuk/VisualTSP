#!/bin/sh

g++ -std=c++11 -I /usr/include/boost main.cpp -o client -lboost_system -lboost_thread -lpthread
