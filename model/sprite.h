#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Sprite : public QObject, public QGraphicsItem {
 Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  explicit Sprite(QPointF point, QObject* parent = 0);

  enum { Type = UserType + 1 };

  int type() const;

 signals:

 public slots:

 private slots:
  void nextFrame();

 private:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget);
  QRectF boundingRect() const;

 private:
  QTimer* burst_animation_timer_;
  QPixmap* sprite_image_;
  int current_frame_coordinates_;
};

#endif // SPRITE_H
