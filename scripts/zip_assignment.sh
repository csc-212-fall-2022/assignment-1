#!/usr/bin/env bash

usage() {
    cat <<EOM
    Usage:
    $(basename $0) YOUR_NAME
EOM
    exit 0
}

[ -z $1 ] && { usage; }
NAME=$1

# https://stackoverflow.com/a/246128
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ASSIGNMENT_DIR=$(dirname "$SCRIPT_DIR")

find . -maxdepth 1 -not -name '.*' -not -name build -not -name cmake-build-debug -print | zip -r "${NAME}.zip" -@
