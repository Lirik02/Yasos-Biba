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
  setRotation(0);      /// Устанавливаем исходный разворот треугольника

  mouse_position_ = QPointF(0, 0);  /// Устанавливаем изначальное положение курсора
  shot_condition_ = false;

  game_timer_ = new QTimer();   /// Инициализируем игровой таймер
  /// Подключаем сигнал от таймера и слоту обработки игрового таймера
  connect(game_timer_, &QTimer::timeout, this, &Triangle::slotGameTimer);
  game_timer_->start(5);   /// Стартуем таймер

  bullet_timer_ = new QTimer(); /// Инициализируем таймер создания пуль
  connect(bullet_timer_, &QTimer::timeout, this, &Triangle::slotBulletTimer);
  bullet_timer_->start(1000 / 5); /// Стреляем 6 раз в секунду
}

Triangle::~Triangle() {

}

// Изменены размеры героя
QRectF Triangle::boundingRect() const {
  return QRectF(-20, -20, 40, 40);
}

/* Возвращаем форму героя
 * В данном случае лучше использовать эллипс
 * */
QPainterPath Triangle::shape() const {
  QPainterPath path;
  path.addEllipse(boundingRect());
  return path;
}

void Triangle::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem* option,
                     QWidget* widget) {
  /** Отрисовка персонажа
   * */
  // QPolygon polygon;
  // polygon << QPoint(-12, -15) << QPoint(-12, 15) << QPoint(12, 15) << QPoint(12, -15);
  painter->setBrush(Qt::red);
  painter->drawEllipse(-10, -15, 20, 30);

  Q_UNUSED(option);
  Q_UNUSED(widget);
}

void Triangle::slotTarget(QPointF point) {
  /// Определяем расстояние до цели
  mouse_position_ = point;
  QLineF lineToTarget(QPointF(0, 0), mapFromScene(mouse_position_));
  /// Угол поворота в направлении к цели
  qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
  if (lineToTarget.dy() < 0)
    angleToTarget = TwoPi - angleToTarget;
  angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

  /** В Зависимости от того, слева или справа находится Муха от Паука,
   * устанавливаем направление поворота паука в данном тике таймера
   * Скорость разворота зависит от угла, на который необходимо повернуться треугольнику
   * */
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
  /// Угол поворота в направлении к цели
  qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
  if (lineToTarget.dy() < 0)
    angleToTarget = TwoPi - angleToTarget;
  angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

  /** В Зависимости от того, слева или справа находится Муха от Паука,
   * устанавливаем направление поворота паука в данном тике таймера
   * Скорость разворота зависит от угла, на который необходимо повернуться пауку
   * */
  if (angleToTarget >= 0 && angleToTarget < Pi) {
    /// Rotate left
    setRotation(rotation() - angleToTarget * 180 / Pi);
  } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
    /// Rotate right
    setRotation(rotation() + (angleToTarget - TwoPi) * (-180) / Pi);
  }
}

void Triangle::slotBulletTimer() {
  /// Если стрельба разрешена, то вызываем сигнал на создание пули
  if (shot_condition_) emit signalBullet(mapToScene(0, -20), mouse_position_);

}

void Triangle::slotShot(bool shot) {
  this->shot_condition_ = shot;  /// Получаем разрешение или запрет на стрельбу
}
