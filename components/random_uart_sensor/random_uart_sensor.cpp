#include "esphome/core/log.h"
#include "random_uart_sensor.h"

namespace esphome {
namespace random_uart_sensor {

static const char *TAG = "random_uart_sensor.sensor";

void RandomUARTSensor::setup() {

}

void RandomUARTSensor::update() {
    this->publish_state(42);
}

void RandomUARTSensor::loop() {

}

void RandomUARTSensor::dump_config(){
    ESP_LOGCONFIG(TAG, "Random UART sensor");
}

}  // namespace random_UART_sensor
}  // namespace esphome