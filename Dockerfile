FROM ubuntu:19.10

# Define arguments
ARG grimm=grimm-node-masternet.tar.gz 

# Install.
RUN \
  apt-get -y  update  && \
  mkdir -p  /home/grimm/node/ && \
  apt -y install wget  && \
  wget -P /home/grimm/node/  https://builds.grimmw.com/master/latest/Release/linux/$grimm  && \
  cd /home/grimm/node/  && tar -xvf $grimm && rm -rf $grimm

# Define volume & working directory.
WORKDIR /home/grimm/node/
VOLUME /home/grimm/node/

# Define default command.
EXPOSE 8100
CMD ["/home/grimm/node/grimm-node-masternet", "--peer=eu-node01.masternet.grimmw.com:8100,eu-node02.masternet.grimmw.com:8100,eu-node04.masternet.grimmw.com:8100,eu-node04.masternet.grimmw.com:8100"]
