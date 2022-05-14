#include "scene.h"
#include "../controller/player_controller.h"

#include <QGraphicsPixmapItem>
#include <cmath>

Scene::Scene(QObject* parent)
    : QGraphicsScene(parent),
      character_(),
      active_item_(nullptr) {
  active_item_ = new QGraphicsPixmapItem(character_.GetCharacter());
  addItem(active_item_);
  active_item_->setPos(PlayerController::Instance().GetCoords());
}

CharacterModel& Scene::GetCharacterModel() {
  return character_;
}

QGraphicsItem* Scene::GetActiveItem() {
  return active_item_;
}

void Scene::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key::Key_A: {
      PlayerController::Instance().GetCoords().rx() -= 10;
      break;
    }
    case Qt::Key::Key_S: {
      PlayerController::Instance().GetCoords().ry() += 10;
      break;
    }
    case Qt::Key::Key_D: {
      PlayerController::Instance().GetCoords().rx() += 10;
      break;
    }
    case Qt::Key::Key_W: {
      PlayerController::Instance().GetCoords().ry() -= 10;
      break;
    }
  }
  active_item_->setPos(PlayerController::Instance().GetCoords());
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  QGraphicsScene::mousePressEvent(event);
  PlayerController::Instance().GetDirection() = event->scenePos();;
}


