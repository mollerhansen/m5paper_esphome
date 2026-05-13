# Home Assistant Configuration for M5Paper Climate Control

Add these scripts to your `scripts.yaml` or via the Home Assistant UI (Settings -> Automations & Scenes -> Scripts).

## 1. Ventilate Stuen (Luft ud)
Turns off all radiators/floor heating on the ground floor to save energy while windows are open.

```yaml
m5paper_ventilate_stuen:
  alias: "M5Paper: Luft ud i Stuen"
  icon: mdi:window-open
  sequence:
    - action: climate.set_hvac_mode
      target:
        entity_id:
          - climate.stuen_radiators
          - climate.radiator_kokken
          - climate.gulvvarme_termostat
      data:
        hvac_mode: "off"
    # Optional: Set a status message back to the M5Paper
    - action: input_text.set_value
      target:
        entity_id: input_text.m5paper_status_text
      data:
        value: "Klar" # This dismisses the alert after a while, or you can set a custom "Lufter ud" status.
```

## 2. Adjust Temperature
A generic script to handle +/- button presses from the M5Paper.

```yaml
m5paper_set_temp:
  alias: "M5Paper: Set Temperature"
  mode: parallel
  fields:
    entity_id:
      description: "The climate entity to adjust"
      example: "climate.stuen_radiators"
    target_temp:
      description: "The new target temperature"
      example: 21.5
  sequence:
    - action: climate.set_temperature
      target:
        entity_id: "{{ entity_id }}"
      data:
        temperature: "{{ target_temp }}"
```

## 3. Toggle Climate Mode (Heat/Off)
Toggles a thermostat between heating and off.

```yaml
m5paper_toggle_climate:
  alias: "M5Paper: Toggle Climate Mode"
  mode: parallel
  fields:
    entity_id:
      description: "The climate entity to toggle"
    current_mode:
      description: "The current hvac_mode"
  sequence:
    - action: climate.set_hvac_mode
      target:
        entity_id: "{{ entity_id }}"
      data:
        hvac_mode: "{{ 'heat' if current_mode == 'off' else 'off' }}"
```
