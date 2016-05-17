#!/bin/sh

set -e

./server/server& ./client/client "127.0.0.1"
