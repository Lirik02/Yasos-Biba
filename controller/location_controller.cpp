#include "location_controller.h"

LocationController::LocationController() {
  timer = new QTimer();
  timer -> start(1000 / 50);
}
