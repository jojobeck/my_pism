#!/bin/bash

NN=4
DURATION=1000
START=g10km_gridseq.nc
for PPQ in 0.1 0.5 1.0 ; do
  for SIAE in 1 3 6 ; do
     export PISM_DO=echo REGRIDFILE=$START PARAM_PPQ=$PPQ PARAM_SIAE=$SIAE
     ./spinup.sh $NN const $DURATION 10 hybrid p10km_${PPQ}_${SIAE}.nc &> p10km_${PPQ}_${SIAE}.sh
  done
done
