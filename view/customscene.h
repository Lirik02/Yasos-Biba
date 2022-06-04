#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class CustomScene : public QGraphicsScene {
 Q_OBJECT
 public:
  explicit CustomScene(QObject* parent = 0);
  ~CustomScene();

 signals:
  void signalGetMouseCoordinates(QPointF point);
  void signalShotAbility(bool shot);

 public slots:

 private:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  void mousePressEvent(QGraphicsSceneMouseEvent* event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

#endif // CUSTOMSCENE_H
