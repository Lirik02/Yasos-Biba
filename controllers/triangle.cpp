#include "triangle.h"
#include <math.h>
#include <iostream>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle) {
  while (angle < 0)
    angle += TwoPi;
  while (angle > TwoPi)
    angle -= TwoPi;
  return angle;
}

Triangle::Triangle(QObject* parent) :
    QObject(parent), QGraphicsItem() {
  setRotation(0);

  mouse_position_ = QPointF(0, 0);
  shot_condition_ = false;

  game_timer_ = new QTimer();

  connect(game_timer_, &QTimer::timeout, this, &Triangle::slotGameTimer);
  game_timer_->start(5);

  bullet_timer_ = new QTimer();
  connect(bullet_timer_, &QTimer::timeout, this, &Triangle::slotBulletTimer);
  bullet_timer_->start(1000 / 5); /// Стреляем 6 раз в секунду
}

Triangle::~Triangle() {

}

QRectF Triangle::boundingRect() const {
  return QRectF(-20, -20, 40, 40);
}

QPainterPath Triangle::shape() const {
  QPainterPath path;
  path.addEllipse(boundingRect());
  return path;
}

void Triangle::slotTarget(QPointF point) {
  mouse_position_ = point;
  QLineF lineToTarget(QPointF(0, 0), mapFromScene(mouse_position_));

  qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
  if (lineToTarget.dy() < 0)
    angleToTarget = TwoPi - angleToTarget;
  angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

  if (angleToTarget >= 0 && angleToTarget < Pi) {
    /// Rotate left
    setRotation(rotation() - angleToTarget * 180 / Pi);
  } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
    /// Rotate right
    setRotation(rotation() + (angleToTarget - TwoPi) * (-180) / Pi);
  }
}

void Triangle::slotGameTimer() {
  QLineF lineToTarget(QPointF(0, 0), mapFromScene(mouse_position_));

  qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
  if (lineToTarget.dy() < 0)
    angleToTarget = TwoPi - angleToTarget;
  angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

  if (angleToTarget >= 0 && angleToTarget < Pi) {
    /// Rotate left
    setRotation(rotation() - angleToTarget * 180 / Pi);
  } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
    /// Rotate right
    setRotation(rotation() + (angleToTarget - TwoPi) * (-180) / Pi);
  }
}

void Triangle::slotBulletTimer() {
  if (shot_condition_) emit signalBullet(mapToScene(0, -20), mouse_position_);
}

void Triangle::slotShot(bool shot) {
  this->shot_condition_ = shot;
}
