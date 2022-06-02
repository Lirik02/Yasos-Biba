#include "customscene.h"

CustomScene::CustomScene(QObject* parent) :
    QGraphicsScene() {
  Q_UNUSED(parent);
}

CustomScene::~CustomScene() {

}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  emit signalGetMouseCoordinates(event->scenePos());
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  emit signalShotAbility(true); /// Когда клавиша мыши нажата, то можно стрелять
  Q_UNUSED(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  emit signalShotAbility(false); /// Когда клавишу мыши отпустили, то стрелять нельзя
  Q_UNUSED(event);
}
