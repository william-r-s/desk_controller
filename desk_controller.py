#!/usr/bin/env python3
# Send a message over serial port to standing desk controller every second that
# desktop is active (lock screen is not active)
import subprocess
import traceback
from time import sleep

import serial

import termios

sleep(1)
ser = None
try:
    while True:
        completed_process = subprocess.run(["cinnamon-screensaver-command", "-t"],
                                           stdout=subprocess.PIPE)
        if (completed_process.stdout.strip()) == b'The screensaver is not currently active.':

            if ser is None:
                try:
                    ser = serial.Serial('/dev/ttyACM0', 9600)
                except serial.serialutil.SerialException:
                    traceback.print_exc()

            if ser is not None:
                try:
                    ser.reset_output_buffer()
                    ser.write(bytearray([42]))
                except (termios.error, serial.serialutil.SerialException):
                    traceback.print_exc()
                    if ser is not None:
                        ser.close()
                    ser = None

        sleep(1)
finally:
    if ser is not None:
        ser.close()
