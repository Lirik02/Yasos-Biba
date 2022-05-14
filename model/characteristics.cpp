#include "characteristics.h"

int Сharacteristics::GetHealthPoints() {
  return health_points_;
}
void Сharacteristics::SetHealthPoints(int new_health_points) {
  health_points_ = new_health_points;
}

int Сharacteristics::GetManaPoints() {
  return mana_points_;
}
void Сharacteristics::SetManaPoints(int new_mana_points) {
  mana_points_ = new_mana_points;
}

int Сharacteristics::GeStaminaPoints() {
  return stamina_points_;
}
void Сharacteristics::SetStaminaPoints(int new_stamina_points) {
  stamina_points_ = new_stamina_points;
}
