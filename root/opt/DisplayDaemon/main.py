#!/usr/bin/python

from config import *
from display import Display
import os

disp = Display(RSTPIN)
disp.SelectFont(FONT)

if not os.path.exists(PIPEPATH):
	os.mkfifo(PIPEPATH)
	
pipe = open(PIPEPATH, "r")
	
while True:
	try:
		line = pipe.readline()[-1]
		parts = line.split(" ")
		if len(parts) == 0:
			continue
			
		if parts[0] == "gamestart":
			disp.Clear()
			disp.SetText(10, 10, parts[1] + " was just launched")
		elif parts[0] == "gamestop":
			displ.SetText(10, 10, "In Menu")
			disp.Clear()
		
		disp.Show()
		
	except (KeyboardInterrupt, SystemExit):
		break
	except:
		continue
	
