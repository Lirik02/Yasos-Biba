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

//#include <windows.h>

enum Rotation{
  up, down, left, right, in_position
};

class Hero : public QObject, public QGraphicsItem {
 Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  explicit Hero(QObject* parent = 0);
  ~Hero();

  void NextSprite();
  void SetRotation(Rotation rotation);
 signals:
  /// Сигнал для создания пули с параметрами траектории
  void signalBullet(QPointF start, QPointF end);

 public slots:
  /// Слот для получения данных о положении курсора
  void slotTarget(QPointF point);
  /// слот для обработки разрешения стрельбы
  void slotShot(bool shot);

 private:
  QRectF boundingRect() const override;
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  QPainterPath shape() const override;     // Функция, возвращающая форму фигуры, необходимо для обработки коллизий

 private slots:
  void slotGameTimer();   /// Игровой слот
  void slotSpritesTimer();   /// Игровой слот
  void slotBulletTimer(); /// Слот проверки пули

 private:
  bool shot_condition_;              /// Переменная состояния стрельбы
  QTimer* bullet_timer_;    /// Таймер пули
  QTimer* game_timer_;      /// Игровой таймер
  QPointF mouse_position_;         /// Положение курсора
  QPixmap current_sprite_;
  int sprite_x_ {30};
  int sprite_y_ {5};
  Rotation rotation_ {down};
};

#endif // HERO_H
