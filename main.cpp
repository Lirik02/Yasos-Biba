#include "view/view.h"
#include <QGraphicsView>
#include <QApplication>
#include "controller/player_controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  PlayerController::Instance();
  View::Instance();
  QGraphicsView view(&View::Instance().GetScene());
  view.QGraphicsView::setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  View::Instance().GetScene().setSceneRect(0, 0, 800, 600);
  view.show();
  QApplication::exec();
}
