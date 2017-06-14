# ReadME

## Trabalho 2 de Técnicas de programação 

### 1 Objetivo 
 <p>
 Aprender e trabalhar com a linguagem C++, implementando e aplicando conceitos ensinados em sala, incluindo detecção facial, banco de dados e manipulação do GitHub.
 </p>
 
### 1.1 Descrição 
#### Sistema de controle de acesso
<p>
Simular um sistema para ser utilizado no Laboratório de Informática (LINF) da Universidade de Brasília que faz o controle de acesso, modelando por cadastramento, tipo de usuário, detecção facial e reservas.
</p><br />

## Índice
   
   [Requisitos](###2requisitos)<br />
   [MySQL](#MySQL)


<br />
### 2 Requisitos 

 * Compilador g++
 * Editor de texto
 * Biblioteca de processamento de imagens
 * Ferramenta de versionamento
 * Framework para criação de interface gráfica
 * Banco de dados
 
 #### 2.1 Utilizado 
 
 * Terminal linux
 * Compilador g++ Ubuntu 6.2.0-5ubuntu12 20161005
 * Sublime Text
 * GitHub
 * OpenCV
 * Qt Creator
 * MySQL

 ### 2.3 Instalações 

 #### Compilador g++ 

```
$ sudo apt-get install g++
```

#### Sublime Text 

```
$ sudo add-apt-repository ppa:webupd8team/sublime-text-3
$ sudo apt-get update
$ sudo apt-get install sublime-text-installer
```

#### GitHub 

```
$ sudo apt-get install git
```
#### OpenCV 
<p>
Crie um arquivo chamado install_opencv.sh. Você pode utilizar qualquer editor para isso;<br />
Copie o seguinte trecho para dentro do arquivo e salve. Lembre-se de salvar com extensão .sh:

```
#!/bin/bash
 
echo "Installing OpenCV 2.4.9"
sudo apt-get -y remove ffmpeg x264 libx264-dev
 
echo "Installing Dependenices"
sudo apt-get -y install libopencv-dev
sudo apt-get -y install build-essential checkinstall cmake pkg-config yasm
sudo apt-get -y install libtiff4-dev libjpeg-dev libjasper-dev
sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev
sudo apt-get -y install python-dev python-numpy
sudo apt-get -y install libtbb-dev
sudo apt-get -y install libqt4-dev libgtk2.0-dev
sudo apt-get -y install libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev
sudo apt-get -y install x264 v4l-utils ffmpeg
sudo apt-get -y install libgtk2.0-dev unzip
 
cd /opt
echo "Downloading OpenCV 2.4.11"
wget -O opencv-2.4.11.zip https://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.11/opencv-2.4.11.zip/download
echo "Installing OpenCV 2.4.11"
unzip opencv-2.4.11.zip
cd opencv-2.4.11
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
make -j4
sudo make install
sudo sh -c 'echo "/usr/local/lib" &gt; /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
echo "OpenCV 2.4.11 ready to be used"

```
Agora, vamos dar permissão de execução para o arquivo:

```
$ sudo chmod +x install_opencv.sh

```
Por último, vamos executar o arquivo de instalação.

```

$ ./install_opencv.sh

```
#### Qt Creator

[Passo-a-passo](https://wiki.qt.io/Install_Qt_5_on_Ubuntu)

## MySQL

```
$ sudo apt-get intall mysql-server mysql-client
```
