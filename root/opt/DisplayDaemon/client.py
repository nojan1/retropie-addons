#!/usr/bin/python

import xmlrpc.client
import sys

if len(sys.argv) < 2:
    sys.stderr.write("Error: not enough argumets\n")
    sys.exit(1)

s = xmlrpc.client.ServerProxy('http://localhost:9090')

if len(sys.argv) == 2:
    result = s.displayTextCentered(sys.argv[1])
elif len(sys.argv) == 3:
    result = s.displayImageWithText(sys.argv[1], sys.argv[2])

if result[0]:
    sys.exit(0)
else:
    sys.exit(1)
    sys.stderr.write(result[1] + "\n")
