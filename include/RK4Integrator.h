//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef RK4INTEGRATOR_H
#define RK4INTEGRATOR_H

namespace RK4Integrator {
    // State must support: operator+(State), operator*(double)
    // DerivFunc must satisfy: State function(const State&)
    template<typename State, typename DerivFunc>
    State step(const State& state, double dt, DerivFunc f) {
        State k1 = f(state);
        State k2 = f(state + 0.5 * dt * k1);
        State k3 = f(state + 0.5 * dt * k2);
        State k4 = f(state + dt * k3);

        return state + (dt / 6.0) * (k1 + 2.0*k2 + 2.0*k3 + k4);
    }
}

#endif //RK4INTEGRATOR_H
