# Arduino Fuel Pump Simulator

This project is a simple Arduino-based fuel pump simulation using buttons, LEDs, and TM1637 7-segment displays.

---
<img width="832" height="576" alt="20250223_224341" src="https://github.com/user-attachments/assets/eb62a78b-6fcc-4f5a-99f0-85027bcd68b4" />

---

## How It Works

The system simulates a fuel pump with 3 selectable fuel types and real-time price calculation.

### Fuel Selection
- A button on **pin 7** cycles through 3 fuel types.
- Each fuel type is indicated by an LED (pins 2, 3, 4).
- When changed, the pumped litres reset to 0.

---

### Pumping Logic
- A trigger button on **pin 6** controls fuel flow.
- When active, the system adds **0.1 litres every 100ms**.
- Litres increase continuously while the button is held.

---

### Displays (TM1637)

Three 7-segment displays show:

- **Fuel Price (pin 10, 11)** → price per litre for selected fuel
- **Litres Pumped (pin 12, 13)** → total fuel dispensed
- **Total Price (pin 8, 9)** → litres × fuel price

---

## Core Function

### `updateDisplays()`
Updates all displays:
- Shows current fuel price
- Converts litres into display format (×10 scaling)
- Calculates total cost = litres × price

---
<img width="810" height="660" alt="20250224_201027" src="https://github.com/user-attachments/assets/981fe36b-b91a-4d05-977c-c506bdb34fc4" />

---
<img width="696" height="896" alt="20250223_224723" src="https://github.com/user-attachments/assets/f06cc8e9-2f39-4421-8c4d-d7ad2f99dc64" />

---

## Summary

- Button selects fuel type  
- LEDs show selection  
- Trigger simulates pumping fuel  
- Displays update in real time  

---
