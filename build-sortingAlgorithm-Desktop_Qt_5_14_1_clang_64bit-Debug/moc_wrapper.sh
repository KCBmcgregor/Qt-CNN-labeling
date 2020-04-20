#!/bin/bash
DYLD_IMAGE_SUFFIX=_debug
export DYLD_IMAGE_SUFFIX
exec /Users/RoshniShah/Qt/5.14.1/clang_64/bin/moc "$@"
