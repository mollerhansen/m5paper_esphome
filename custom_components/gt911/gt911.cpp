#include "esphome/core/log.h"
#include "esphome/components/i2c/i2c_bus.h"
#include "gt911.h"

namespace esphome {
namespace gt911 {

static const char *TAG = "gt911.sensor";

void IRAM_ATTR HOT GT911TouchscreenStore::gpio_intr(GT911TouchscreenStore *store) {
  store->touch = true;
}

void GT911::setup(){
  this->interrupt_pin_->pin_mode(gpio::FLAG_INPUT);

  if (this->write(nullptr, 0) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to communicate!");
    this->mark_failed();
    return;
  }

  this->store_.pin = this->interrupt_pin_->to_isr();
  this->interrupt_pin_->attach_interrupt(GT911TouchscreenStore::gpio_intr, &this->store_,
                                          gpio::INTERRUPT_FALLING_EDGE);
                                          
  // Default ranges for M5Paper
  this->x_raw_max_ = 960;
  this->y_raw_max_ = 540;
}

void GT911::update_touches(){
  if (!this->store_.touch)
    return;

  this->store_.touch = false;

  uint8_t pointInfo = this->readByteData(GT911_POINT_INFO);
  uint8_t touches = pointInfo & 0x0F;

  if (touches == 0) {
    this->writeByteData(GT911_POINT_INFO, 0);
    return;
  }

  if (pointInfo & 0x80) {
    uint8_t data[touches * 8];
    if (this->readBlockData(data, 0x8150, touches * 8)) {
      for (int i = 0; i < touches; i++) {
        uint8_t *buf = data + i * 8;
        // GT911 typically has X in 0-1 and Y in 2-3
        // dimension_one = (buf[3] << 8) | buf[2]; // Y
        // dimension_two = (buf[1] << 8) | buf[0]; // X
        uint16_t x = (buf[1] << 8) | buf[0];
        uint16_t y = (buf[3] << 8) | buf[2];
        
        this->add_raw_touch_position_(i, x, y);
      }
      this->send_touches_();
    }
    this->writeByteData(GT911_POINT_INFO, 0);
  }
}

void GT911::dump_config(){
  ESP_LOGCONFIG(TAG, "GT911:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
}

void GT911::calculate_checksum() {
  uint8_t checksum = 0;
  for (uint8_t i=0; i<GT911_CONFIG_SIZE; i++) {
    checksum += configBuf[i];
  }
  checksum = (~checksum) + 1;
  configBuf[GT911_CONFIG_CHKSUM - GT911_CONFIG_START] = checksum;
}

void GT911::reflashConfig() {
  this->calculate_checksum();
  this->writeByteData(GT911_CONFIG_CHKSUM, configBuf[GT911_CONFIG_CHKSUM-GT911_CONFIG_START]);
  this->writeByteData(GT911_CONFIG_FRESH, 1);
}

void GT911::setResolution(uint16_t _width, uint16_t _height) {
  configBuf[GT911_X_OUTPUT_MAX_LOW - GT911_CONFIG_START] = lowByte(_width);
  configBuf[GT911_X_OUTPUT_MAX_HIGH - GT911_CONFIG_START] = highByte(_width);
  configBuf[GT911_Y_OUTPUT_MAX_LOW - GT911_CONFIG_START] = lowByte(_height);
  configBuf[GT911_Y_OUTPUT_MAX_HIGH - GT911_CONFIG_START] = highByte(_height);
  this->reflashConfig();
}

void GT911::writeByteData(uint16_t reg, uint8_t val) {
  uint8_t buffer[3];
  buffer[0] = highByte(reg);
  buffer[1] = lowByte(reg);
  buffer[2] = val;
  this->write(buffer, 3);
}

uint8_t GT911::readByteData(uint16_t reg) {
  uint8_t buffer[2];
  buffer[0] = highByte(reg);
  buffer[1] = lowByte(reg);
  this->write(buffer, 2);
  uint8_t data;
  this->read(&data, 1);
  return data;
}

void GT911::writeBlockData(uint16_t reg, uint8_t *val, uint8_t size) {
  uint8_t buffer[size + 2];
  buffer[0] = highByte(reg);
  buffer[1] = lowByte(reg);
  memcpy(&buffer[2], val, size);
  this->write(buffer, size + 2);
}

bool GT911::readBlockData(uint8_t *buf, uint16_t reg, uint8_t size) {
  uint8_t buffer[2];
  buffer[0] = highByte(reg);
  buffer[1] = lowByte(reg);
  if (this->write(buffer, 2) != i2c::ERROR_OK) {
    return false;
  }
  return this->read(buf, size) == i2c::ERROR_OK;
}

}  // namespace gt911
}  // namespace esphome
