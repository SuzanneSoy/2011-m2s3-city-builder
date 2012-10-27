Minimal requirements
====================

* `g++` et GNU `make` (paquet `build-essential`)
* `libsdl-dev`
* `libglew-dev`
* `freeglut3-dev`
* `libsdl-image1.2-dev`

The following command should install the required packages on ubuntu.

    sudo apt-get install build-essential libsdl-dev libglew-dev freeglut3-dev libsdl-image1.2-dev

How to run this program ?
=========================

    make

How to run the statistics ?
===========================

    mkdir -p png && make city && ./city > statistics.plt && pv statistics.plt | tail -n +2 | gnuplot
