#!/bin/bash

echo "Moving recorded audio files..."

RECORD_DIR="/var/spool/asterisk"
STORE_DIR="/home/nextrad/Documents/Audio/output"

for i in "$RECORD_DIR"/*.wav
do
	echo "${i}"
	mv "${i}" "$STORE_DIR"
done

echo "Removing file privileges..."

for i in "$STORE_DIR"/*.wav
do
	chmod 777 "${i}" 
done

echo "Audio files moved to $STORE_DIR"




