#!/usr/bin/env python3
import pystray
from PIL import Image, ImageDraw

icon = pystray.Icon('test name')

# Generate an image
width = 32
height = 32
color1 = 128
color2 = 0
image = Image.new('RGB', (width, height), color1)
dc = ImageDraw.Draw(image)
dc.rectangle((width // 2, 0, width, height // 2), fill=color2)
dc.rectangle((0, height // 2, width // 2, height), fill=color2)

icon.icon = image


def setup(icon):
    icon.visible = True
    icon.icon = image


icon.run(setup)
icon.icon = image
