#!/bin/sh

cd $1
cp -r root/* / 

patchfiles=$(patches/*.patch)
cd / && patch -b -N -p0 -i $patchfiles