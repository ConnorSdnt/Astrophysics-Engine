add_library(Astrophysics_Engine_Core
        Orbit.cpp
        CelestialBody.cpp
        Spacecraft.cpp
        StateVector.cpp
        OrbitalConverter.cpp
)

target_include_directories(Astrophysics_Engine_Core
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)