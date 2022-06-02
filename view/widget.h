#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

#include "../controllers/triangle.h"
#include "customscene.h"
#include "../model/bullet.h"
#include "../controllers/target.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget {
 Q_OBJECT

 public:
  explicit Widget(QWidget* parent = 0);
  ~Widget();

 private:
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void SlotMovmentTimer();

  Ui::Widget* ui;
  CustomScene* custom_scene_;        /// Объявляем графическую сцену
  Triangle* triangle_;         /// Объявляем треугольник
  QTimer* target_creating_timer_;        // Таймер для создания мишеней
  static QList<QGraphicsItem*> targets_list_;  // Список мишеней

  bool is_a_key_pressed_ = false;
  bool is_s_key_pressed_ = false;
  bool is_d_key_pressed_ = false;
  bool is_w_key_pressed_ = false;
  QTimer* move_timer_;

  static void slotHitTarget(QGraphicsItem* item); // CallBack Функция

 private slots:
  void slotCreateBullet(QPointF start, QPointF end); /// Слот для создания пули
  void slotCreateTarget(); // Слот для создания мишеней

};

#endif // WIDGET_H
