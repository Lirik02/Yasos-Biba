#ifndef VIEW_H_
#define VIEW_H_

#include "scene.h"

#include <QGraphicsScene>

class View : public QGraphicsScene {
 public:
  static View& Instance();
  void Draw();
  Scene& GetScene();
 private:
  Scene scene_{};
};

#endif //VIEW_H_
