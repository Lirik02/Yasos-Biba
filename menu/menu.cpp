#include "menu.h"

Menu::Menu() :
    layout_(new QVBoxLayout()),
    widget_(new QWidget(this)),
    play_button_(new QPushButton("Play", this)),
    settings_button_(new QPushButton("Settings", this)),
    exit_button_(new QPushButton("Exit", this)) {

  resize(1440, 900);
  setMinimumSize(1440, 900);
  setWindowTitle("Roguelike");

  play_button_->setStyleSheet("background-color: red;"
                              "border-style: outset;"
                              "border-width: 2px;"
                              "border-radius: 10px;"
                              "border-color: beige;"
                              "font: bold 14px;"
                              "min-width: 10em;"
                              "padding: 6px;");
  settings_button_->setStyleSheet("background-color: red;"
                                  "border-style: outset;"
                                  "border-width: 2px;"
                                  "border-radius: 10px;"
                                  "border-color: beige;"
                                  "font: bold 14px;"
                                  "min-width: 10em;"
                                  "padding: 6px;");
  exit_button_->setStyleSheet("background-color: red;"
                              "border-style: outset;"
                              "border-width: 2px;"
                              "border-radius: 10px;"
                              "border-color: beige;"
                              "font: bold 14px;"
                              "min-width: 10em;"
                              "padding: 6px;");


  //создаем фон
  QPalette palette;
  palette.setBrush(QPalette::Window,
                   QBrush(QPixmap("../resources/menu_fon.jpg").scaled(this->size())));
  setPalette(palette);

  CreateWidgets();

  ConnectWidgets();

  setCentralWidget(widget_);
}

void Menu::CreateWidgets() {

  buttons_.push_back(play_button_);
  buttons_.push_back(settings_button_);
  buttons_.push_back(exit_button_);

  layout_->addWidget(play_button_, 1, Qt::AlignCenter);
  layout_->addWidget(settings_button_, 2, Qt::AlignCenter);
  layout_->addWidget(exit_button_, 3, Qt::AlignCenter);

  layout_->setStretch(1, 0);
  layout_->setStretch(21, 1);
  layout_->setStretch(21, 2);
  layout_->setStretch(21, 3);

  widget_->setLayout(layout_);
}

void Menu::ConnectWidgets() {
  connect(play_button_, &::QPushButton::clicked, this, [&]() {
    window = new (Widget);
    window->show();
    close();
  });
  connect(settings_button_, &::QPushButton::clicked, this, [&]() {
    Settings* settings = new Settings(sound_level_);
    settings->show();
  });

  connect(exit_button_, &::QPushButton::clicked, this, [&]() {
    auto answer = QMessageBox::question(this, "Exit",
                                        "Are you sure?");
    if (answer == QMessageBox::Yes) {
      close();
    }
  });
}

Menu::Settings::Settings(int sound_level) :
    volume_level_(new QSpinBox(this)),
    sound_(new QLabel("Sound", this)) {

  setWindowTitle("Settings");
  setMinimumSize(200, 150);
  resize(200, 150);

  QGridLayout* layout = new QGridLayout;

  layout->addWidget(sound_, 0, 0, Qt::AlignLeft);
  layout->addWidget(volume_level_, 0, 1, Qt::AlignCenter);

  QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setSizePolicy(policy);

  setLayout(layout);

  volume_level_->setRange(0, 100);
  volume_level_->setValue(sound_level);

}

