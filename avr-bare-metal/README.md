# AVR "Bare Metal" Programming

A getting started guide for bare-metal programming on an AVR microcontroller using the GNU Toolchain for learning purposes.

## Prerequisites

To get started, install the following toolchain components:
- `avr-gcc`
- `avr-binutils`
- `make`
- `avrdude`

## Quick Start

### 1. Get the files

Clone the repository:

```sh
git clone https://github.com/arcosbr/avr-bare-metal.git
```

### 2. Write your code

Write your code in `main.c` and create as many source files as needed. Compile your code with:

```sh
make
```

### 3. (Optional) Analyze it

Check the `build/memory.map` and `build/firmware.lst` files to ensure everything is as expected.

### 4. Flash it

Plug in your AVR Microcontroller with a bootloader and execute:

```sh
./scripts/flash.sh -P <port> -m <mcu> -c <programmer> -b <path_to_hex>
```

Example:

```sh
./scripts/flash.sh -P /dev/ttyACM0 -m atmega328p -c arduino -b build/release/firmware.hex
```
