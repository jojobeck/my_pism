#!/bin/bash

export PARAM_PPQ=0.5
export REGRIDFILE=g20km_10ka_hy.nc
PISM_DO=echo ./spinup.sh 4 paleo 25000 20 hybrid g20km_25ka_paleo.nc
