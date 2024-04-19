#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace random_uart_sensor {

class RandomUARTSensor : public sensor::Sensor {
 public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
};

}  // namespace random_uart_sensor
}  // namespace esphome