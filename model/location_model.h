#ifndef LOCATION_MODEL_H
#define LOCATION_MODEL_H

#include <QImage>

class LocationModel {
  QImage GetMap();
  void SetMap();
 private:
  QImage map_;
};

#endif //LOCATION_MODEL_H
