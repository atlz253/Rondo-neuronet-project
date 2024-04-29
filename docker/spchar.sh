#!/bin/bash

if [[ $SHOW_PRECENTAGE = "true" ]]; then
  SHOW_PRECENTAGE="--show-precentage"
else
  SHOW_PRECENTAGE=""
fi

./spchar image.png $SHOW_PRECENTAGE