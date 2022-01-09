# Introduction
This is a service to get the public IP of the service that is calling it.

# Building
## Pre-requisite
- CMake
- C++17 supported compiler or above
- make
- uSockets library (Clone the library and then execute make)
- Docker # in case you want to execute in the docker environment

## How to Build

### Building binary
- git clone https://github.com/GrokkingLabs/rabri.git rabri # Clone the repository 
- cd rabri # Go to the directory
- git submodule update --init --recursive # Initialize the submodules
- mkdir build # Create a build directory to store the build files
- cmake -H. -Bbuild -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release # Generate make files Unix systems
- make -C build # Build the project

### Building docker image
- cd build
- docker build -t rabri . # You have to be in the build directory

## Executing

### Executing the binary
- ./build/rabri --port=8081 --threaded=1 # Start the server in the port mentioned
- nohup ./build/rabri --port=8081 --threaded=1 & # To start without shell associated
- docker run --name rabri -p 8080:8080 -d rabri

# Using the library

## / endpoint
This endpoint will give you the public ip
```curl --location --request GET 'http://<server-address>:8080/'```
