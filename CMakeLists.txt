cmake_minimum_required(VERSION 3.15)
project(Pizza)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pizza Restaurant.hpp Order.hpp time.hpp driver.hpp userinterface.cpp)