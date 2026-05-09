//
// Created by Connor Bethel on 06/05/2026.
//

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <unordered_map>


class CelestialBody {
public:
  static const CelestialBody& get(const std::string& name);
  static const CelestialBody& get(const char* name) { return get(std::string(name)); }
  static bool exists(const std::string& name);

  [[nodiscard]] std::string getName() const;
  [[nodiscard]] double getGm() const;
  [[nodiscard]] double getMeanRadius() const;
  [[nodiscard]] double getSoiRadius() const;
  [[nodiscard]] double getJ2Coef() const;

private:
  CelestialBody(std::string  name, double gm, double mean_radius_km, double soi_radius_km, double j2_coef);

  const std::string name;
  const double gm;
  const double mean_radius_km;
  const double soi_radius_km;
  const double j2_coef;

  static const std::unordered_map<std::string, CelestialBody>& catalogue();
};



#endif //CELESTIALBODY_H
