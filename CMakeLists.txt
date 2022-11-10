
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("WordConverter")

file(GLOB SOURCE_FILES
     "src/*.h"
     "src/*.cpp"
)

add_executable (word_converter  ${SOURCE_FILES})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
