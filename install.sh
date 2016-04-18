#!/bin/sh

[ ! -f ./install.sh ] && (echo "Please run script from the retropie-addons directory"; exit 1)

mv /opt/DisplayDaemon/config.py config.backup
cp -r root/* /
mv config.backup /opt/DisplayDaemon/config.py

patchfiles=$(patches/*.patch)
cd / && patch -b -N -p0 -i $patchfiles
