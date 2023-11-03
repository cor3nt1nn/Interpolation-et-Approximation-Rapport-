#!/bin/bash
cd ..
(./approxi "results/text/41.txt") < data/41.txt
(./approxi "results/text/42.txt") < data/42.txt
(./approxi "results/text/43.txt") < data/43.txt
(./approxi "results/text/44.txt") < data/44.txt
(./approxi "results/text/45.txt") < data/45.txt
cd results
python3 graph.py