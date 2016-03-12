#!/bin/sh

#cd $1

mv /opt/DisplayDaemon/config.py config.backup
cp -r root/* /
mv config.backup /opt/DisplayDaemon/config.py
