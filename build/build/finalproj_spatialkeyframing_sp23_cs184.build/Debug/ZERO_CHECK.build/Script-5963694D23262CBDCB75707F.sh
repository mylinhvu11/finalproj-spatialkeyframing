#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build
  make -f /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build
  make -f /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build
  make -f /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build
  make -f /Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/build/CMakeScripts/ReRunCMake.make
fi

