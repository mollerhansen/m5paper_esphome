# M5Paper ESPHome Improvement Specifications

This document outlines the identified issues and proposed architectural/functional improvements for the M5Paper ESPHome project.

## 1. Identified Issues & Bugs

### 1.1 natlåsens rutine aktiveres men vises ikke længere på skærmen

Jeg ved ikke om det nogle side har været tilfældet men når min natlås rutine køre på timeren kl 22 vises der ikke en alert på skærmen. Er der noget jeg skal opdatere i min rutine i HA?

### 1.2 pikachu vejrudsigt viser både sovende og instruerende pikachu

Vejrudsigten skal ikke vise sovende, sovende skal først komme igen når vejrudsigten går væk.

### 1.3 Manglende Emoji-tegn i skrifttyper (Emoji Glyphs)

- **`font_medium` (FreeSans.ttf)** indeholder ikke emojier. Knappen `"🪟 Luft ud"` på Stue-siden viser emojien `🪟` som manglende tegn.
- **`font_icon` (Noto Emoji str. 55)** mangler glyphs for ikoner som `🔒` (låst dør), `🔋` (batteri), `🧺` (vasketøj), `🫧` (sæbebobler), `💧` (vand leak). Hvis disse sendes som status-ikon, tegnes et tomt felt.
- **`font_calendar` (OpenSansEmoji.ttf str. 32)** indeholder kun et begrænset udvalg af emojier (`♥🍻🏡🚛🍷🎉🎁🎂`). Almindelige kalender-emojier (`📅`, `🚗`, `⚽`, `🎓`, `🏥`, `🛒`, `✈️`, `🔑`) mangler.

### 1.4 Header tekst-overlapning ved lange status-beskeder

I `draw_header` ([`display_helpers.h`](file:///home/david/Documents/CodeProjects/m5paper_esphome/display_helpers.h)) starter statusbeskeden ved `x=50`, mens ur-stemplet er placeret højrejusteret ved `x=530`. Hvis en statusbesked fra Home Assistant er lang (f.eks. `"Kælderdør åben | Lås kælderdør"`), skrives den hen over uret.

### 1.5 Overfyldt Footer på Stue-siden (page_stuen)

På Stue-siden placeres "Luft ud"-knappen (`x=20..220`), den sovende Pikachu (`x=222..318`) og CO2-målingen (`x=330..530`) tæt sammen på samme linje (`y=840`). Højrejustering og afstand bør optimeres for at forhindre overlap.

### 1.6 Alert når gcal integrationen fejler

Vi har gang på gang problemer med gcal integrationen i HA pga auth issues. Lad Pikachu informere om problemet, så jeg kan fixe det.

## 2. Improvements

Stuen er en etage som består af Køkken, bad og stue. 1. sal består Af Georgs værelse, Eskes værelse, Soveværelse og Badeværelse.

### 2.1 Tilføje lys styring i rum (PLANNED)
Vi skal kunne justere lyset i de rum der har smart pøre med en touch kontrol knap (down-arrow, on/off,up-arrow). Vi skal finde ud af at skifte mellem lys og temperatur styrings kontrollen. Måske ved en lys/radiator ikon switch i toppen af etage panelet.
