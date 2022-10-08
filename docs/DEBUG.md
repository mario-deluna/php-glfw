# Debug notes

These are just some personal notes of things and command i need during debugging:

**extension build debug**

```
sudo phpize && ./configure --enable-glfw --enable-debug
sudo make install
```

**php from source debug on my mac**

```
export PATH="/usr/local/opt/bison/bin:$PATH"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/openssl@1.1/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/krb5/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/libffi/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/libxml2/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/libxslt/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/zlib/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/icu4c/lib/pkgconfig"

./configure --enable-debug --without-iconv --with-config-file-path=/usr/local/etc/php/8.1/ --disable-all --enable-mbstring  --enable-cli --enable-opcache --disable-cgi --enable-opcache --with-gmp
```
