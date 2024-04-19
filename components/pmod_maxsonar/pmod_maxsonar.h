#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/gpio.h"

namespace esphome {
namespace pmod_maxsonar {

class PmodMaxSonar : public sensor::Sensor, public uart::UARTDevice, public PollingComponent {
  void setup() override;
  void loop() override;
  void update() override;
  void dump_config() override;

 protected:
  GPIOPin *enable_rx_pin_{nullptr};

  void read_data();

public:
  void set_enable_rx_pin(GPIOPin *enable_rx_pin) { this->enable_rx_pin_ = enable_rx_pin; }
};

}  // namespace pmod_maxsonar
}  // namespace esphome
