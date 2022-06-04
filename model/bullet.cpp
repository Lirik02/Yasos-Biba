#include "bullet.h"
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle) {
  while (angle < 0)
    angle += TwoPi;
  while (angle > TwoPi)
    angle -= TwoPi;
  return angle;
}

Bullet::Bullet(QPointF start, QPointF end, QGraphicsItem* hero, QObject* parent)
    : QObject(parent), QGraphicsItem() {
  this->hero_ = hero;
  this->setRotation(0);
  start.rx() -= 0;
  start.ry() += 35;
  this->setPos(start);

  QLineF lineToTarget(start, end);

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

  bullet_timer_ = new QTimer();
  connect(bullet_timer_, &QTimer::timeout, this, &Bullet::slotBulletTimer);
  bullet_timer_->start(7);
}

Bullet::~Bullet() {

}

QRectF Bullet::boundingRect() const {
  return QRectF(0, 0, 10, 34);
}

void Bullet::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {

  painter->drawPixmap(0, 0, QPixmap("../resources/arrow.png"));

  Q_UNUSED(option);
  Q_UNUSED(widget);
}

void Bullet::slotBulletTimer() {
  setPos(mapToParent(0, -3));

  QList<QGraphicsItem*> foundItems = scene()->items(QPolygonF()
                                                        << mapToScene(0, 0)
                                                        << mapToScene(-1, -1)
                                                        << mapToScene(1, -1));

      foreach (QGraphicsItem* item, foundItems) {
      /* Добавляем в проверку ещё и сами взрывы,
       * чтобы пули их игнорировали и не взрывались
       * попав во взрвым от другой пули
       * */
      if (item == this || item == hero_ || item->type() == (UserType + 1))
        continue;
      // При попадании по цели или препятствию, вызываем взрыв
      scene()->addItem(new Sprite(this->pos()));
      callbackFunc(item);     // Вызываем CallBack функцию
      this->deleteLater();    // Уничтожаем пулю
    }

  if (this->x() < 0) {
    this->deleteLater();
  }
  if (this->x() > 1920) {
    this->deleteLater();
  }

  if (this->y() < 0) {
    this->deleteLater();
  }
  if (this->y() > 1080) {
    this->deleteLater();
  }
}

void Bullet::setCallbackFunc(void (* func)(QGraphicsItem*)) {
  callbackFunc = func;
}
