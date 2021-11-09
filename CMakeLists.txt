# CMakeList.txt : CMake project for ScorchedEarthConsole, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ScorchedEarthConsole")

# Add source to this project's executable.
add_executable (ScorchedEarthConsole "ScorchedEarthConsole.cpp" "ScorchedEarthConsole.h" "LinearAlgebra.h" "HelperLib.cpp" "HelperLib.h")

# TODO: Add tests and install targets if needed.
