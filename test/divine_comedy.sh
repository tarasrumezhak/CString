#!/bin/sh

echo 'WRITING DIVINA COMMEDIA'
for i in {1..400}; do cat ../test/divine_comedy.txt >> DIVINA_COMMEDIA.txt; done

echo 'OF SIZE '$(du -h DIVINA_COMMEDIA.txt | cut -f 1)

echo 'REVERSING IT'
time ./examples/example DIVINA_COMMEDIA.txt DIVINA_COMMEDIA_REVERSED.txt

echo 'REVERSED'
