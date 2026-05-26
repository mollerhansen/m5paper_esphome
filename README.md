# M5Paper ESPHome Dashboard

A comprehensive ESPHome configuration and set of custom components for the **M5Stack Paper (M5Paper)**, designed for integration with Home Assistant.

This project features a dynamic UI with a "Pikachu Helper Assistant" that provides alerts and status updates for your smart home.

---

## 🚀 Attribution & Origins

This project is forked from the excellent work by **Stephen Bird ([sebirdman](https://github.com/sebirdman))**. 

Original Repository: [sebirdman/m5paper_esphome](https://github.com/sebirdman/m5paper_esphome)

The core custom drivers included in this project:
- **IT8951E** (E-Ink Display): Originally by sebirdman.
- **GT911** (Touchscreen): Based on work by TomG736 and sebirdman.
- **BM8563** (RTC): Based on work by TomG736 and sebirdman.

---

## ✨ Features

- **Dynamic E-Ink UI**: Multiple pages (Living Room, 1st Floor, Calendar, Outdoor/Forecast).
- **Pikachu Assistant**: 
  - **Animated States**: Happy, Angry, Excited, Informative, and Sleeping.
  - **Contextual Alerts**: Pikachu "speaks" through speech bubbles based on Home Assistant events (e.g., CO2 alerts, doors left open, laundry finished).
- **Climate Controls**: Interactive touch buttons to adjust radiator temperatures and toggle modes.
- **Smart Power Management**: Uses the BM8563 RTC for deep sleep and scheduled wake-ups to preserve battery.
- **Partial Refresh**: Optimized e-ink updates to minimize screen flickering.

---

## 🛠 Recent Improvements

- **Sleeping Pikachu**: Added a resting Pikachu to the home screen when no alerts are active.
- **UI Refinement**: Redesigned alert zones for better readability and prioritized security alerts (e.g., door locks) over appliance notifications.
- **Artifact Fixes**: Programmatically cleaned the 2-bit grayscale sprite data to remove rendering artifacts.
- **Security Hardening**: Migrated credentials to `secrets.yaml`.

---

## 📦 Setup & Installation

### 1. Prerequisites
- [ESPHome](https://esphome.io/) installed locally.
- A Home Assistant instance.

### 2. Configuration (`secrets.yaml`)
For security, this project uses a `secrets.yaml` file for credentials. Create a file named `secrets.yaml` in the root directory with the following content:

```yaml
wifi_ssid: "Your_SSID"
wifi_password: "Your_WiFi_Password"
api_encryption_key: "Your_ESPHome_API_Key"
```

### 3. Compilation & Flashing
To compile and flash the firmware:

```bash
esphome run m5paper.yaml
```

---

## 📂 Project Structure

- `m5paper.yaml`: The primary ESPHome configuration.
- `display_helpers.h`: Custom C++ drawing functions and UI logic.
- `custom_components/`: Hardware drivers (IT8951E, GT911, BM8563).
- `helper_assistant/`: Pikachu grayscale sprites.
- `home_assistant_config/`: Templates for Home Assistant sensors and scripts to drive the dashboard.
- `2026-05-26_blogpost.md`: A detailed write-up about the project's evolution and features.

---

## 📄 License

This project carries the licenses of the original drivers and ESPHome. Please refer to individual component folders for details.
