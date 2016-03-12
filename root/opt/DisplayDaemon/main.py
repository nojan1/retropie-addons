#!/usr/bin/python

from config import *
from display import Display
import os, sys

#from xmlrpc.server import SimpleXMLRPCServer
from SimpleXMLRPCServer import SimpleXMLRPCServer

server = SimpleXMLRPCServer(("localhost", 9090))

disp = Display(RSTPIN, 1, 0x3d)
disp.SelectFont(FONT)

disp.PutTextCenter("Display ready")

def displayTextCentered(text):
        try:
                disp.PutTextCenter(text)
                return (True, "")
        except Exception as e:
                return (False, e.message)
        
def displayImageWithText(imagename, text):
        try:
                return (True, "")
        except Exception as e:
                return (False, e.message)

server.register_function(displayTextCentered)
server.register_function(displayImageWithText)

server.serve_forever()
