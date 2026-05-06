include(GoogleTest)

add_executable(test_orbit test_orbit.cpp ${PROJECT_SOURCE_DIR}/src/Orbit.cpp)
target_link_libraries(test_orbit PRIVATE GTest::gtest_main)
target_include_directories(test_orbit PRIVATE ${PROJECT_SOURCE_DIR}/include)
gtest_discover_tests(test_orbit)