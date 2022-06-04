
#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QPalette>
#include <QSpinBox>
#include <QLabel>

#include "../view/widget.h"

class Menu : public QMainWindow {

 Q_OBJECT

 public:
  Menu();

  class Settings : public QWidget {
   public:
    Settings(int sound_level);
   private:
    QSpinBox* volume_level_;
    QLabel* sound_;
  };

  Widget* window;

 private:

  QVBoxLayout* layout_;
  QWidget* widget_;

  std::vector<QPushButton*> buttons_;

  QPushButton* play_button_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;

  int sound_level_ = 50;

  void CreateWidgets();
  void ConnectWidgets();

};

#endif //MENU_H
