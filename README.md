# Advent of Code 2024 in C

# How to run

choose compiler in Makefile(CC). By default I use tiny c compiler (tcc).

`make` to compile. Build artefacts will be in **build** folder

`make run` to compile and run.

# Commands

```
valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./build/advent

```


# ok makefile sources:

https://stackoverflow.com/questions/75728275/multiple-definition-of-main-first-defined-here-when-using-cunit-tests




# day 16


- path can be longer but with fewer turns
- one path can be part of other path in begining/end/middle
- removing unsuccessful parts can lead to removing succesful cells
