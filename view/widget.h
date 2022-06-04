#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QImage>

#include "../controllers/hero.h"
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
  void DrawValidMap();

  Ui::Widget* ui;
  CustomScene* custom_scene_;
  Hero* hero_;

  QTimer* target_creating_timer_;
  QTimer* move_timer_;
  QTimer* enemy_damage_timer_;


  static QList<QGraphicsItem*> targets_list_;

  QPushButton* exit_button_;

  bool is_a_key_pressed_ = false;
  bool is_s_key_pressed_ = false;
  bool is_d_key_pressed_ = false;
  bool is_w_key_pressed_ = false;

  int map_x_ = 0;
  int map_y_ = 0;
  int map_width_ = 1440;
  int map_height_ = 900;
  QPixmap full_fon_;

  static void slotHitTarget(QGraphicsItem* item);

 private slots:
  void slotCreateBullet(QPointF start, QPointF end);
  void slotCreateTarget();
  void SlotMovementTimer();
  void SlotDamageTimer();

};

#endif // WIDGET_H
