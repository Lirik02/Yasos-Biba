#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

class Сharacteristics {
 public:
  int GetHealthPoints();
  void SetHealthPoints(int new_health_points);

  int GetManaPoints();
  void SetManaPoints(int new_mana_points);

  int GeStaminaPoints();
  void SetStaminaPoints(int new_stamina_points);

 private:
  int health_points_ = 100;
  int mana_points_ = 100;
  int stamina_points_ = 100;

};

#endif //CHARACTERISTICS_H
