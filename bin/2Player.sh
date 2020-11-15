#!/bin/bash
while true; do scp $1:~/1p.io 2p.io; scp 1p.io $1:~/2p.io; done