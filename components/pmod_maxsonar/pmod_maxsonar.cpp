#include "esphome/core/log.h"
#include "pmod_maxsonar.h"

namespace esphome {
namespace pmod_maxsonar {

static const char *TAG = "pmod_maxsonar.sensor";

void PmodMaxSonar::setup() {
  ESP_LOGCONFIG(TAG, "Setting up PmodMaxSonar '%s'...", this->name_.c_str());

  if (this->enable_rx_pin_ != nullptr) {
    this->enable_rx_pin_->setup();
    this->enable_rx_pin_->pin_mode(gpio::FLAG_OUTPUT);
    this->enable_rx_pin_->digital_write(false);
  }
}

void PmodMaxSonar::loop() {}

void PmodMaxSonar::update() {
  this->enable_rx_pin_->digital_write(true);
  auto f = std::bind(&PmodMaxSonar::read_data, this);
  this->set_timeout("value", 49, f);
}

void PmodMaxSonar::read_data() {
  const int DATA_SIZE = 5;
  uint8_t read_data[DATA_SIZE];

  this->read_array(read_data, DATA_SIZE);
  // this->flush();
  this->enable_rx_pin_->digital_write(false);

  for (auto i = 0; i < DATA_SIZE; i++) {
    ESP_LOGI(TAG, "data\t|\tindex: '%d'\t|\tvalue: '%d'", i, read_data[i]);
  }

  if (read_data[4] != 'R') {
    ESP_LOGW(TAG, "Got faulty reading from MAXSONAR, first char isn't 'R', instead got char id '%d'", read_data[4]);
    this->publish_state(NAN);
    this->status_set_warning();
    return;
  }

   if (read_data[0] != '\r') {
    ESP_LOGW(TAG, "Got faulty reading from MAXSONAR, last char isn't '\\r', instead got char id '%d'", read_data[0]);
    this->publish_state(NAN);
    this->status_set_warning();
    return;
   }

  char frame[3];
  for (int i = 0; i < 3;i++) {
    frame[i] = read_data[3-i];
  }

  uint16_t data = atoi(frame);
}

void PmodMaxSonar::dump_config() {
  ESP_LOGCONFIG(TAG, "PmodMaxSonar '%s'", this->name_.c_str());
  if (this->enable_rx_pin_ != nullptr) {
    LOG_PIN("  Enable RX Pin: ", this->enable_rx_pin_);
  }
}

}  // namespace pmod_maxsonar
}  // namespace esphome
