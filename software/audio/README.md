## Setup

### bcm2835

````
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
cd bcm2835-1.xx
./configure
make
sudo make check
sudo make install
sudo ldconfig
````

### fdk-aac

````
wget -O fdk-aac.tar.gz https://github.com/mstorsjo/fdk-aac/tarball/master
tar xzvf fdk-aac.tar.gz
cd mstorsjo-fdk-aac**
autoreconf -fiv
./configure --prefix="$HOME" --disable-shared
make
make install
````

#### v2

Open `etc/apt/sources.list` and Add

````
deb http://www.deb-multimedia.org/ bullseye main non-free
````

````
wget https://www.deb-multimedia.org/pool/main/d/deb-multimedia-keyring/deb-multimedia-keyring_2016.8.1_all.deb
sudo dpkg -i deb-multimedia-keyring_2016.8.1_all.deb
sudo apt update
sudo apt-get install libfdk-aac-dev
````

### bluez-alsa

````
sudo apt-get install git automake build-essential libtool pkg-config
sudo apt-get install libasound2-dev libbluetooth-dev libdbus-1-dev libglib2.0-dev libsbc-dev


git clone https://github.com/Arkq/bluez-alsa.git
cd bluez-alsa

autoreconf --install --force
mkdir build && cd build
../configure --enable-aac --enable-ofono --enable-debug
make
sudo make install
````