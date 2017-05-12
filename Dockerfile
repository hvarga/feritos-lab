# Base image for building Yocto images
FROM ubuntu:16.04

LABEL maintainer "hrvoje.varga@sartura.hr"
LABEL build "sudo docker build -t yocto-image-builder ."
LABEL run "sudo docker run -it --rm yocto-image-builder"

# Yocto's depends
RUN apt-get -qq --yes update && \
    apt-get -qq --yes install gawk wget git-core diffstat unzip texinfo gcc-multilib \
    build-essential chrpath socat cpio python python3 python3-pip python-pexpect vim locales

# Set the locale
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# Replace 1000 with builder user and group id
RUN export uid=1000 gid=1000 && \
    mkdir -p /home/builder && \
    mkdir -p /etc/sudoers.d && \
    echo "builder:x:${uid}:${gid}:Builder,,,:/home/builder:/bin/bash" >> /etc/passwd && \
    echo "builder:x:${uid}:" >> /etc/group && \
    echo "builder ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/builder && \
    chmod 0440 /etc/sudoers.d/builder && \
    chown ${uid}:${gid} -R /home/builder

# Switch to builder user and configure its environment
USER builder
ENV HOME /home/builder
WORKDIR /home/builder

# Set bash as the entrypoint
ENTRYPOINT ["bash"]
