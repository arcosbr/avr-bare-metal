import os

# Add toolchain directory to PATH
toolchain_path = "C:/Tools/avr-gcc-toolchain/bin"
os.environ["PATH"] = os.environ["PATH"] + ";" + toolchain_path
