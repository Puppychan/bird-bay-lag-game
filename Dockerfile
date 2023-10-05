FROM ubuntu:20.04

# Environment variable to prevent prompts
ENV DEBIAN_FRONTEND=noninteractive 

# Update and install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    wget \
    xz-utils \
    make \
    git \
    libgtk-3-dev \
    ca-certificates \
    x11vnc \
    xvfb \
    fluxbox \
    net-tools \
    python3 \
    python3-numpy \
    python3-websockify \
    && rm -rf /var/lib/apt/lists/*

# Install NoVNC from the GitHub repository
WORKDIR /opt
RUN git clone https://github.com/novnc/noVNC.git && \
    cd noVNC/utils && \
    git clone https://github.com/novnc/websockify.git

# Install the aarch64-none-elf-gcc compiler
WORKDIR /opt
RUN wget -qO- "https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar.xz" | tar xJ && \
    echo 'export PATH=/opt/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin:$PATH' >> ~/.bashrc

# Compile QEMU from source (this step can take a while)
WORKDIR /opt
RUN git clone https://git.qemu.org/git/qemu.git && \
    cd qemu && \
    git checkout tags/v6.2.0 && \
    ./configure --target-list=aarch64-softmmu && \
    make -j$(nproc) && \
    make install

# Copy your project into the Docker image
WORKDIR /project
COPY . .

# Start the QEMU, VNC, noVNC stack when running the container
COPY start.sh /start.sh
RUN chmod +x /start.sh
CMD ["/start.sh"]
