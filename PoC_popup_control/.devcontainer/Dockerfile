FROM mcr.microsoft.com/devcontainers/cpp:2-debian13
    LABEL org.opencontainers.image.authors="Fluffy Kaiju <fluffy@fluffy-laptop>"

# Install python3-venv (Required for PlatformIO)
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends python3-venv ccls

ENV PATH="/home/vscode/.platformio/penv/bin/:${PATH}"

USER vscode
ADD --chown=vscode:vscode https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py /tmp/get-platformio.py

RUN python3 /tmp/get-platformio.py

