#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../model/character_model.h"
#include "../view/view.h"

#include <QGraphicsScene>

class PlayerController : public QGraphicsScene {
 public:
  static PlayerController& Instance();
  QPointF& GetCoords();
  QPointF& GetDirection();
 private:
  QPointF direction_{400, 300};
  QPointF coords_{400, 300};
};

#endif //PLAYER_CONTROLLER_H
