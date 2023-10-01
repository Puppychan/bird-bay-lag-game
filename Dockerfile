# Using a base image which includes necessary tools and libraries
FROM debian:buster-slim

# Updating and Installing necessary packages
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    build-essential \
    gcc-aarch64-linux-gnu \
    binutils-aarch64-linux-gnu \
    qemu-system-arm \
    qemu-system-x86 \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# Set up environment variables for cross compilation
ENV CC=aarch64-linux-gnu-gcc
ENV LD=aarch64-linux-gnu-ld
ENV OBJCOPY=aarch64-linux-gnu-objcopy

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the contents of the current directory (on host) to the working directory (in container)
COPY . .

# Run the 'make test' command when the container starts
CMD ["make", "test"]
