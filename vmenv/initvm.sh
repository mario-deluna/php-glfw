sudo apt update && sudo apt -y upgrade
sudo apt install lsb-release ca-certificates apt-transport-https software-properties-common -y
sudo add-apt-repository ppa:ondrej/php
sudo apt update
sudo apt install php8.1 -y
sudo apt install php8.1-dev php8.1-mbstring -y
sudo apt install cmake -y

curl -LO https://phar.phpunit.de/phpunit-9.5.phar
sudo mv phpunit-9.5.phar /usr/bin/phpunit
chmod 777 /usr/bin/phpunit

php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php -r "if (hash_file('sha384', 'composer-setup.php') === '55ce33d7678c5a611085589f1f3ddf8b3c52d662cd01d4ba75c0ee0459970c2200a51f492d557530c71c15d8dba01eae') { echo 'Installer verified'; } else { echo 'Installer corrupt'; unlink('composer-setup.php'); } echo PHP_EOL;"
php composer-setup.php
php -r "unlink('composer-setup.php');"
sudo mv composer.phar /usr/bin/composer
chmod 777 composer

sudo apt-get update && sudo apt-get install -y php-dev build-essential cmake xvfb libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev gdb
cd vendor/glfw && cmake . -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=ON && sudo make install && sudo ldconfig && cd ../../
sudo phpize && ./configure --enable-glfw && make -j$(nproc)

sudo make install && grep -qxF 'extension=glfw.so' /etc/php/8.1/cli/php.ini || echo 'extension=glfw.so' >> /etc/php/8.1/cli/php.ini