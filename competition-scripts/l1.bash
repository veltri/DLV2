#!/bin/bash

PIPE=/tmp/wasppipe_$$

./build/release/dlv2 --stdin --selector=$$ --silent | ./l2.bash $PIPE 


