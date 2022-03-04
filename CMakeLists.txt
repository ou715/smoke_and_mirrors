# CMakeList.txt : CMake project for smoke_and_mirrors, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("smoke_and_mirrors")

# Add source to this project's executable.
add_executable (smoke_and_mirrors "src/smoke_and_mirrors.cpp"  
									"src/math/geometry.h" "src/math/geometry.cpp" 
									"src/math/vector3.h" "src/math/vector3.cpp" 
									"src/math/sphere.h" "src/math/sphere.cpp"
									"src/math/plane.h" "src/math/plane.cpp"
									"src/physics/light.h" "src/physics/light.cpp"
									"src/physics/shade.h" "src/physics/shade.cpp"
									"src/trace.h" "src/trace.cpp" 
									"src/utility/camera.h" "src/utility/camera.cpp" 
									"src/utility/utility.h" "src/utility/utility.cpp"  
									"src/shadowTrace.h" "src/shadowTrace.cpp" 
									"src/raytrace.h"  "src/raytrace.cpp" 
									"src/physics/surface.h"  "src/utility/scene.h")


target_include_directories(smoke_and_mirrors PUBLIC dependencies)