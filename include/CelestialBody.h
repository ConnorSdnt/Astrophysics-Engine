//
// Created by Connor Bethel on 06/05/2026.
//

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <unordered_map>
#include <vector>


class CelestialBody {
public:
  static const CelestialBody& get(const std::string& name);
  static const CelestialBody& get(const char* name) { return get(std::string(name)); }
  static const std::vector<std::string>& getAllNames();
  static bool exists(const std::string& name);

  [[nodiscard]] const std::string& getName() const;
  [[nodiscard]] const std::string& getParentName() const;
  [[nodiscard]] double getGm() const;
  [[nodiscard]] double getMeanRadius() const;
  [[nodiscard]] double getSoiRadius() const;
  [[nodiscard]] double getJ2Coef() const;
  [[nodiscard]] bool hasParent() const;

private:
  CelestialBody(std::string  name, double gm, double mean_radius_km, double soi_radius_km, double j2_coef, std::string parent_name);

  const std::string name;
  const std::string parent_name;
  const double gm;
  const double mean_radius_km;
  const double soi_radius_km;
  const double j2_coef;

  static const std::unordered_map<std::string, CelestialBody>& catalogue();
};



#endif //CELESTIALBODY_H
