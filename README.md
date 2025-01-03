# ue5_test

## Overview
This project demonstrates a system for dynamically spawning interactive boxes in Unreal Engine based on JSON data fetched from an online source. The implementation is done entirely using Unreal Engine's C++, focusing on functionality, customization, and performance.



## Features and Logic

### Online JSON Data Fetching
- **Logic**: 
  - An HTTP request is sent to fetch a JSON file from the URL: `https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json`.
  - The JSON file is parsed to extract data for each box (type, color, health, score).
  - The extracted data is validated to ensure all required fields are present and correctly formatted.
- **Error Handling**:
  - HTTP errors are managed to ensure fallback behaviors if the file is unavailable.
  - JSON parsing errors are handled to prevent crashes due to malformed data.

### Box Spawning
- **Logic**:
  - The `SpawnCube` function is called to spawn boxes based on JSON data.
  - For each valid JSON entry, a new box is spawned in the game world.
  - The box’s properties (e.g., color, health, score) are dynamically set based on the JSON data.
  - Boxes are spawned across the map at designated locations when the "F" key is pressed.
- **Features**:
  - Material colors are applied dynamically based on the color field from the JSON.

### Custom Material
- **Logic**:
  - A custom material instance is created for each box.
  - A parameterized color control node in the material allows dynamic updates.
  - The color value from the JSON is converted to a format compatible with Unreal Engine materials.

### Shooting and Interaction Mechanics
- **Logic**:
  - The player shoots projectiles.
  - When a projectile  intersects with a box, the box’s health is reduced by 1.
  - If health reaches zero, the box is destroyed, and the player's score is updated.

### Score Display
- **Logic**:
  - A `UUserWidget` is used to display the player’s score.
  - The score is updated whenever a box is destroyed.
- **Features**:
  - UI is implemented in C++ and extended in Blueprint for layout customization.

---

## Steps to Test
1. Press the "F" key to spawn boxes across the map based on JSON data.
2. Shoot the boxes to reduce their health and destroy them.
3. Observe the score displayed on the widget update as each box is destroyed.

### Error Handling Tests
1. Use an unavailable or malformed JSON URL to test HTTP and parsing error handling.

---

## Challenges Faced
1. **Performance Issues with Unreal Engine 5.5**:
   - Compilation and build times in Unreal Engine 5.5 with Visual Studio were noticeably longer compared to versions 5.2 and 5.3.
   - Adjusted workflow to accommodate longer iteration cycles.

2. **Material Logic in C++**:
   - Initially challenging to dynamically set material parameters in C++ but resolved with research and testing.

---

## Repository Structure
- **Source Code**: Contains the C++ implementation for the described features.
- **Assets**: Includes basic Unreal Engine assets for boxes and projectiles.
- **Documentation**: Well-commented code with supporting documents.

---

## How to Run
1. Clone this repository.
2. Open the project in Unreal Engine 5.5 or compatible versions.
3. Compile the code and launch the game.
4. Press the "F" key to test the spawning and gameplay functionality as described in the Steps to Test section.

