cmake_minimum_required(VERSION 3.5)

project(rabri LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-E")
set(CMAKE_C_FLAGS_DISTRIBUTION "-E")

include(CMakePrintHelpers)
include_directories(/usr/local/include)
include_directories(src/main/)
include_directories(src/main/include)
include_directories(src/third_party/)
#include_directories(src/third_party/boost)
include_directories(src/third_party/uWebSockets/src/)
include_directories(src/third_party/uWebSockets/uSockets/src)
include_directories(src/third_party/json/single_include/nlohmann)
#include_directories(src/third_party/spdlog/include/)
#include_directories(src/third_party/fmt/include/)
include_directories(src/third_party/lz4/lib/)

add_compile_definitions(LIBUS_NO_SSL)
add_compile_definitions(UWS_NO_ZLIB)
file(GLOB
  UWEBSOCKETS
  "src/third_party/uWebSockets/src/*.h"
  "src/third_party/uWebSockets/src/f2/function2.hpp"
  )

file(GLOB
  USOCKETS
  "src/third_party/uWebSockets/uSockets/src/*.c"
  "src/third_party/uWebSockets/uSockets/src/*.h"
  "src/third_party/uWebSockets/uSockets/src/eventing/*.c"
  "src/third_party/uWebSockets/uSockets/src/eventing/*.h"
  "src/third_party/uWebSockets/uSockets/src/crypto/*.c"
  "src/third_party/uWebSockets/uSockets/src/crypto/*.cpp"
  "src/third_party/uWebSockets/uSockets/src/crypto/*.h"
  "src/third_party/uWebSockets/uSockets/src/internal/*.h"
  "src/third_party/uWebSockets/uSockets/src/internal/eventing/*.h"
  "src/third_party/uWebSockets/uSockets/src/internal/networking/*.h"
  )

file(GLOB
  JSON_FOR_CPP
  "src/third_party/json/single_include/nlohmann/json.hpp"
  )

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
  )
add_subdirectory(src/third_party/fmt)
add_subdirectory(src/third_party/spdlog)

add_executable(rabri
  ${UWEBSOCKETS}
  ${USOCKETS}
  ${JSON_FOR_CPP}
#  ${SPDLOG}
#  ${FMT}
  ${CODE_SOURCES}
  ${LZ4_SOURCES}
  ${BOOST}
  main.cpp
  )
#target_link_libraries(rabri PRIVATE fmt::fmt-header-only)
#target_link_libraries(rabri PRIVATE spdlog::spdlog_header_only)
target_link_libraries(rabri PRIVATE spdlog::spdlog)
target_link_libraries(rabri PRIVATE fmt::fmt)
link_directories(/usr/local/lib/)
#add_compile_options(-O3 -v)
