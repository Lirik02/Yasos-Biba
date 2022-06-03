#include "hero.h"
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

Hero::Hero(QObject* parent) :
    QObject(parent), QGraphicsItem() {
  QPixmap image("../resources/character.png");
  current_sprite_ = image.copy(sprite_x_, sprite_y_, 80, 85);
  mouse_position_ =
      QPointF(0, 0);  /// Устанавливаем изначальное положение курсора
  shot_condition_ = false;

  game_timer_ = new QTimer();   /// Инициализируем игровой таймер
  /// Подключаем сигнал от таймера и слоту обработки игрового таймера
  connect(game_timer_, &QTimer::timeout, this, &Hero::slotGameTimer);
  game_timer_->start(250);   /// Стартуем таймер

  bullet_timer_ = new QTimer(); /// Инициализируем таймер создания пуль
  connect(bullet_timer_, &QTimer::timeout, this, &Hero::slotBulletTimer);
  bullet_timer_->start(1000 / 5); /// Стреляем 6 раз в секунду
}

Hero::~Hero() {

}

// Изменены размеры героя
QRectF Hero::boundingRect() const {
  return QRectF(-45, -45, 90, 90);
}

/* Возвращаем форму героя
 * В данном случае лучше использовать эллипс
 * */
QPainterPath Hero::shape() const {
  QPainterPath path;
  path.addEllipse(boundingRect());
  return path;
}

void Hero::paint(QPainter* painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget* widget) {
  /** Отрисовка персонажа
   * */
  // QPolygon polygon;
  // polygon << QPoint(-12, -15) << QPoint(-12, 15) << QPoint(12, 15) << QPoint(12, -15);

  painter->drawPixmap(-45, -45, current_sprite_);

  Q_UNUSED(option);
  Q_UNUSED(widget);
}

void Hero::slotTarget(QPointF point) {
  // /// Определяем расстояние до цели
  mouse_position_ = point;
  // QLineF lineToTarget(QPointF(0, 0), mapFromScene(mouse_position_));
  // /// Угол поворота в направлении к цели
  // qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
  // if (lineToTarget.dy() < 0)
  //   angleToTarget = TwoPi - angleToTarget;
  // angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
  //
  // /** В Зависимости от того, слева или справа находится Муха от Паука,
  //  * устанавливаем направление поворота паука в данном тике таймера
  //  * Скорость разворота зависит от угла, на который необходимо повернуться треугольнику
  //  * */
  // if (angleToTarget >= 0 && angleToTarget < Pi) {
  //   /// Rotate left
  //   setRotation(rotation() - angleToTarget * 180 / Pi);
  // } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
  //   /// Rotate right
  //   setRotation(rotation() + (angleToTarget - TwoPi) * (-180) / Pi);
  // }
}

void Hero::slotGameTimer() {
  NextSprite();
  // QLineF lineToTarget(QPointF(0, 0), mapFromScene(mouse_position_));
  // /// Угол поворота в направлении к цели
  // qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
  // if (lineToTarget.dy() < 0)
  //   angleToTarget = TwoPi - angleToTarget;
  // angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
  //
  // /** В Зависимости от того, слева или справа находится Муха от Паука,
  //  * устанавливаем направление поворота паука в данном тике таймера
  //  * Скорость разворота зависит от угла, на который необходимо повернуться пауку
  //  * */
  // if (angleToTarget >= 0 && angleToTarget < Pi) {
  //   /// Rotate left
  //   setRotation(rotation() - angleToTarget * 180 / Pi);
  // } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
  //   /// Rotate right
  //   setRotation(rotation() + (angleToTarget - TwoPi) * (-180) / Pi);
  // }
}

void Hero::slotBulletTimer() {
  /// Если стрельба разрешена, то вызываем сигнал на создание пули
  if (shot_condition_) emit signalBullet(mapToScene(0, -20), mouse_position_);

}

void Hero::slotShot(bool shot) {
  this->shot_condition_ = shot;  /// Получаем разрешение или запрет на стрельбу
}
void Hero::NextSprite() {
  QPixmap image("../resources/character.png");
  if (rotation_ == down) {
    sprite_y_ = 5;
    sprite_x_ += 80;
    if (sprite_x_ == 830) {
      sprite_x_ = 30;
    }
    current_sprite_ = image.copy(sprite_x_, sprite_y_, 80, 85);
  }
  if (rotation_ == up) {
    sprite_y_ = 175;
    sprite_x_ += 80;
    if (sprite_x_ == 830) {
      sprite_x_ = 30;
    }
    current_sprite_ = image.copy(sprite_x_, sprite_y_, 80, 85);
  }
  if (rotation_ == left) {
    sprite_y_ = 90;
    sprite_x_ += 80;
    if (sprite_x_ == 830) {
      sprite_x_ = 30;
    }
    current_sprite_ = image.copy(sprite_x_, sprite_y_, 80, 85);
  }
  if (rotation_ == right) {
    sprite_y_ = 260;
    sprite_x_ += 80;
    if (sprite_x_ == 830) {
      sprite_x_ = 30;
    }
    current_sprite_ = image.copy(sprite_x_, sprite_y_, 80, 85);
  }
  if(rotation_ == in_position) {
    sprite_x_ = 30;
  }
}

void Hero::SetRotation(Rotation rotation) {
  rotation_ = rotation;
}
void Hero::slotSpritesTimer() {

}
