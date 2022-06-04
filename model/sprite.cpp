#include "sprite.h"

Sprite::Sprite(QPointF point, QObject* parent) :
    QObject(parent), QGraphicsItem() {
  this->setPos(point);    // Устанавливаем позицию взрыва
  current_frame_coordinates_ = 0;
  sprite_image_ = new QPixmap("../resources/sprites/sprite_sheet.png");

  burst_animation_timer_ =
      new QTimer();

  connect(burst_animation_timer_, &QTimer::timeout, this, &Sprite::nextFrame);
  burst_animation_timer_->start(25);
}

QRectF Sprite::boundingRect() const {
  return QRectF(-10, -10, 20, 20);
}

void Sprite::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {

  painter->drawPixmap(-10,
                      -10,
                      *sprite_image_,
                      current_frame_coordinates_,
                      0,
                      20,
                      20);
  Q_UNUSED(option);
  Q_UNUSED(widget);
}

void Sprite::nextFrame() {
  current_frame_coordinates_ += 20;
  if (current_frame_coordinates_ >= 300) {
    this->deleteLater();
  } else {
    this->update(-10, -10, 20, 20);
  }
}

int Sprite::type() const {
  return Type;
}
