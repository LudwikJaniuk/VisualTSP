#!/bin/sh

g++ -std=c++11 -I /usr/include/boost -I ../common main.cpp ../common/common.cpp -o client.bin -lboost_system -lboost_thread -lpthread
