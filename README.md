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

# day 19
```
(0 1 2 3) (0 1 2) (0 1) (0) = 9
(0 1 2) (0 1) (1) = 4

3 * ( 2 * x )
2 * ( 3 * x )
2 * ( 4 * x )
1 * ()


3 * 2 + 2 * 3
2* 3

4*3*2*1 
overlapping : - (3*2 + 2*1) + (4 * 2)
compensate: + 1


4*(3-)*(2-1)*(1)
=9





a b c
ab b c
a bc c
ab bc c (no)
abc c
abc bc c (no)
=4
```


```
(012) (012) (01) (0)
abcd

ab: 2*2
abc: 2*2+1
bc: 1
bcd: 1

total: 18
overlapping: 11
result: 
7
```
