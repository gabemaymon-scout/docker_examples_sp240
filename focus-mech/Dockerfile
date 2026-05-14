FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# =========================
# System dependencies
# =========================
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    g++ \
    cmake \
    pkg-config \
    python3 \
    python3-pip \
    python-is-python3 \
    iproute2 \
    net-tools \
    can-utils \
    libgpiod-dev \
    && rm -rf /var/lib/apt/lists/*

# =========================
# Workspace
# =========================
WORKDIR /workspace

# Copy source
COPY FocusMech.cpp /workspace/

# =========================
# Build application
# =========================
RUN g++ FocusMech.cpp -o FocusMech \
    -lgpiod \
    -O2

# =========================
# Runtime permissions note
# =========================
# (GPIO + UART access usually requires privileged container)

# =========================
# Run binary by default
# =========================
CMD ["/workspace/FocusMech"]
