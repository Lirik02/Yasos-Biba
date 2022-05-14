#include "character_model.h"

CharacterModel::CharacterModel() {
  image_.load("../textures/character.png");
  model_ = QPixmap::fromImage(image_);
}

QPixmap CharacterModel::GetCharacter() {
  return model_;
}

void CharacterModel::SetCharacter(const QString& file_name) {
  image_.load(file_name);
}
