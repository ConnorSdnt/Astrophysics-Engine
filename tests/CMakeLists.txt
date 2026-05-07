include(GoogleTest)

add_executable(test_orbit
        test_orbit.cpp
        ${PROJECT_SOURCE_DIR}/src/Orbit.cpp
        ${PROJECT_SOURCE_DIR}/src/CelestialBody.cpp
)
target_link_libraries(test_orbit PRIVATE GTest::gtest_main)
target_include_directories(test_orbit PRIVATE ${PROJECT_SOURCE_DIR}/include)
gtest_discover_tests(test_orbit)

add_executable(test_celestial_body test_celestial_body.cpp ${PROJECT_SOURCE_DIR}/src/CelestialBody.cpp)
target_link_libraries(test_celestial_body PRIVATE GTest::gtest_main)
target_include_directories(test_celestial_body PRIVATE ${PROJECT_SOURCE_DIR}/include)
gtest_discover_tests(test_celestial_body)

add_executable(test_spacecraft test_spacecraft.cpp ${PROJECT_SOURCE_DIR}/src/Spacecraft.cpp)
target_link_libraries(test_spacecraft PRIVATE GTest::gtest_main)
target_include_directories(test_spacecraft PRIVATE ${PROJECT_SOURCE_DIR}/include)
gtest_discover_tests(test_spacecraft)

add_executable(test_state_vector test_state_vector.cpp ${PROJECT_SOURCE_DIR}/src/StateVector.cpp)
target_link_libraries(test_state_vector PRIVATE GTest::gtest_main)
target_include_directories(test_state_vector PRIVATE ${PROJECT_SOURCE_DIR}/include)
gtest_discover_tests(test_state_vector)