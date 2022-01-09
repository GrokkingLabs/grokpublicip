cmake_minimum_required(VERSION 3.5)

project(rabri LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-E")
set(CMAKE_C_FLAGS_DISTRIBUTION "-E")

set(PROJECT_NAME rabri)
include(CMakePrintHelpers)
include_directories(/usr/local/include)
include_directories(src/main/)
include_directories(src/main/include)
include_directories(src/third_party/)
include_directories(src/third_party/uWebSockets/src/)
include_directories(src/third_party/uWebSockets/uSockets/src)
#include_directories(src/third_party/json/single_include/nlohmann)
#include_directories(src/third_party/spdlog/include/)
#include_directories(src/third_party/fmt/include/)
include_directories(src/third_party/lz4/lib/)
include_directories(src/third_party/argh)


add_compile_definitions(LIBUS_NO_SSL)
add_compile_definitions(UWS_NO_ZLIB)
#add_compile_definitions(LIBUS_USE_LIBUV)
file(GLOB
  USOCKETS
  "src/third_party/uWebSockets/uSockets/src/socket.c"
  "src/third_party/uWebSockets/uSockets/src/loop.c"
  "src/third_party/uWebSockets/uSockets/src/context.c"
  "src/third_party/uWebSockets/uSockets/src/bsd.c"
#  "src/third_party/uWebSockets/uSockets/src/eventing/asio.cpp"
  "src/third_party/uWebSockets/uSockets/src/eventing/epoll_kqueue.c"
  "src/third_party/uWebSockets/uSockets/src/eventing/gcd.c"
  "src/third_party/uWebSockets/uSockets/src/eventing/libuv.c"
  "src/third_party/uWebSockets/uSockets/src/internal/eventing/asio.h"
  "src/third_party/uWebSockets/uSockets/src/internal/eventing/epoll_kqueue.h"
  "src/third_party/uWebSockets/uSockets/src/internal/eventing/gcd.h"
  "src/third_party/uWebSockets/uSockets/src/internal/eventing/libuv.h"
  "src/third_party/uWebSockets/uSockets/src/internal/networking/bsd.h"
  "src/third_party/uWebSockets/uSockets/src/internal/internal.h"
  "src/third_party/uWebSockets/uSockets/src/internal/loop_data.h"
  )

add_compile_definitions(LIBUS_USE_ASIO)
set(LIBUS_USE_ASIO 1)
file(GLOB
  UWEBSOCKETS
  "src/third_party/uWebSockets/src/*.h"
  "src/third_party/uWebSockets/src/f2/function2.hpp"
  )

file(GLOB
  ARGH
  "src/third_party/argh/argh.h"
  )

#file(GLOB
#  JSON_FOR_CPP
#  "src/third_party/json/single_include/nlohmann/json.hpp"
#  )

file(GLOB
  SPDLOG
  "src/third_party/spdlog/include/spdlog/*.h"
  "src/third_party/spdlog/include/spdlog/cfg/*.h"
  "src/third_party/spdlog/include/spdlog/details/*.h"
  "src/third_party/spdlog/include/spdlog/details/*.h"
  "src/third_party/spdlog/include/spdlog/fmt/*.h"
  "src/third_party/spdlog/include/spdlog/fmt/bundled/*.h"
  "src/third_party/spdlog/include/spdlog/sinks/*.h"
  )

file(GLOB
  LZ4_SOURCES
  "src/third_party/lz4/lib/lz4.c"
  "src/third_party/lz4/lib/lz4hc.c"
  "src/third_party/lz4/lib/lz4.h"
  "src/third_party/lz4/lib/lz4hc.h"
  "src/third_party/lz4/lib/lz4frame.c"
  "src/third_party/lz4/lib/lz4frame.h"
  "src/third_party/lz4/lib/xxhash.c")

add_compile_definitions(BOOST_ALL_NO_LIB)
add_compile_definitions(Boost_USE_STATIC_LIBS)
set(Boost_USE_STATIC_LIBS ON)
file(
  GLOB_RECURSE
  BOOST
  "src/third_party/boost/*.hpp"
  )

file(
  GLOB
  CODE_SOURCES
  "src/main/src/main/*.hpp"
  "src/main/src/main/*.cpp"
  "src/main/include/utils/*.hpp"
  "src/main/include/models/*.hpp"
  "src/main/cpp/*.cpp"
  "src/main/cpp/*.c"
  )

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(src/third_party/json/)
add_subdirectory(src/third_party/fmt)
add_subdirectory(src/third_party/spdlog)
#set(EASY_PROFILER_NO_GUI OFF CACHE INTERNAL "")
#set(EASY_PROFILER_NO_SAMPLES OFF CACHE INTERNAL "")
#set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
#add_subdirectory(src/third_party/easy_profiler)
#find_package(easy_profiler REQUIRED)
#add_subdirectory(src/third_party/abseil-cpp)
#add_subdirectory(src/third_party/libuv)
find_package(Threads REQUIRED)
#find_package(libuv REQUIRED)
#find_package (Boost REQUIRED COMPONENTS
#        filesystem
#        program_options
#        system
#        thread
#        )
#add_subdirectory(src/third_party/uWebSockets)

add_executable(${PROJECT_NAME}
  ${USOCKETS}
  ${UWEBSOCKETS}
  ${JSON_FOR_CPP}
#  ${SPDLOG}
#  ${FMT}
  ${ARGH}
  ${CODE_SOURCES}
  ${LZ4_SOURCES}
  ${BOOST}
  main.cpp
  )
link_directories(/usr/local/lib/)
#find_library(libuv PRIVATE)
#target_link_libraries(rabri PRIVATE fmt::fmt-header-only)
#target_link_libraries(rabri PRIVATE spdlog::spdlog_header_only)
#target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
#target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
find_library(USOCKET_LIB uSockets.a /usr/local/lib/)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
#    LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu/)
#    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} dl)
    target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()
message("USOCKET_LIB=${USOCKET_LIB}")
target_link_libraries(${PROJECT_NAME}
  PRIVATE
#        Boost::boost
#        Boost::filesystem
#        Boost::thread
#        Boost::system
#        Boost::program_options
#        Boost::disable_autolinking
        spdlog::spdlog
        fmt::fmt
        nlohmann_json::nlohmann_json
#        easy_profiler

#        absl::algorithm
#        absl::base
#        absl::debugging
#        absl::flat_hash_map
#        absl::flags
#        absl::memory
#        absl::meta
#        absl::numeric
#        absl::random_random
#        absl::strings
#        absl::synchronization
#        absl::time
#        absl::utility
        pthread
        ${USOCKET_LIB}
#        NuDB::beast_extras
        )
add_compile_options(-O3 -v)
