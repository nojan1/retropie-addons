import math
import time
import sys

import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw

class Display:
	def __init__(self, RST, BUS, ADDR):
		self.disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST, i2c_bus=BUS, i2c_address=ADDR)
		
		self.buffer = Image.new('1', (self.disp.width, self.disp.height))
		self.draw = ImageDraw.Draw(self.buffer)
		
		#Clean the display
		self.disp.begin()
		self.disp.clear()
		self.disp.display()
	
	def SelectFont(self, font = None):
		if font == None:
			self.font = ImageFont.load_default()
		else:
			self.font = ImageFont.truetype(font)
	
	def PutText(self, x, y, text):
		if not self.font:
			raise Exception("Font not set")
			
		self.draw.text((x, y), text, font=self.font, fill=255)
	
	def PutTextCenter(self, text):
		if not self.font:
			raise Exception("Font not set")

		size = self.font.getsize(text)

		x = (self.disp.width - size[0]) / 2
		y = (self.disp.height - size[1]) / 2

		self.draw.text((x, y), text, font=self.font, fill=255)
		
	def PutImageCenteredOnRow(self, y, image):
		targetWidth = 100
		if image.size[0] > targetWidth:
			ratio = targetWidth / image.size[0]
			image = image.resize((targetWidth, image.size[1] * ratio))
			
		x = (self.disp.width / 2) - (image.size[0] / 2)
		
		self.buffer.paste(image, (x,y))
		
	def PutImage(self, x, y, image):
		if type(image) is str:
			image = Image.open(image).convert('1')
			
		self.buffer.paste(image, (x,y))
	
	def Clear(self):
		self.draw.rectangle((0, 0, self.disp.width, self.disp.height), outline=0, fill=0)
		
	def Show(self):
		sys.stderr.write("Redrawing display \n")
		self.disp.image(self.buffer)
		self.disp.display()