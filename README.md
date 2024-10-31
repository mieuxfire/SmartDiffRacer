# E-Drive Pro

E-Drive Pro is an advanced electronic differential control system for an electric car. This project utilizes an ESP32 microcontroller to control three motors—one front BLDC motor and two rear motors—while employing encoder-based steering and throttle inputs. The system features real-time speed adjustments and a user-friendly OLED display for monitoring and configuring settings.

## Features

- **Electronic Differential Control**: Independently controls the left and right rear motors based on steering angle and throttle input, ensuring smooth cornering.
- **PID Control**: Employs PID controllers for precise motor speed management, enhancing stability and performance.
- **OLED Display**: Displays real-time information such as steering angle, set speed, and individual motor speeds.
- **Menu Navigation**: Adjustable parameters and settings using a rotary encoder with push-button functionality.

## Hardware Requirements

- ESP32 microcontroller
- Three DC or BLDC motors
- Two encoders (for steering and menu control)
- 1.3" OLED I2C display (128x64 pixels)
- Power supply suitable for the motors and ESP32

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/e-drive-pro.git
   ```
2. Install the necessary libraries:
   - [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
   - [Encoder Library](https://github.com/PaulStoffregen/Encoder)
   - [PID Library](https://github.com/br3ttb/Arduino-PID-Library)

3. Open the project in the Arduino IDE and upload the code to your ESP32.

## Code Overview

### Main Components

1. **Encoder Setup**:
   - Two encoders are utilized: one for measuring the steering angle and the other for navigating the menu.

2. **Motor Control**:
   - The code calculates individual speeds for the left and right rear motors based on the steering angle and throttle input using an electronic differential logic.

3. **PID Control**:
   - The system uses PID controllers to adjust the motor speeds, ensuring responsive and stable driving dynamics.

4. **OLED Display**:
   - The display provides real-time feedback and visual representation of the current settings and speeds.

### Menu Overview

Below is an ASCII art representation of the menu structure available through the OLED display:

```
+-------------------+
|    Main Menu      |
+-------------------+
| 1. Set Speed      |
| 2. View Status    |
| 3. Calibrate      |
| 4. Exit           |
+-------------------+
```

#### Menu Options Description

- **Set Speed**: Adjust the target speed for the motors.
- **View Status**: Display current steering angle, set speed, and motor speeds.
- **Calibrate**: Calibration settings for the motors and sensors.
- **Exit**: Exit the menu and return to normal operation.

## Usage

1. **Power On**: Connect the power supply to the ESP32 and motors.
2. **Navigate Menu**: Use the rotary encoder to scroll through the menu and press the button to select options.
3. **Monitor Performance**: Observe the OLED display for real-time feedback on your vehicle's performance.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Thanks to the authors of the libraries used in this project.
- Special thanks to the open-source community for their continuous support and contributions.

---

For any inquiries or suggestions, please feel free to reach out!
