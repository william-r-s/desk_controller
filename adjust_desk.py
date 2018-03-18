#!/usr/bin/env python3
# Send a message over serial port to standing desk controller
import termios
import traceback
from time import sleep

import serial

path = '/dev/ttyACM0'

reset_arduino = False
# Disable reset after hangup
with open(path) as f:
    attrs = termios.tcgetattr(f)
    if attrs[2] & termios.HUPCL:
        reset_arduino = True
        attrs[2] = attrs[2] & ~termios.HUPCL
        termios.tcsetattr(f, termios.TCSAFLUSH, attrs)

if reset_arduino:
    try:
        ser = serial.Serial(path, 9600, timeout=5)
        ser.read()
    except (serial.serialutil.SerialException, termios.error):
        traceback.print_exc()
    finally:
        if ser is not None:
            ser.close()

try:
    ser = serial.Serial(path, 9600)
    ser.reset_output_buffer()
    # ser.read(1)
    ser.write(bytearray([42]))
except (serial.serialutil.SerialException, termios.error):
    traceback.print_exc()
finally:
    if ser is not None:
        ser.close()
