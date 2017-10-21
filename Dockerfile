FROM library/gcc:7

RUN apt-get update 
RUN apt-get install -y build-essential git cmake cmake-curses-gui xorg-dev libgl1-mesa-dev libglu-dev
#RUN apt-get install -y libpng-dev libcurl4-openssl-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev \
# libgtk2.0-dev libasound-dev libpulse-dev libflac-dev libdumb1-dev
#RUN apt-get install -y exuberant-ctags dvi2ps dvipdfmx latex2html pandoc

RUN git clone https://github.com/liballeg/allegro5.git

WORKDIR "/allegro5"

RUN git checkout 5.0

RUN mkdir build

WORKDIR "/allegro5/build"

RUN cmake ..

RUN make

RUN make install
