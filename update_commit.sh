#!/bin/sh
set -eou pipefail
./commit.sh | grep -q $(./clib_commit.sh) || { echo -e "sed 's/$(./clib_commit.sh)/$(./commit.sh)/g' -i clib.json"; }
