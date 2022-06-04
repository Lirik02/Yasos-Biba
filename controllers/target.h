#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Target : public QObject, public QGraphicsItem {
 Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  explicit Target(QObject* parent = 0);
  ~Target();
  void Hit(int damage);

 signals:

 public slots:

 protected:
  QRectF boundingRect() const;
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget);

 private:
  int health_;
  int max_health_;
};

#endif // TARGET_H
