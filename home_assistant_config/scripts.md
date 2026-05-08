# Home Assistant Scripts for M5Paper Integration

This file documents the scripts required in Home Assistant to support the M5Paper's advanced features.

## 1. House Power Down
This script orchestrates the shutdown of the home while providing step-by-step feedback to the M5Paper via its status sensors.

```yaml
# Add this to your scripts.yaml
house_power_down:
  alias: "House Power Down"
  icon: mdi:power-sleep
  mode: restart
  sequence:
    # 1. Update
     Pikachu to "Informing" / Working
    - service: input_text.set_value
      target:
        entity_id: input_text.m5paper_status_icon
      data:
        value: "🌬"
    - service: input_text.set_value
      target:
        entity_id: input_text.m5paper_status_text
      data:
        value: "Slukker huset..."

    # 2. Turn off all lights
    # You might want to target specific areas or groups here
    - service: light.turn_off
      target:
        entity_id: all 
    
    # 3. Ensure Kælderdør is locked
    # Based on sensor.kaelderdor_operator availability
    - if:
        - condition: state
          entity_id: lock.kaelderdor
          state: "unlocked"
      then:
        - service: lock.lock
          target:
            entity_id: lock.kaelderdor

    # 4. Final Status: Pikachu goes to sleep
    - service: input_text.set_value
      target:
        entity_id: input_text.m5paper_status_icon
      data:
        value: "🌙"
    - service: input_text.set_value
      target:
        entity_id: input_text.m5paper_status_text
      data:
        value: "Alt slukket. Godnat!"
```

## Implementation Notes
- **Status Updates**: The script directly updates `input_text.m5paper_status_icon` and `input_text.m5paper_status_text`, which triggers the M5Paper's `on_value` handlers to update the display.
- **Deep Sleep**: To save battery, consider adding a final step to trigger a deep sleep command on the M5Paper after a short delay, or rely on the manual shutdown button on the device.
