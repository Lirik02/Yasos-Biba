#include "sprite.h"

Sprite::Sprite(QPointF point, QObject* parent) :
    QObject(parent), QGraphicsItem() {
  this->setPos(point);    // Устанавливаем позицию взрыва
  current_frame_coordinates_ = 0;       /// Координату X начала взрыва пули
  sprite_image_ = new QPixmap("../resources/sprites/sprite_sheet.png");

  burst_animation_timer_ =
      new QTimer();   /// Инициализируем таймер анимации взрыва
  /// Подключаем сигнал от таймера к слоту анимации взрыва
  connect(burst_animation_timer_, &QTimer::timeout, this, &Sprite::nextFrame);
  burst_animation_timer_->start(25);   /// Стартуем таймер с частотой 25 милисекунд
}

QRectF Sprite::boundingRect() const {
  return QRectF(-10, -10, 20, 20);
}

void Sprite::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {
  // Отрисовываем один из кадров взрыва
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
  current_frame_coordinates_ +=
      20; // Продвигаем координату X для выбора следующего кадра
  if (current_frame_coordinates_ >= 300) {
    this->deleteLater();    // Если кадры закончились, то удаляем объект взрыва
  } else {
    this->update(-10,
                 -10,
                 20,
                 20);    // В противном случае обновляем графический объект
  }
}

int Sprite::type() const {
  // Возвращаем тип объекта
  return Type;
}
