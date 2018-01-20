#!/usr/bin/env bash
amounts=(1 10 100 1000 10000 100000 1000000 10000000 100000000 1000000000)

for i in ${amounts[@]}
    do
        ./cmake-build-debug/IRSPIMI.exe ./Wikipedia/enwiki-20170820-pages-articles.xml $i >> SPIMI${i}.txt
        ./cmake-build-debug/IRBSBI.exe ./Wikipedia/enwiki-20170820-pages-articles.xml $i >> BSBI${i}.txt
        rm -rf SPIMI
        rm -rf bsbi
    done