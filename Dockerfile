FROM debian:bullseye-slim

# Update and install necessary tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-aarch64-linux-gnu \
    qemu-system \
    qemu-arch-extra \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

# Copy the project files to the working directory
COPY . .

# Build the project
RUN make

# Run QEMU with the created image when the container starts
CMD ["qemu-system-aarch64", "-M", "raspi3b", "-kernel", "kernel8.img", "-serial", "null", "-serial", "stdio"]
