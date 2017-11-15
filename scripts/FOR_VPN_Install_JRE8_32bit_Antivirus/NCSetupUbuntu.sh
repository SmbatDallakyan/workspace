#!/bin/bash
#Download Java8u66 32 bit
mkdir /usr/java32
wget http://ftp.osuosl.org/pub/funtoo/distfiles/oracle-java/jre-8u144-linux-i586.tar.gz
tar -xvf jre-8u144-linux-i586.tar.gz -C /usr/java32

#update Java settings
update-alternatives --install /usr/bin/java java /usr/java32/jre1.8.0_144/bin/java 10
ln -s /usr/bin/update-alternatives /usr/sbin/
dpkg --add-architecture i386

#install required 32 bit libs
apt-get update -y
apt-get install libstdc++6:i386 lib32z1 lib32ncurses5 lib32bz2-1.0 libxext6:i386 libxrender1:i386 libxtst6:i386 libxi6:i386 -y

#install Java8u66 64 bit
apt-add-repository ppa:webupd8team/java
apt-get update
apt-get install oracle-java8-installer -y
