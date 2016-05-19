#!/usr/bin/python

from config import *
from display import Display
import os, sys

from PIL import Image

#from xmlrpc.server import SimpleXMLRPCServer
from SimpleXMLRPCServer import SimpleXMLRPCServer

server = SimpleXMLRPCServer(("localhost", 9090))

disp = Display(RSTPIN, 1, 0x3d)
disp.SelectFont(FONT)

disp.PutTextCenter("Display ready")
disp.Show()

def displayTextCentered(text):
	try:
		disp.Clear()
		disp.PutTextCenter(text)
		disp.Show()
		return (True, "")
	except Exception as e:
		return (False, e.message)
	
def displayImageWithText(imagename, text):
	try:
		disp.Clear()
	
		try:
			if not imagename.endswith(IMAGEEXTENSION):
				imagename = imagename + "." + IMAGEEXTENSION
				
			if not os.path.exists(IMAGEDIR + "/" + imagename):
				raise Exception("No such image " + imagename)
			
			image = Image.open(IMAGEDIR + "/" + imagename)
			disp.PutImageCenteredOnRow(3, image)
			disp.PutText(10,50, text)
			
			disp.Show()
			
		except Exception as e2:
			sys.stderr.write(e2.message + "\n")
			disp.PutTextCenter(text)
			disp.Show()
			
			raise e2

		return (True, "")
	except Exception as e:
		return (False, e.message)

server.register_function(displayTextCentered)
server.register_function(displayImageWithText)

server.serve_forever()