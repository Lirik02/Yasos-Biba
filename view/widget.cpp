#include "widget.h"
#include "ui_widget.h"

#include <iostream>
#include <cmath>

static int randomBetween(int low, int high) {
  return (rand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    exit_button_(new QPushButton("Exit", this)) {

  this->resize(1440, 900);
  this->setMinimumSize(1440, 900);

  ui->setupUi(this);
  custom_scene_ =
      new CustomScene();

  ui->graphicsView->setScene(custom_scene_);  /// Устанавливаем графическую сцену в graphicsView
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

  custom_scene_->setSceneRect(0,
                              0,
                              Widget::window()->width(),
                              Widget::window()->height());

  // QPolygon polygon;
  // polygon << QPoint(210, 0)
  //         << QPoint(1615, 600)
  //         << QPoint(1150, 1160)
  //         << QPoint(1050, 2420)
  //         << QPoint(1414, 2470)
  //         << QPoint(1960, 690)
  //         << QPoint(2673, 670)
  //         << QPoint(3333, 2222)
  //         << QPoint(4160, 3206)
  //         << QPoint(4160, 0);
  // borders_.emplace_back(polygon);
  // polygon.clear();
  // polygon << QPoint(0, 275)
  //         << QPoint(670, 858)
  //         << QPoint(390, 1340)
  //         << QPoint(581, 3290)
  //         << QPoint(1355, 3340)
  //         << QPoint(2145, 1595)
  //         << QPoint(2440, 1615)
  //         << QPoint(4160, 3600)
  //         << QPoint(4160, 3840)
  //         << QPoint(0, 3840);
  // borders_.emplace_back(polygon);
  // for (int i = 0; i < borders_.size(); ++i) {
  //   custom_scene_->addPolygon(borders_[i]);
  // }
  // custom_scene_->addPolygon(polygon);

  full_fon_ = (QPixmap("../resources/map/map.png"));

  DrawValidMap();

  QCursor cursor = QCursor(QPixmap("../resources/cursor/cursorTarget.png"));
  ui->graphicsView->setCursor(cursor);
  hero_ = new Hero();
  hero_->setPos(Widget::width() / 2,
                Widget::height() / 2);
  hero_->setZValue(2);
  custom_scene_->addItem(hero_);

  move_timer_ = new QTimer();
  connect(move_timer_, &QTimer::timeout, this, &Widget::SlotMovementTimer);
  move_timer_->start(5);

  enemy_damage_timer_ = new QTimer();
  connect(enemy_damage_timer_,
          &QTimer::timeout,
          this,
          &Widget::SlotDamageTimer);
  enemy_damage_timer_->start(1000);

  ui->graphicsView->setMouseTracking(true);

  connect(custom_scene_,
          &CustomScene::signalGetMouseCoordinates,
          hero_,
          &Hero::slotTarget);

  connect(custom_scene_,
          &CustomScene::signalShotAbility, hero_, &Hero::slotShot);

  connect(hero_, &Hero::signalBullet, this, &Widget::slotCreateBullet);

  Widget::update();

  // QPolygon polygon;
  // polygon << QPoint(300, 180) << QPoint(125, 365) << QPoint(100, 149);
  // custom_scene_->addPolygon(polygon);


  target_creating_timer_ = new QTimer();
  connect(target_creating_timer_,
          &QTimer::timeout,
          this,
          &Widget::slotCreateTarget);
  target_creating_timer_->start(1000);

  connect(exit_button_, &QPushButton::pressed, this, [&] {
    auto answer = QMessageBox::question(this, "Exit",
                                        "Are you sure?");
    if (answer == QMessageBox::Yes) {
      close();
    }
  });
  exit_button_->raise();
}

Widget::~Widget() {
  delete ui;
}

void Widget::slotCreateBullet(QPointF start, QPointF end) {
  Bullet* bullet = new Bullet(start, end, hero_);
  bullet->setCallbackFunc(slotHitTarget);
  custom_scene_->addItem(bullet);
}

void Widget::slotCreateTarget() {
  Target* target = new Target();
  custom_scene_->addItem(target);
  target->setPos(rand() % Widget::width(), rand() % Widget::height());
  target->setZValue(-1);
  targets_list_.append(target);
}

void Widget::slotHitTarget(QGraphicsItem* item) {
      foreach (QGraphicsItem* targ, targets_list_) {
      if (targ == item) {
        auto* t = qgraphicsitem_cast<Target*>(targ);
        t->Hit(15);
        targets_list_.removeOne(t);
      }
    }
}

QList<QGraphicsItem*> Widget::targets_list_;

void Widget::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key::Key_A: {
      is_a_key_pressed_ = true;
      break;
    }
    case Qt::Key::Key_S: {
      is_s_key_pressed_ = true;
      break;
    }
    case Qt::Key::Key_D: {
      is_d_key_pressed_ = true;
      break;
    }
    case Qt::Key::Key_W: {
      is_w_key_pressed_ = true;
      break;
    }
  }
}

void Widget::keyReleaseEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key::Key_A: {
      is_a_key_pressed_ = false;
      break;
    }
    case Qt::Key::Key_S: {
      is_s_key_pressed_ = false;
      break;
    }
    case Qt::Key::Key_D: {
      is_d_key_pressed_ = false;
      break;
    }
    case Qt::Key::Key_W: {
      is_w_key_pressed_ = false;
      break;
    }
  }
}

static const double Pi = acos(-1);
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle) {
  while (angle < 0)
    angle += TwoPi;
  while (angle > TwoPi)
    angle -= TwoPi;
  return angle;
}

void Widget::SlotMovementTimer() {

  if (is_a_key_pressed_) {
    hero_->SetRotation(left);
    //hero_->setX(hero_->x() - 1);
    // for (int i = 0; i < borders_.size(); ++i) {
    //   for (int j = 0; j < borders_[i].size(); ++j) {
    //     borders_[i][j].setX(borders_[i][j].x() + 1);
    //   }
    // }
    map_x_--;
    DrawValidMap();

    if (!hero_->scene()->collidingItems(hero_).isEmpty()) {
      //hero_->setX(hero_->x() + 1);
      // for (int i = 0; i < borders_.size(); ++i) {
      //   for (int j = 0; j < borders_[i].size(); ++j) {
      //     borders_[i][j].setX(borders_[i][j].x() - 1);
      //   }
      // }
      map_x_++;
      DrawValidMap();
    } else {
      for (int i = 0; i < targets_list_.size(); ++i) {
        targets_list_[i]->setX(targets_list_[i]->x() + 1);
      }
    }
  }
  if (is_d_key_pressed_) {
    hero_->SetRotation(right);
    //hero_->setX(hero_->x() + 1);
    // for (int i = 0; i < borders_.size(); ++i) {
    //   for (int j = 0; j < borders_[i].size(); ++j) {
    //     borders_[i][j].setX(borders_[i][j].x() - 1);
    //   }
    // }
    map_x_++;
    DrawValidMap();

    if (!hero_->scene()->collidingItems(hero_).isEmpty()) {
      // hero_->setX(hero_->x() - 1);
      // for (int i = 0; i < borders_.size(); ++i) {
      //   for (int j = 0; j < borders_[i].size(); ++j) {
      //     borders_[i][j].setX(borders_[i][j].x() + 1);
      //   }
      // }
      map_x_--;
      DrawValidMap();
    } else {
      for (int i = 0; i < targets_list_.size(); ++i) {
        targets_list_[i]->setX(targets_list_[i]->x() - 1);
      }
    }
  }
  if (is_w_key_pressed_) {
    hero_->SetRotation(up);
    // hero_->setY(hero_->y() - 1);
    // for (int i = 0; i < borders_.size(); ++i) {
    //   for (int j = 0; j < borders_[i].size(); ++j) {
    //     borders_[i][j].setY(borders_[i][j].y() - 1);
    //   }
      map_y_--;
      DrawValidMap();

      if (!hero_->scene()->collidingItems(hero_).isEmpty()) {
        //  hero_->setY(hero_->y() + 1);
        map_y_++;
        DrawValidMap();
      } else {
        for (int i = 0; i < targets_list_.size(); ++i) {
          targets_list_[i]->setY(targets_list_[i]->y() + 1);
        }
        // for (int i = 0; i < borders_.size(); ++i) {
        //   for (int j = 0; j < borders_[i].size(); ++j) {
        //     borders_[i][j].setY(borders_[i][j].y() + 1);
        //   }
        // }
      }
  }
  if (is_s_key_pressed_) {
    hero_->SetRotation(down);
    //hero_->setY(hero_->y() + 1);
    map_y_++;
    DrawValidMap();

    if (!hero_->scene()->collidingItems(hero_).isEmpty()) {
      // hero_->setY(hero_->y() - 1);
      map_y_--;
      DrawValidMap();
    } else {
      for (int i = 0; i < targets_list_.size(); ++i) {
        targets_list_[i]->setY(targets_list_[i]->y() - 1);
      }
      // for (int i = 0; i < borders_.size(); ++i) {
      //   for (int j = 0; j < borders_[i].size(); ++j) {
      //   borders_[i][j].setY(borders_[i][j].y() - 1);
      //   }
      // }
    }
  }
  if (!is_w_key_pressed_ && !is_a_key_pressed_ && !is_s_key_pressed_
      && !is_d_key_pressed_) {
    hero_->SetRotation(in_position);
  }
  for (int i = 0; i < targets_list_.size(); ++i) {
    double x = targets_list_[i]->x() - hero_->x();
    double y = targets_list_[i]->y() - hero_->y();
    double range = sqrt(x * x + y * y);
    if (range <= 500 && range >= 100) {
      targets_list_[i]->setX(targets_list_[i]->x() - x / (range * 2));
      targets_list_[i]->setY(targets_list_[i]->y() - y / (range * 2));
    }
  }
}

void Widget::DrawValidMap() {
  QPixmap visible_fon = full_fon_.copy(map_x_, map_y_,
                                       map_width_, map_height_);
  if (map_x_ < 0) {
    map_x_ = 0;
    for (int i = 0; i < targets_list_.size(); ++i) {
      targets_list_[i]->setX(targets_list_[i]->x() - 1);
    }
  }
  if (map_y_ < 0) {
    map_y_ = 0;
    for (int i = 0; i < targets_list_.size(); ++i) {
      targets_list_[i]->setY(targets_list_[i]->y() - 1);
    }
  }
  if (map_x_ + map_width_ > full_fon_.width()) {
    map_x_ = full_fon_.width() - map_width_;
    for (int i = 0; i < targets_list_.size(); ++i) {
      targets_list_[i]->setX(targets_list_[i]->x() + 1);
    }
  }
  if (map_y_ + map_height_ > full_fon_.height()) {
    map_y_ = full_fon_.height() - map_height_;
    for (int i = 0; i < targets_list_.size(); ++i) {
      targets_list_[i]->setY(targets_list_[i]->y() + 1);
    }
  }
  custom_scene_->setBackgroundBrush(visible_fon);
}

void Widget::SlotDamageTimer() {
  for (int i = 0; i < targets_list_.size(); ++i) {
    double x = targets_list_[i]->x() - hero_->x();
    double y = targets_list_[i]->y() - hero_->y();
    double range = sqrt(x * x + y * y);
    if (range <= 100) {
      bool flag = hero_->Hit(5);
      if (flag) {
        OnLose();
      }
    }
  }
}
void Widget::OnLose() {
  target_creating_timer_->stop();
  move_timer_->stop();
  enemy_damage_timer_->stop();
  target_creating_timer_->stop();
  move_timer_->stop();
  enemy_damage_timer_->stop();

  hero_->deleteLater();

  borders_.clear();

  //custom_scene_->addPixmap(QPixmap("../resources/on_lose.jpg"));

   QPixmap full (QPixmap("../resources/on_lose.jpg"));
  QPixmap part = full.copy(250, 100,
                              map_width_, map_height_);
  custom_scene_->addPixmap(part);

}







