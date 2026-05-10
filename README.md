# Astrophysics-Engine
A project implementing a C++ astrophysics engine that can accurately plan and simulate fuel-optimal orbital transfers between any celestial bodies in the solar system. Given a spacecraft, an origin orbit around any body, and a targit orbit around any body, it finds the optimal depature date, computes the burn schedule with continously varying mass, and validates the trajectory against a full n-body finite burn simulation.

In screensaver mode, it will run autonomously, picking random destinations, solving real trajectories, and flying a ship across a live rendered solar system forever. 

## Current Status

**Phase 1 - Foundation (✅)**
- US5 - CMake Build system, GoogleTest, GitHub actions CI ✅
- US1 - Orbit representation with 6 orbital elements ✅
- US2 - CelestialBody Catalogue (all solar system bodies) ✅
- US3 - Spacecraft mass and propulsion model ✅

**Phase 2 - Physics Engine (✅)**
- US7 - RK4 integrator and two-body equations of motion ✅
- US8 - J2 oblateness perturbation ✅
- US9 - Trajectory representation ✅
- US10 - SOI detection and automatic frame transitions ✅

## Backlog & User Stories
Full backlog managed in [GitHub Projects](https://github.com/users/ConnorSdnt/projects/4)

## Architecture
```
Astrophysics-Engine/
├── include/        # Public headers
├── src/            # Implementation files
│   ├── CelestialBody.cpp     # Solar system body catalogue with parent hierarchy
│   ├── Orbit.cpp             # 6-element orbital representation (all orbit types)
│   ├── Spacecraft.cpp        # Mass and propulsion model
│   ├── StateVector.cpp       # Cartesian position and velocity
│   ├── OrbitalConverter.cpp  # Elements ↔ state vector conversion
│   ├── TrajectoryPoint.cpp   # Single point in a trajectory
│   ├── Ephemeris.cpp         # JPL mean elements for planetary positions
│   ├── OrbitalPropagator.cpp # RK4 propagation with SOI transitions
│   └── main.cpp              # Entry point
├── tests/          # GoogleTest unit tests
```

**Core components:**

- `Orbit` — immutable snapshot of any orbital state (circular, elliptical, hyperbolic)
- `CelestialBody` — solar system gravitational body catalogue with parent hierarchy (GM, radius, SOI, J2)
- `Spacecraft` — mass and propulsion properties with Tsiolkovsky modelling
- `StateVector` — Cartesian state vector for position and velocity with arithmetic operators
- `OrbitalConverter` — bidirectional conversion between orbital elements and state vectors
- `Ephemeris` — JPL mean orbital elements for all 8 planets at J2000
- `OrbitalPropagator` — RK4 integrator with J2 perturbation and automatic SOI transitions
- `TrajectoryPoint / Trajectory` — full trajectory representation with timestamps and central body

## Tech Stack

- **C++17**
- **CMake 3.20+**
- **GoogleTest** — unit testing

## Build

**Requirements:** CMake 3.20+, C++17 compiler, Ninja

```bash
git clone https://github.com/ConnorSdnt/Astrophysics-Engine.git
cd Astrophysics-Engine
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/Astrophysics-Engine
```

## Tests

```bash
cd build
ctest --output-on-failure
```

## Roadmap

| Phase | Description | Status |
|---|---|---|
| 1 — Foundation | Orbit, CelestialBody, Spacecraft | ✅ |
| 2 — Physics | RK4 propagator, J2, SOI transitions | ✅ |
| 3 — Lambert | Izzo solver, patched conic pipeline | In Progress |
| 4 — Optimiser | Multi-objective, Pareto front | ⬜ Backlog |
| 5 — Validator | Yoshida, finite burns, diff. correction, Monte Carlo | ⬜ Backlog |
| 6 — Ephemeris | JPL SPICE DE440 | ⬜ Backlog |
| 7 — Renderer | SFML solar system visualiser | ⬜ Backlog |
| 8 — Screensaver | Autonomous mission director | ⬜ Backlog |
| 9 — Hardening | Validation, pybind11, release | ⬜ Backlog |
