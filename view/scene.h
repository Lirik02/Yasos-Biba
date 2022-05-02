#ifndef SCENE_H_
#define SCENE_H_

#include "../model/character_model.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class Scene : public QGraphicsScene {
 Q_OBJECT
 public:
  explicit Scene(QObject* parent = nullptr);
  CharacterModel& GetCharacterModel();
  QGraphicsItem* GetActiveItem();
 private:
  CharacterModel character_;
  QGraphicsItem* active_item_;
  void keyPressEvent(QKeyEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif //SCENE_H_
