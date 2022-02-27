# CMakeList.txt : CMake project for smoke_and_mirrors, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("smoke_and_mirrors")

# Add source to this project's executable.
add_executable (smoke_and_mirrors "src/smoke_and_mirrors.cpp"  
									"src/utility.cpp" "src/utility.h" 
									"src/math/geometry.cpp" "src/math/geometry.h" 
									"src/camera.h" "src/camera.cpp" 
									"src/light.h" "src/light.cpp" 
									"src/trace.h" "src/trace.cpp" 
									"src/shade.h" "src/shade.cpp" 
									"src/math/vector3.h" "src/math/vector3.cpp" "src/math/sphere.h" "src/math/sphere.cpp")

# TODO: Add tests and install targets if needed.

target_include_directories(smoke_and_mirrors PUBLIC dependencies)