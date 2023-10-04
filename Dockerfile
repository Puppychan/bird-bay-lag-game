FROM multiarch/qemu-user-static:x86_64-aarch64 as qemu

FROM ubuntu:20.04

# Copy QEMU binary from qemu image
COPY --from=qemu /usr/bin/qemu-aarch64-static /usr/bin

# Install other necessary tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    make \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*


# Clean up unnecessary packages and reduce image size
RUN apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* qemu-6.2.0 qemu-6.2.0.tar.xz

# Copy your source code into the image
COPY ./src /src
COPY ./data /data
COPY ./gcclib /gcclib
COPY Makefile /Makefile

# Define the working directory
WORKDIR /

# Set default behavior when running the container without arguments
CMD ["make", "cleanall-run"]
