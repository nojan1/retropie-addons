#!/bin/sh

if [ ! -f ./install.sh ]; then
	echo "Please run script from the retropie-addons directory" 
	exit 1
fi

BASEPATH=$(pwd)

if [ -f /opt/DisplayDaemon/config.py ]; then
	echo "Backing up old display daemon config file. It will be restored"
	mv /opt/DisplayDaemon/config.py config.backup
fi

cp -r root/* /
[ -f config.backup ] && mv config.backup /opt/DisplayDaemon/config.py

patch -d / -b -N -p0 -i $BASEPATH/patches/*.patch
