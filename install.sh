#!/bin/bash

# Function to check if a command exists
command_exists () {
    type "$1" &> /dev/null ;
}

# Update package list
apt-get update

# Install make if not installed
if ! command_exists make ; then
    apt-get install -y make
fi

# Install gcc if not installed
if ! command_exists gcc ; then
    apt-get install -y gcc
fi

# Install gcc-aarch64-linux-gnu if not installed
if ! command_exists aarch64-linux-gnu-gcc ; then
    apt-get install -y gcc-aarch64-linux-gnu
fi

# Install binutils-aarch64-linux-gnu if not installed
if ! command_exists aarch64-linux-gnu-ld ; then
    apt-get install -y binutils-aarch64-linux-gnu
fi

# Install qemu-system if not installed
if ! command_exists qemu-system-aarch64 ; then
    apt-get install -y qemu-system
fi

# Clean up APT when done
apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
