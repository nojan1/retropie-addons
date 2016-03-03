import math
import time

import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw

class Display:
	def __init__(self, RST):
		self.disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)
		
		self.buffer = Image.new('1', (self.disp.width, self.disp.height))
		self.draw = ImageDraw.Draw(self.buffer)
		
		#Clean the display
		self.disp.begin()
		#self.disp.clear()
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
		
	def PutImage(self, x, y, image):
		if type(image) is str:
			image = Image.open(image).convert('1')
			
		self.buffer.paste(image, (x,y))
	
	def Clear(self):
		self.draw.rectangle((0, 0, self.disp.width, self.disp.height), outline=0, fill=0)
		
	def Show(self):
		self.disp.image(self.buffer)
		self.disp.display()