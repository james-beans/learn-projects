#!/usr/bin/env bash

n() { echo ""; }

compile() {
  # projects/bp.cpp
  clang++ -std=c++23 projects/bp.cpp -o dist/bp

  # projects/convertemp.cpp
  clang++ -std=c++23 projects/convertemp.cpp -o dist/convertemp

  # projects/gtn.cpp
  clang++ -std=c++23 projects/gtn.cpp -o dist/gtn

  # projects/hypotenuse.cpp
  clang++ -std=c++23 projects/hypotenuse.cpp -o dist/hypotenuse

  # projects/qg.cpp
  clang++ -std=c++23 projects/qg.cpp -o dist/qg

  # projects/rectangleloop.cpp
  clang++ -std=c++23 projects/rectangleloop.cpp -o dist/rectangleloop

  # projects/reg.cpp
  clang++ -std=c++23 projects/reg.cpp -o dist/reg

  # projects/rps.cpp
  clang++ -std=c++23 projects/rps.cpp -o dist/rps

  # projects/tcalc.cpp
  clang++ -std=c++23 projects/tcalc.cpp -o dist/tcalc

  # projects/ccv.cpp
  clang++ -std=c++23 projects/ccv.cpp -o dist/ccv

  # projects/ttt.cpp
  clang++ -std=c++23 projects/ttt.cpp -o dist/ttt

  n && echo "Compiled all programs." && n
}

main() {
  clear

  # Check if the 'dist' folder exists and then safely delete contents using find.
  if [ -d "dist" ]; then
    echo "Safely removing existing 'dist' directory contents..."
    # Recursively delete everything *inside* the 'dist' directory.
    # -mindepth 1 ensures we only target contents, not 'dist' itself.
    find dist -mindepth 1 -delete

    # Remove the now (hopefully) empty 'dist' directory using the safer rmdir.
    # The '|| true' ensures the script doesn't crash if rmdir fails (e.g., if files remain).
    rmdir dist 2>/dev/null || true
  fi

  n

  # Make the dist directory
  mkdir -p dist

  compile
}

main
