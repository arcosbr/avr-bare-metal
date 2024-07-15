#!/bin/bash

# Default values
port='/dev/ttyACM0'
mcu='atmega328p'
programmer='arduino'
hexfile='build/release/firmware.hex'

# Usage function
usage() {
    echo "Usage: $0 [-P port] [-m mcu] [-c programmer] [-b hexfile]"
    echo "  -P port       Specify the serial port (default: /dev/ttyACM0)"
    echo "  -m mcu        Specify the MCU type (default: atmega328p)"
    echo "  -c programmer Specify the programmer type (default: arduino)"
    echo "  -b hexfile    Specify the path to the hex file (default: build/release/firmware.hex)"
    exit 1
}

# Parse command line options
while getopts "P:m:c:b:h" flag; do
    case "${flag}" in
        P) port=${OPTARG};;
        m) mcu=${OPTARG};;
        c) programmer=${OPTARG};;
        b) hexfile=${OPTARG};;
        h) usage;;
        *) usage;;
    esac
done

# Check if the hex file exists
if [ ! -f "$hexfile" ]; then
    echo "Error: Hex file '$hexfile' not found!"
    exit 1
fi

# Execute avrdude command
if ! avrdude -v -p $mcu -c $programmer -P $port -U flash:w:$hexfile; then
    echo "Error: avrdude failed to program the device!"
    exit 1
fi

echo "Programming successful!"
