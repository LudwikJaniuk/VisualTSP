#!/bin/sh

set -e

printf "Building client... " 
cd client
sh build.sh
printf "Done.\n"

printf "Building server... " 
cd ../server
sh build.sh
printf "Done.\n"
