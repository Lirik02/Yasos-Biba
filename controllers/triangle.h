#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QCursor>

//#include <windows.h>

class Triangle : public QObject, public QGraphicsItem {
 Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  explicit Triangle(QObject* parent = 0);
  ~Triangle();

 signals:
  void signalBullet(QPointF start, QPointF end);

 public slots:
  void slotTarget(QPointF point);
  void slotShot(bool shot);

 private:
  QRectF boundingRect() const override;
  QPainterPath shape() const override;     // Функция, возвращающая форму фигуры, необходимо для обработки коллизий

 private slots:
  void slotGameTimer();
  void slotBulletTimer();

 private:
  bool shot_condition_;
  QTimer* bullet_timer_;
  QTimer* game_timer_;
  QPointF mouse_position_;

};

#endif // TRIANGLE_H
