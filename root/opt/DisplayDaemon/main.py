#!/usr/bin/python

from config import *
from display import Display
import os, sys

disp = Display(RSTPIN, 1, 0x3d)
disp.SelectFont(FONT)

if not os.path.exists(PIPEPATH):
	os.mkfifo(PIPEPATH)
	
pipe = open(PIPEPATH, "r")

disp.PutTextCenter("Display ready")
disp.Show()
	
while True:
	try:
		line = pipe.readline()[-1]
		parts = line.split(" ")
		if len(parts) == 0:
			continue
			
		sys.stderr.write("Read line from fifo: " + line + "\n")
			
		if parts[0] == "gamestart":
			disp.Clear()
			disp.PutText(10, 10, parts[1] + " was just launched")
		elif parts[0] == "gamestop":
			disp.Clear()
			disp.PutText(10, 10, "In Menu")

		disp.Show()
		
	except (KeyboardInterrupt, SystemExit):
		break
	except Exception as e:
		sys.stderr.write("Exception: " + e.message + "\n")
		continue
	
