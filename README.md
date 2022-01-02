# Introduction
This is a service to get the public IP of the service that is calling it.

# Building
## Pre-requisite
- CMake
- C++17 supported compiler
- make
## How to Build
- git clone https://github.com/GrokkingLabs/rabri.git rabri # Clone the repository 
- cd rabri # Go to the directory
- git submodule update --init --recursive # Initialize the submodules
- mkdir build # Create a build directory to store the build files
- cmake -H. -Bbuild -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release # Generate make files Unix systems
- make -C build # Build the project
- ./build/rabri --port=8081 # Start the server in the port mentioned
