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
    # 1. Update status
    - action: input_text.set_value
      data:
        entity_id: input_text.m5paper_status_icon
        value: "🌬"
    - action: input_text.set_value
      data:
        entity_id: input_text.m5paper_status_text
        value: "Godnat | Slukker huset..."

    # 2. Turn off lights in living room floor (Stue, Køkken, Bad)
    - action: light.turn_off
      target:
        area_id:
          - stue
          - kokken
          - bad_stue # Adjust area IDs as needed for your setup

    # 3. Ensure Kælderdør is locked
    - if:
        - condition: state
          entity_id: lock.kaelderdor
          state: "unlocked"
      then:
        - action: lock.lock
          data:
            entity_id: lock.kaelderdor

    # 4. Final Status
    - action: input_text.set_value
      data:
        entity_id: input_text.m5paper_status_icon
        value: "🌙"
    - action: input_text.set_value
      data:
        entity_id: input_text.m5paper_status_text
        value: "Alt slukket | Godnat!"
```

## Implementation Notes
- **Status Updates**: The script directly updates `input_text.m5paper_status_icon` and `input_text.m5paper_status_text`, which triggers the M5Paper's `on_value` handlers to update the display.
- **Deep Sleep**: To save battery, consider adding a final step to trigger a deep sleep command on the M5Paper after a short delay, or rely on the manual shutdown button on the device.
