FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# =========================
# Dependencies
# =========================
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    gcc \
    g++ \
    make \
    cmake \
    pkg-config \
    python3 \
    python3-pip \
    python3-dev \
    pipx \
    libcurl4-openssl-dev \
    libsocketcan-dev \
    can-utils \
    libzmq3-dev \
    libyaml-dev \
    libelf-dev \
    libbsd-dev \
    fonts-powerline \
    && rm -rf /var/lib/apt/lists/*

# =========================
# Install meson + ninja
# =========================
RUN pipx install meson && \
    apt-get update && apt-get install -y ninja-build

ENV PATH="/root/.local/bin:${PATH}"

# =========================
# Clone CSH
# =========================
WORKDIR /opt

RUN git clone --recurse-submodules \
    https://github.com/spaceinventor/csh.git

WORKDIR /opt/csh

# =========================
# Build + install
# =========================
RUN ./configure && ./install

# =========================
# Default shell
# =========================
CMD ["csh"]