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
  emit signalShotAbility(true);
  Q_UNUSED(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  emit signalShotAbility(false);
  Q_UNUSED(event);
}
