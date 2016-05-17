#!/bin/sh

g++ -std=c++11 -I /usr/include/boost main.cpp ../common/common.cpp -o server -lboost_system -lboost_thread -lpthread
