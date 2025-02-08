FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential bison flex libncurses5-dev \
    libssl-dev wget gawk git diffstat unzip texinfo bc ccache util-linux \
    elfutils libelf-dev file rsync cpio \
    python3 python3-pip python3-setuptools \
    libtool autoconf automake pkg-config \
    libglib2.0-dev libpixman-1-dev

# Set up the working directory
WORKDIR /workspace

# Copy the repository contents into the container
COPY . .

# Create necessary directories
RUN mkdir -p /workspace/output/target/usr/libexec/

# Use cached directories
VOLUME /workspace/.buildroot-ccache
VOLUME /workspace/dl
VOLUME /workspace/output

# Build the image
RUN make clean && \
    make BR2_DEFCONFIG=proj/buildroot.config defconfig && \
    make -s V=0
