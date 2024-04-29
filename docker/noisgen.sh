#!/bin/bash

if [[ $NO_SELECTION_JSON = "true" ]]; then
  NO_SELECTION_JSON="--no-selection-json"
else
  NO_SELECTION_JSON=""
fi

if [[ $NO_IMAGE_GENERATION = "true" ]]; then
  NO_IMAGE_GENERATION="--no-image-generation"
else
  NO_IMAGE_GENERATION=""
fi

if [[ $SEED != "" ]]; then
  SEED="--seed $SEED"
fi

if [[ $ITERATIONS != "" ]]; then
  ITERATIONS="--iterations $ITERATIONS"
fi

if [[ $PRECENTAGE != "" ]]; then
  PRECENTAGE="--precentage $PRECENTAGE"
fi

./noisgen --input /var/input --output /var/output $ITERATIONS $PRECENTAGE $SEED $NO_IMAGE_GENERATION $NO_SELECTION_JSON