#include "widget.h"
#include "ui_widget.h"

#include <iostream>

/** Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high) {
  return (rand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Widget) {
  /// Устанавливаем параметры окна приложения
  this->resize(600, 600);
  this->setFixedSize(600, 600);

  ui->setupUi(this);
  custom_scene_ =
      new CustomScene();    /// Инициализируем кастомизированную сцену

  ui->graphicsView->setScene(custom_scene_);  /// Устанавливаем графическую сцену в graphicsView
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

  custom_scene_->setSceneRect(0,
                              0,
                              Widget::window()->width(),
                              Widget::window()->height());   /// Устанавливаем размеры графической сцены

  /// Создаем кастомизированный курсор из ресурсного файла
  QCursor cursor = QCursor(QPixmap("../resources/cursor/cursorTarget.png"));
  ui->graphicsView->setCursor(cursor);    /// Устанавливаем курсор в QGraphicsView
  triangle_ = new Triangle();  /// Инициализируем треугольник
  triangle_->setPos(60, 60);  /// Устанавливаем стартовую позицию треугольника
  triangle_->setZValue(2);
  custom_scene_->addItem(triangle_);   /// Добавляем треугольник на графическую сцену

  move_timer_ = new QTimer();   /// Инициализируем игровой таймер
  /// Подключаем сигнал от таймера и слоту обработки игрового таймера
  connect(move_timer_, &QTimer::timeout, this, &Widget::SlotMovmentTimer);
  move_timer_->start(5);   /// Стартуем таймер

  /** Разрешаем отслеживание положение курсора мыши
   * без необходимости нажатия на кнопки мыши
   * Применяем это свойство именно для QGraphicsView,
   * в котором установлена графическая сцена
   * */
  ui->graphicsView->setMouseTracking(true);

  /// Подключаем сигнал от графической сцены к слоту треугольника
  connect(custom_scene_,
          &CustomScene::signalGetMouseCoordinates,
          triangle_,
          &Triangle::slotTarget);
  /// Соединяем сигнала стрельбы с графической сцены со слотом разрешения стрельбы треугольника
  connect(custom_scene_,
          &CustomScene::signalShotAbility, triangle_, &Triangle::slotShot);
  /// Соединяем сигнал на создание пули со слотом, создающим пули в игре
  connect(triangle_, &Triangle::signalBullet, this, &Widget::slotCreateBullet);

  // Поставим стены
  custom_scene_->addRect(0, 0, 520, 20, QPen(Qt::NoPen), QBrush(Qt::darkGray));
  custom_scene_->addRect(0, 0, 20, 520, QPen(Qt::NoPen), QBrush(Qt::darkGray));
  custom_scene_->addRect(0,
                         500,
                         520,
                         20,
                         QPen(Qt::NoPen),
                         QBrush(Qt::darkGray));
  custom_scene_->addRect(500,
                         0,
                         20,
                         520,
                         QPen(Qt::NoPen),
                         QBrush(Qt::darkGray));
  custom_scene_->addRect(170,
                         250,
                         180,
                         20,
                         QPen(Qt::NoPen),
                         QBrush(Qt::darkGray));
  custom_scene_->addRect(250,
                         170,
                         20,
                         180,
                         QPen(Qt::NoPen),
                         QBrush(Qt::darkGray));

  // QPolygon polygon;
  // polygon << QPoint(300, 180) << QPoint(125, 365) << QPoint(100, 149);
  // custom_scene_->addPolygon(polygon);

  /// Инициализируем таймер для создания мишеней
  target_creating_timer_ = new QTimer();
  connect(target_creating_timer_,
          &QTimer::timeout,
          this,
          &Widget::slotCreateTarget);
  target_creating_timer_->start(1500);
}

Widget::~Widget() {
  delete ui;
}

void Widget::slotCreateBullet(QPointF start, QPointF end) {
  /// Добавляем на сцену пулю
  Bullet* bullet = new Bullet(start, end, triangle_);
  bullet->setCallbackFunc(slotHitTarget);
  custom_scene_->addItem(bullet);
}

void Widget::slotCreateTarget() {
  Target* target = new Target();  /// Создаём цель
  custom_scene_->addItem(target);         /// Помещаем цель в сцену со случайной позицией
  target->setPos(rand() % ((500 - 40 + 1) - 40) + 40,
                 rand() % ((500 - 40 + 1) - 40) + 40);
  target->setZValue(-1);          /// Помещаем цель ниже Героя
  targets_list_.append(target);         /// Добавляем цель в список
}

void Widget::slotHitTarget(QGraphicsItem* item) {
  /** Получив сигнал от Пули
   * Перебираем весь список целей и наносим ему случайный урон
   * */
      foreach (QGraphicsItem* targ, targets_list_) {
      if (targ == item) {
        /// Кастуем объект из списка в класс Target
        Target* t = qgraphicsitem_cast<Target*>(targ);
        t->Hit(randomBetween(1, 3)); /// Наносим урон
      }
    }
}

QList<QGraphicsItem*> Widget::targets_list_; /// реализация списка

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

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle) {
  while (angle < 0)
    angle += TwoPi;
  while (angle > TwoPi)
    angle -= TwoPi;
  return angle;
}

void Widget::SlotMovmentTimer() {
  /** Перемещаем треугольник в зависимости от нажатых кнопок
   * */
  if (is_a_key_pressed_) {
    triangle_->setX(triangle_->x() - 1);
    /* Проверяем на столкновение,
     * если столкновение произошло,
     * то возвращаем героя обратно в исходную точку
     * */
    if (!triangle_->scene()->collidingItems(triangle_).isEmpty()) {
      triangle_->setX(triangle_->x() + 1);
    }
  }
  if (is_d_key_pressed_) {
    triangle_->setX(triangle_->x() + 1);
    /* Проверяем на столкновение,
     * если столкновение произошло,
     * то возвращаем героя обратно в исходную точку
     * */
    if (!triangle_->scene()->collidingItems(triangle_).isEmpty()) {
      triangle_->setX(triangle_->x() - 1);
    }
  }
  if (is_w_key_pressed_) {
    triangle_->setY(triangle_->y() - 1);
    /* Проверяем на столкновение,
     * если столкновение произошло,
     * то возвращаем героя обратно в исходную точку
     * */
    if (!triangle_->scene()->collidingItems(triangle_).isEmpty()) {
      triangle_->setY(triangle_->y() + 1);
    }
  }
  if (is_s_key_pressed_) {
    triangle_->setY(triangle_->y() + 1);
    /* Проверяем на столкновение,
     * если столкновение произошло,
     * то возвращаем героя обратно в исходную точку
     * */
    if (!triangle_->scene()->collidingItems(triangle_).isEmpty()) {
      triangle_->setY(triangle_->y() - 1);
    }
  }
}



