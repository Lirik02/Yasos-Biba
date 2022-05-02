#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include <QImage>
#include <QPixmap>
class CharacterModel {
 public:
  CharacterModel();

  QPixmap GetCharacter();
  void SetCharacter(const QString& file_name);
 private:
  QImage image_;
  QPixmap model_;
};

#endif //CHARACTER_MODEL_H
