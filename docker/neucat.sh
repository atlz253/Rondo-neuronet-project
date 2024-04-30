#!/bin/bash

if [[ $GENERATE_REPORT = "true" ]]; then
  GENERATE_REPORT="--generate-report"
else
  GENERATE_REPORT=""
fi

if [[ $NO_WEIGHTS_SAVE = "true" ]]; then
  NO_WEIGHTS_SAVE="--no-weights-save"
else
  NO_WEIGHTS_SAVE=""
fi

if [[ $NO_DATASET_SHUFFLE = "true" ]]; then
  NO_DATASET_SHUFFLE="--no-dataset-shuffle"
else
  NO_DATASET_SHUFFLE=""
fi

if [ -f /input_weights.json ]; then
  WEIGHTS="--weights input_weights.json"
else
  WEIGHTS=""
fi

if [ -f /test_selection.json ]; then
  TEST_SELECTION="--test-selection test_selection.json"
else
  TEST_SELECTION=""
fi

./neucat --input-selection input_selection.json  --learning-rate $LEARNING_RATE --epochs-count $EPOCHS_COUNT --first-layer-neurons-count $FIRST_LAYER_NEURONS_COUNT $TEST_SELECTION $WEIGHTS $GENERATE_REPORT $NO_WEIGHTS_SAVE $NO_DATASET_SHUFFLE

if [ -f /weights.json ]; then
  mv /weights.json /result/weights.json
fi

if [ -f /report.bson ]; then
  mv /report.bson /result/report.bson
fi