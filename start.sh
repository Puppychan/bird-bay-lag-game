#!/bin/bash

# Start QEMU here (modify as needed for your QEMU command)
qemu-system-aarch64 -M raspi3b -kernel kernel8.img -display vnc=:0 -serial stdio &

# Set up VNC and noVNC
Xvfb :0 -screen 0 1024x768x24 &
fluxbox -display :0.0 &
x11vnc -display :0.0 -forever -usepw -create &
novnc --vnc localhost:5900

# Keep the script running
tail -f /dev/null
