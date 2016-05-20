#!/bin/sh

set -e

./server/server& ./client/client.bin "127.0.0.1"
