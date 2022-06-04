#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QCursor>

enum Rotation{
  up, down, left, right, in_position
};

class Hero : public QObject, public QGraphicsItem {
 Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  explicit Hero(QObject* parent = 0);
  ~Hero();

  bool Hit(int damage);
  void NextSprite();
  void SetRotation(Rotation rotation);
 signals:
  void signalBullet(QPointF start, QPointF end);

 public slots:
  void slotTarget(QPointF point);
  void slotShot(bool shot);

 private:
  QRectF boundingRect() const override;
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  QPainterPath shape() const override;

 private slots:
  void slotGameTimer();
  void slotBulletTimer();

 private:
  bool shot_condition_;

  QTimer* bullet_timer_;
  QTimer* game_timer_;

  QPointF mouse_position_;
  QPixmap current_sprite_;

  int sprite_x_ {30};
  int sprite_y_ {5};

  Rotation rotation_ {down};

  int health_{100};
  int max_health_{100};
};

#endif // HERO_H
