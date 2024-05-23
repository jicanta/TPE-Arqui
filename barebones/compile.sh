#!/bin/bash
sudo docker start BIRSA
sudo docker exec -ti BIRSA make clean -C/root/Toolchain
sudo docker exec -ti BIRSA make clean -C/root/
sudo docker exec -ti BIRSA make -C/root/Toolchain
sudo docker exec -ti BIRSA make -C/root/
sudo docker stop BIRSA