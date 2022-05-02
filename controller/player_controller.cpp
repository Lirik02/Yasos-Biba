#include "player_controller.h"

#include <QGraphicsPixmapItem>

PlayerController& PlayerController::Instance() {
  static PlayerController instance;
  return instance;
}

QPointF& PlayerController::GetCoords() {
  return coords_;
}
