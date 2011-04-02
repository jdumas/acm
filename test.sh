#!/bin/bash

PROGRAM=${1%.cpp}
INPUT=${2:-input}

make $PROGRAM
./$PROGRAM < $INPUT
