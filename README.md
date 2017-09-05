# TravisTest
Small repository linked with Travis CI to experiment with continuous
integration.

## What is it?
1. `cannon.cpp`: C++ implementation using GSL to compupute the trajectory
    of artillery taking air drag and density into account.  Don't use
    this for real world applications, please.
1. `Makefile`: make file to build and run the application.
1. `.travis.yml`: Travis CI configuration file.