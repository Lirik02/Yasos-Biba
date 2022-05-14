#ifndef LOCATION_CONTROLLER_H
#define LOCATION_CONTROLLER_H

#include <QTimer>

class LocationController : public QObject {
 Q_OBJECT
 public:
  explicit LocationController(QObject* parent = nullptr);
 private:
  QTimer* timer;
 private slots:
  void MoveSlot();
};

#endif //LOCATION_CONTROLLER_H
