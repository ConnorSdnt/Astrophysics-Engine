# Astrophysics-Engine
A project implementing a C++ astrophysics engine that can accurately plan and simulate fuel-optimal orbital transfers between any celestial bodies in the solar system. Given a spacecraft, an origin orbit around any body, and a targit orbit around any body, it finds the optimal depature date, computes the burn schedule with continously varying mass, and validates the trajectory against a full n-body finite burn simulation.

In screensaver mode, it will run autonomously, picking random destinations, solving real trajectories, and flying a ship across a live rendered solar system forever. 

## Current Status

**Phase 1 - Foundation (In Progress)**
- US5 - CMake Build system, GoogleTest, GitHub actions CI ✅
- US1 - Orbit representation with 6 orbital elements ✅
- US2 - CelestialBody Catalogue (all solar system bodies) ✅
- US3 - Spacecraft mass and propulsion model ⬜️

## Backlog & User Stories
Full backlog managed in [GitHub Projects](https://github.com/users/ConnorSdnt/projects/4)

## Architecture
```
Astrophysics-Engine/
├── include/        # Public headers
├── src/            # Implementation files
│   ├── Orbit.cpp
│   ├── CelestialBody.cpp
│   └── Spacecraft.cpp (In development)
├── tests/          # GoogleTest unit tests
└── main.cpp        # Entry point
```

**Core components:**

- `Orbit` — immutable snapshot of an orbital state (6 classical elements)
- `CelestialBody` — gravitational body catalogue (GM, radius, SOI, J2)
- `Spacecraft` — mass and propulsion properties _(in progress)_

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
| 1 — Foundation | Orbit, CelestialBody, Spacecraft | In progress |
| 2 — Physics | RK4 propagator, J2, SOI transitions | ⬜ Backlog |
| 3 — Lambert | Izzo solver, patched conic pipeline | ⬜ Backlog |
| 4 — Optimiser | Multi-objective, Pareto front | ⬜ Backlog |
| 5 — Validator | Yoshida, finite burns, diff. correction, Monte Carlo | ⬜ Backlog |
| 6 — Ephemeris | JPL SPICE DE440 | ⬜ Backlog |
| 7 — Renderer | SFML solar system visualiser | ⬜ Backlog |
| 8 — Screensaver | Autonomous mission director | ⬜ Backlog |
| 9 — Hardening | Validation, pybind11, release | ⬜ Backlog |
