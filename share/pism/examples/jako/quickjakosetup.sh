#!/bin/bash

# Copyright (C) 2011-2012, 2015 the PISM authors

# executes all preprocessing actions appropriate to Jakobshavn case,
# with a particular selection of terminus rectangle

# assumes local presence of "regional-tools" script pism_regional.py
# scripts called here download large files if they are not already present
# result is file jako.nc

set -x

./preprocess.sh

python pism_regional.py -i gr1km.nc -o jakomask.nc -x 360,382 -y 1135,1176 -b 50

ncks -O -d x,299,918 -d y,970,1394 gr1km.nc jako.nc
# rename x and y to avoid type clash (float in gr1km.nc and double in jako.nc)
ncrename -O -v x,x1 -v y,y1 jako.nc jako.nc
ncks -A -d x,299,918 -d y,970,1394 jakomask.nc jako.nc

