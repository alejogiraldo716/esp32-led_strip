| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 | Linux |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | -------- | -------- | -------- | ----- |
## Project Brief

## Brief Description

This project utilizes an ESP32 microcontroller to control a 30-LED strip. The ESP32 generates various patterns to display on the LED strip, showcasing different lighting effects and animations. The project is built using the ESP-IDF framework and includes source files for the main application and LED strip control.


## Prerequisites

Before you begin, ensure you have met the following requirements:

- **ESP-IDF**: Install the ESP-IDF framework. Follow the [official installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).
- **Python**: Ensure you have Python installed. You can download it from [here](https://www.python.org/downloads/).
- **CMake**: Install CMake, which is required for building the project. You can download it from [here](https://cmake.org/download/).

Make sure all the above tools are added to your system's PATH.

## Folder contents

The project **esp-led_stip** contains one source file in C language [main.c](main/src/main.c). The file is located in folder [main/src/](main/src/).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.
```
├── CMakeLists.txt      # Root CMake file
├── main                # Folder: Main application directory
│ ├── src               # Folder: Source files
│ │ ├── main.c              # Main application file
│ │ ├── led_strip.c         # LED strip - C file
│ │ └── CMakeLists.txt      # CMake file for the src directory
│ └── inc               # Folder: Header files
│   └── led_strip.h         # Header file for LED strip 
└── README.md # This is the file you are currently reading
```


For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Build project
Build the project by using the following command:
`idf.py build`


## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs. (change PORT to "/dev/tty**x**" or "COM**x**" --> x = the port created by the host)
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

## Technical support and feedback

Please use the following feedback channels:

* For technical queries, go to the [esp32.com](https://esp32.com/) forum
* For a feature request or bug report, create a [GitHub issue](https://github.com/alejogiraldo716/esp32-led_strip/issues)

We will get back to you as soon as possible.

## Authors

Currently (`20240731`) the project is maintain by :
- **Alejandro Giraldo Martinez** alejo.giraldo716@gmail.com - Alejo



