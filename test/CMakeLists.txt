find_package(GTest REQUIRED)
file(GLOB test_sources CONFIGURE_DEPENDS ./*.cpp)
add_executable(
  fcsearch_test
  ${test_sources}
)

target_link_libraries(
  fcsearch_test
  GTest::gtest_main
)

file(GLOB test_sources CONFIGURE_DEPENDS ../src/*.cpp ../src/*.hpp)
target_sources(fcsearch_test PUBLIC ${test_sources})
include(GoogleTest)
gtest_discover_tests(fcsearch_test)

if(CMAKE_COMPILER_IS_GNUCXX)
  LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
  include(CodeCoverage)
  APPEND_COVERAGE_COMPILER_FLAGS()
  setup_target_for_coverage_gcovr_xml(NAME cov
                            EXECUTABLE emscripten_sdl2_framework_test
                            DEPENDENCIES emscripten_sdl2_framework_test
                            EXCLUDE "${PROJECT_SOURCE_DIR}/test/*"
                            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}")

  setup_target_for_coverage_gcovr_html(NAME cov_html 
                            EXECUTABLE emscripten_sdl2_framework_test
                            DEPENDENCIES emscripten_sdl2_framework_test
                            EXCLUDE "${PROJECT_SOURCE_DIR}/test/*"
                            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}") 
endif()