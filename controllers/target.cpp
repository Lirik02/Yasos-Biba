#include "target.h"

static int randomBetween(int low, int high) {
  return (rand() % ((high + 1) - low) + low);
}

Target::Target(QObject* parent) :
    QObject(parent), QGraphicsItem() {
  health_ = randomBetween(1, 15);
  max_health_ = health_;
}

Target::~Target() {

}

QRectF Target::boundingRect() const {
  return QRectF(-20,
                -20,
                64,
                74);
}

void Target::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {

  painter->drawPixmap(-20,
                      -10,
                      QPixmap(
                          "../resources/enemy/1 Pink_Monster/Pink_Monster.png"));

  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::red);
  painter->drawRect(-20, -20, (int) 40 * health_ / max_health_, 3);

  Q_UNUSED(option);
  Q_UNUSED(widget);
}

void Target::Hit(int damage) {
  health_ -= damage;
  this->update(QRectF(-20,
                      -20,
                      64,
                      74));
  if (health_ <= 0) {
    this->deleteLater();
    destroyed(this);
  }
}
