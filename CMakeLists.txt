cmake_minimum_required(VERSION 2.8)
project(SimplePascalCompiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-return-type -Wno-c++11-compat-deprecated-writable-strings -Wno-deprecated-register -Wno-switch")
set(CMAKE_CXX_COMPILER /usr/bin/clang++-6.0)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/parser.cpp)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${BisonOutput}
            COMMAND ${BISON_EXECUTABLE}
            -d ${CMAKE_SOURCE_DIR}/pascal.y
            -o ${CMAKE_SOURCE_DIR}/parser.cpp
            COMMENT "Generating parser.cpp"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/token.cpp)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${FlexOutput}
            COMMAND ${FLEX_EXECUTABLE}
            -o ${CMAKE_SOURCE_DIR}/token.cpp ${CMAKE_SOURCE_DIR}/pascal.l
            COMMENT "Generating token.cpp"
    )
ENDIF()

find_package(LLVM 6.0 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(SOURCE_FILES AbstractTree.cpp CodeGenContext.cpp main.cpp)
add_executable(pascal ${SOURCE_FILES} ${BisonOutput} ${FlexOutput})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(pascal ${llvm_libs})