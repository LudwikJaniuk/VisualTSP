#!/bin/sh

g++ -std=c++11 -I /usr/include/boost -I ../common main.cpp ../common/common.cpp -o client -lboost_system -lboost_thread -lpthread
