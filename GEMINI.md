# GEMINI.md - M5Paper ESPHome Project

## Project Overview
This project provides a comprehensive ESPHome configuration and a set of custom components for the **M5Stack Paper (M5Paper)**. The M5Paper is an ESP32-based device featuring a 4.7" e-ink display, a GT911 touchscreen, a BM8563 RTC, and integrated environmental sensors.

### Key Technologies
- **ESPHome**: The primary framework for building and managing the firmware.
- **C++ / Python**: Custom components are implemented using C++ for hardware interaction and Python for ESPHome integration.
- **IT8951E**: Driver for the e-ink display controller.
- **GT911**: Driver for the capacitive touchscreen.
- **BM8563**: Driver for the Real-Time Clock, essential for low-power operation and deep sleep.

### Hardware Architecture
- **Display**: Connected via SPI (IT8951E controller).
- **Touch**: Connected via I2C (GT911 controller).
- **RTC**: Connected via I2C (BM8563).
- **Sensors**: SHT3xD (Temperature/Humidity) on I2C.
- **Power Management**: Managed via GPIO pins for battery and main power rails.

## Building and Running
To build and flash the firmware, use the ESPHome CLI. It is recommended to use `example.yaml` as a template for your own configuration.

### Common Commands
- **Run/Flash**: `esphome run example.yaml`
- **Logs**: `esphome logs example.yaml`
- **Compile only**: `esphome compile example.yaml`
- **I2C Diagnostic**: `esphome run m5paper.yaml` (Used for scanning the I2C bus to verify hardware connectivity).

## Custom Components
The project includes several custom components in the `custom_components/` directory:

1.  **`it8951e`**: The e-ink display driver. Supports partial updates and rotations.
2.  **`gt911`**: Touchscreen integration. Allows defining touch buttons and regions.
3.  **`bm8563`**: RTC driver. Handles time synchronization and wake-up timers for deep sleep.
4.  **`m5paper`**: General board support component. Manages power rails (`battery_power_pin`, `main_power_pin`) and provides battery voltage sensing.
5.  **`spi`**: A specialized SPI implementation sometimes required for the IT8951E's high-speed communication.

## Development Conventions

### Configuration Structure
- **Boot Sequence**: The M5Paper requires a specific power-on sequence for its peripherals. Refer to the `on_boot` section in `m5paper.yaml` or `example.yaml`.
- **Power Management**: To save battery, use the `m5paper.shutdown_main_power` action. This requires the RTC (`bm8563`) to be configured to wake the device back up.
- **Display Updates**: The e-ink display is usually updated manually via `component.update: m5paper_display` to save power and prevent unnecessary flickering.

### Adding New Features
- Custom components follow the standard ESPHome structure: `__init__.py` for the configuration schema and code generation, and `.h`/`.cpp` files for the C++ implementation.
- If modifying hardware interactions, ensure you account for the power rails (GPIO2 for main power, GPIO5 for battery/peripheral power).

## Key Files
- `example.yaml`: The primary example configuration showing all components working together.
- `m5paper.yaml`: A diagnostic configuration for I2C scanning and power rail testing.
- `custom_components/`: Contains the drivers for M5Paper-specific hardware.
- `FreeSans.ttf`: Default font used in the example display configuration.
