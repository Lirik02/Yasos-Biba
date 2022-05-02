#include "view.h"
#include "../controller/player_controller.h"

#include <QGraphicsView>

void View::Draw() {
  QGraphicsView view(&scene_);
  scene_.setSceneRect(0, 0, 800, 600);
  view.show();
}

View& View::Instance() {
  static View instance;
  return instance;
}

Scene& View::GetScene() {
  return scene_;
}

