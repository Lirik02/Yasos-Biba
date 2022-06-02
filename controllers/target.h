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
  /* Функция по нанесению урона,
   * величина урона передаётся в качестве аргумента функции
   * */
  void Hit(int damage);

 signals:

 public slots:

 protected:
  QRectF boundingRect() const;
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget);

 private:
  int health_;         // Текущий запас здоровья мишени
  int max_health_;      // Максимальный запас здоровья мишени
};

#endif // TARGET_H
