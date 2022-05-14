#include "location_controller.h"
#include "player_controller.h"

#include <QGraphicsItem>

LocationController::LocationController(QObject* parent) {
  timer = new QTimer();
  timer->setInterval(1000 / 50);
  connect(timer, &QTimer::timeout, this, &LocationController::MoveSlot);
  timer->start();
}

void LocationController::MoveSlot() {
  if (abs(PlayerController::Instance().GetDirection().x()
              - PlayerController::Instance().GetCoords().x()) > 5
      || abs(PlayerController::Instance().GetDirection().y()
                 - PlayerController::Instance().GetCoords().y()) > 5) {
    QPointF pos = PlayerController::Instance().GetDirection();
    QPointF vector;
    vector.rx() = pos.x() - PlayerController::Instance().GetCoords().x();
    vector.ry() = pos.y() - PlayerController::Instance().GetCoords().y();
    double range = sqrt(vector.rx() * vector.rx() + vector.ry() * vector.ry());
    double times = range / 10;
    PlayerController::Instance().GetCoords().rx() +=
        static_cast<int>(vector.rx() / times);
    PlayerController::Instance().GetCoords().ry() +=
        static_cast<int>(vector.ry() / times);
    View::Instance().GetScene().GetActiveItem()->setPos(PlayerController::Instance().GetCoords());
  }
}
