cmake_minimum_required(VERSION 3.5)
project(fcsearch VERSION 0.1.0 LANGUAGES C CXX)
include(CTest)
enable_testing()
set(CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 20)

if(ENABLE_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy -extra-arg=-std=gnu++${CMAKE_CXX_STANDARD} --config-file ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy --header-filter=${CMAKE_CURRENT_SOURCE_DIR}/[src|test]*.*hpp)
  if(ENABLE_WERROR)
      set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -warnings-as-errors=*)
  endif()
endif()

aux_source_directory(src sources)
add_executable(fcsearch ${sources} main.cpp)

add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
