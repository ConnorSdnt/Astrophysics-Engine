//
// Created by Connor Bethel on 07/05/2026.
//

#ifndef SPACECRAFT_H
#define SPACECRAFT_H

class Spacecraft {
public:
    Spacecraft(double dry_mass_kg, double fuel_mass_kg, double thrust_N, double isp);

    [[nodiscard]] double getDryMass() const;
    [[nodiscard]] double getFuelMass() const;
    [[nodiscard]] double getThrust() const;
    [[nodiscard]] double getIsp() const;
    [[nodiscard]] double getWetMass() const;
    [[nodiscard]] double getMaxDeltaV() const;
    [[nodiscard]] double getMassFlowRate() const;

private:
    const double dry_mass_kg;
    double fuel_mass_kg;
    const double thrust_N;
    const double isp;
};

#endif //SPACECRAFT_H
