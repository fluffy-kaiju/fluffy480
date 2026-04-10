from archlinux:base
    LABEL org.opencontainers.image.authors="Fluffy Kaiju <fluffy@fluffy-laptop>"


run pacman -Syu --noconfirm sudo zsh python3 ccls git && \
    pacman -Scc --noconfirm

run useradd -m -s /bin/zsh dev
workdir /home/dev/
run chown -R dev:dev /home/dev/
RUN echo "dev ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

user vscode
add --chown=dev:dev https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py /tmp/get-platformio.py

user dev
run python3 /tmp/get-platformio.py
env PATH="/home/dev/.platformio/penv/bin/:${PATH}"

run sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
