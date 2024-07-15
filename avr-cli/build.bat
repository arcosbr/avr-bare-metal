@echo off
arduino-cli compile --fqbn arduino:avr:uno hello.ino --output-dir build

rem Apaga arquivo não utilizado posteiormente
del build\hello.ino.eep

rem Renomeia os arquivos de build
rename build\hello.ino.elf build\hello.elf
rename build\hello.ino.hex build\hello.hex
rename build\hello.ino.with_bootloader.bin build\hello_with_bootloader.bin
rename build\hello.ino.with_bootloader.hex build\hello_with_bootloader.hex
