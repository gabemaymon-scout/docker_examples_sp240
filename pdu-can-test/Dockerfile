FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive

# Install Git, compiler toolchain, CMake, and SocketCAN libraries
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    libsocketcan-dev \
    can-utils \
    && rm -rf /var/lib/apt/lists/*

# Clone, build, and globally install libcsp from GitHub
WORKDIR /tmp-libcsp
RUN git clone https://github.com/spaceinventor/libcsp . \
    && mkdir build && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
             -DCSP_HAS_CAN_SOCKETCAN=ON \
             -DCSP_HAS_POSIX=ON .. \
    && make -j$(nproc) && make install \
    && ldconfig

# Establish the clean application directory
WORKDIR /app

# Copy your local C file and the newly modified CMakeLists.txt
COPY . .

# Compile your custom standalone project using the temporary driver directory
RUN mkdir build && cd build \
    && cmake .. \
    && make -j$(nproc)

# Clean up the temporary library source files after everything compiles successfully
RUN rm -rf /tmp-libcsp

# Set the entry working directory to the compiled binary location
WORKDIR /app/build
