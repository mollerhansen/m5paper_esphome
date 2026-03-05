#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/display/display_buffer.h"

namespace esphome {
namespace it8951e {

// Vi fjerner 'PollingComponent' herfra, da DisplayBuffer allerede arver fra den.
// Dette løser "ambiguous base" fejlen.
class IT8951ESensor : public display::DisplayBuffer,
                      public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING,
                                            spi::DATA_RATE_2MHZ> {
 public:
  float get_loop_priority() const override;
  float get_setup_priority() const override;

typedef struct
{
    uint16_t usPanelW; 
    uint16_t usPanelH; 
    uint16_t usImgBufAddrL;
    uint16_t usImgBufAddrH;
    char usFWVersion[16];   
    char usLUTVersion[16];  
}IT8951DevInfo;

typedef enum               
{                          
    UPDATE_MODE_INIT = 0,  
    UPDATE_MODE_DU   = 1,  
    UPDATE_MODE_GC16 = 2,  
    UPDATE_MODE_GL16 = 3,  
    UPDATE_MODE_GLR16 = 4, 
    UPDATE_MODE_GLD16 = 5, 
    UPDATE_MODE_DU4 = 6,  
    UPDATE_MODE_A2 = 7,  
    UPDATE_MODE_NONE = 8
} m5epd_update_mode_t; 

  void set_reset_pin(GPIOPin *reset) { this->reset_pin_ = reset; }
  void set_busy_pin(GPIOPin *busy) { this->busy_pin_ = busy; }
  void set_cs_pin(GPIOPin *cs) { 
    cs->pin_mode(gpio::FLAG_OUTPUT);
    this->cs_pin_ = cs; 
  }
  void set_reversed(bool reversed) { this->reversed_ = reversed; }
  
  void setup() override;
  void update() override;
  void dump_config() override;

  // LØSNING PÅ DUBLET: Denne linje stod også i toppen. Nu står den kun her.
  display::DisplayType get_display_type() override { return display::DisplayType::DISPLAY_TYPE_BINARY; }

  void clear(bool init);

 protected:
  // LØSNING PÅ REDEFINITION:
  // Vi har kun deklarationerne her (ingen { ... }). 
  // Implementationen ligger i .cpp filen, hvilket er korrekt.
  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  int get_width_internal() override;
  int get_height_internal() override;

  uint32_t get_buffer_length_();

 private:
  IT8951DevInfo *device_info_{nullptr};
  uint8_t *should_write_buffer_{nullptr};
  void get_device_info(IT8951DevInfo *info);

  uint32_t max_x = 0;
  uint32_t max_y = 0;

  GPIOPin *reset_pin_{nullptr};
  GPIOPin *busy_pin_{nullptr};
  GPIOPin *cs_pin_{nullptr};

  bool reversed_ = false;

  void enable_cs();
  void disable_cs();

  void reset(void);

  void wait_busy(uint32_t timeout = 3000);
  void check_busy(uint32_t timeout = 3000);

  uint16_t read_word();
  void read_words(void *buf, uint32_t length);

  void write_two_byte16(uint16_t type, uint16_t cmd);
  void write_command(uint16_t cmd);
  void write_word(uint16_t cmd);
  void write_reg(uint16_t addr, uint16_t data);
  void set_target_memory_addr(uint32_t tar_addr);
  void write_args(uint16_t cmd, uint16_t *args, uint16_t length);

  void set_area(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void update_area(uint16_t x, uint16_t y, uint16_t w,
                    uint16_t h, m5epd_update_mode_t mode);

  void write_buffer_to_display(uint16_t x, uint16_t y, uint16_t w,
                                uint16_t h, const uint8_t *gram);
  void write_display();
};

template<typename... Ts> class ClearAction : public Action<Ts...>, public Parented<IT8951ESensor> {
 public:
  void play(Ts... x) override { this->parent_->clear(true); }
};

}  // namespace it8951e
}  // namespace esphome