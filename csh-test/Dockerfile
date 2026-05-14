FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /app

# Explicitly install the specific system runtimes requested by the csh binary
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        libpython3.12 \
        libyaml-0-2 \
        libcurl4t64 \
        libzmq5 \
        can-utils && \
    rm -rf /var/lib/apt/lists/*

# Copy and install your custom debian package
COPY si-csh_24.04_amd64_2.10.3-0-g872b858.deb .

RUN apt-get update && \
    apt-get install -y --no-install-recommends ./si-csh_24.04_amd64_2.10.3-0-g872b858.deb && \
    rm -rf /var/lib/apt/lists/* si-csh_24.04_amd64_2.10.3-0-g872b858.deb

CMD ["csh"]
