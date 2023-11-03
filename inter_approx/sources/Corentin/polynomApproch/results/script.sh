#!/bin/bash
cd ..
(./neville "results/text/41.txt") < data/41.txt
(./neville "results/text/42.txt") < data/42.txt
(./neville "results/text/43.txt") < data/43.txt
cd results
python3 graph.py