# Use a Debian base image
FROM debian:bullseye-slim

# Define working directory
WORKDIR /usr/src/app

# Copy your project files into the docker image
COPY . .

# Install necessary packages and clean up
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    make \
    gcc \
    gcc-aarch64-linux-gnu \
    binutils-aarch64-linux-gnu \
    qemu-system \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Default command to run
CMD ["make", "cleanall-run"]
