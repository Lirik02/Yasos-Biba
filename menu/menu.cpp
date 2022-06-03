#include "menu.h"

Menu::Menu() :
    layout_(new QVBoxLayout()),
    widget_(new QWidget(this)),
    play_button_(new QPushButton("Играть", this)),
    settings_button_(new QPushButton("Настройки", this)),
    exit_button_(new QPushButton("Выход", this)) {


  resize(700, 700);
  setMinimumSize(300, 300);
  setWindowTitle("Игра");


  //создаем фон
  QPalette palette;
  palette.setBrush(QPalette::Window,
                   QBrush(QPixmap("://01.06.2022/01.06.2022/resources/menu").scaled(this->size())));
  setPalette(palette);

  CreateWidgets();

  ConnectWidgets();

  setCentralWidget(widget_);
}

void Menu::CreateWidgets() {

  buttons_.push_back(play_button_);
  buttons_.push_back(settings_button_);
  buttons_.push_back(exit_button_);

  layout_ ->addWidget(play_button_, 500, Qt::AlignCenter);
  layout_ ->addWidget(settings_button_, 10, Qt::AlignCenter);
  layout_ ->addWidget(exit_button_, 10, Qt::AlignCenter);

  QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  widget_->setSizePolicy(policy);

  widget_ ->setLayout(layout_);
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
    auto answer = QMessageBox::question(this, "Выход",
                                        "Вы уверены?");
    if (answer == QMessageBox::Yes) {
      close();
    }
  });
}

Menu::Settings::Settings(int sound_level) :
volume_level_(new QSpinBox(this)),
sound_(new QLabel("Громкость", this)) {

  setWindowTitle("Настройки");
  setMaximumSize(500, 300);

  QGridLayout* layout = new QGridLayout;

  layout->addWidget(sound_, 0, 0, Qt::AlignLeft);
  layout->addWidget(volume_level_, 0, 1, Qt::AlignCenter);

  QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setSizePolicy(policy);

  setLayout(layout);

  volume_level_->setRange(0, 100);
  volume_level_->setValue(sound_level);

}

