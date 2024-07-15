Claro, aqui está um `README.md` em Inglês para o seu repositório no GitHub:

```markdown
# AVR Bare Metal Projects

This repository contains a collection of bare-metal projects for testing purposes on various AVR microcontrollers. These projects are intended as drafts and examples for those interested in AVR programming without an operating system.

## Projects Overview

### 1. `avr-bare-mega`
This project is for the ATmega2560 microcontroller, using PlatformIO as the development environment.

### 2. `avr-bare-metal`
This project targets the ATmega328P and ATTiny85 microcontrollers, using a Makefile for building and flashing.

### 3. `arduino-cli`
A very simple project that uses the Arduino CLI to build and flash code to an Arduino Uno.

## Getting Started

### Prerequisites

Ensure you have the following tools installed based on the project you wish to work with:

- **avr-bare-mega**:
  - PlatformIO
- **avr-bare-metal**:
  - avr-gcc
  - avr-binutils
  - make
  - avrdude
- **arduino-cli**:
  - Arduino CLI

### Quick Start

#### avr-bare-mega

1. Clone the repository:

    ```sh
    git clone https://github.com/arcosbr/avr-bare-metal.git
    cd avr-bare-metal/avr-bare-mega
    ```

2. Build and upload the project using PlatformIO:

    ```sh
    platformio run --target upload
    ```

#### avr-bare-metal

1. Clone the repository:

    ```sh
    git clone https://github.com/arcosbr/avr-bare-metal.git
    cd avr-bare-metal/avr-bare-metal
    ```

2. Write your code in `main.c` and create additional source files as needed.

3. Build the project:

    ```sh
    make
    ```

4. Flash the firmware:

    ```sh
    ./scripts/flash.sh -P <port> -m <mcu> -c <programmer> -b build/release/firmware.hex
    ```

   Example:

    ```sh
    ./scripts/flash.sh -P /dev/ttyACM0 -m atmega328p -c arduino -b build/release/firmware.hex
    ```

#### arduino-cli

1. Clone the repository:

    ```sh
    git clone https://github.com/arcosbr/avr-bare-metal.git
    cd avr-bare-metal/avr-cli
    ```

2. Build and upload the project:

    ```sh
    build.bat
    ```

or

    ```sh
    arduino-cli compile --fqbn arduino:avr:uno hello.ino --output-dir build
    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno
    ```
