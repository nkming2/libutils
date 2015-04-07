#!/bin/bash
set -ev
if [ "${LU_BUILD}" = "DEBUG" ]; then
	bin/libutils-test-d
else
	bin/libutils-test-r
fi
