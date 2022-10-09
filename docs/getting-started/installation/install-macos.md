<div class="grid cards" markdown>

-   :fontawesome-brands-linux:{ .lg .middle } __Install on Linux__

    ---

    [:octicons-arrow-right-24: Linux Installation](./install-linux.md)

-   :fontawesome-brands-windows:{ .lg .middle } __Install on Windows__

    ---

    [:octicons-arrow-right-24: Windows Installation](./install-windows.md)
</div>


# Installing PHP-GLFW on MacOS

To make the installation on MacOS as painless as possible we provide an installer script that in most scenarios installs the extension in a one liner. 

## Installer

Run the following command to download and execute the installer.<br>
**Having PHP installed locally is required!**

```
php -r "copy('https://raw.githubusercontent.com/mario-deluna/php-glfw/master/install/macos-installer.php', 'phpglfw-installer.php');" && sudo php phpglfw-installer.php
```

!!! success ""
    
    **Thats it**, if you see the text "Installation finished!" you should be ready to go!


## Manual installation

If you prefer a "manual" approach, ensure you have installed the `php-dev`, `git` and `cmake` packages. **They are required!**

Clone the repository:

```bash
git clone https://github.com/mario-deluna/php-glfw
cd php-glfw
```

Configure and build the extension

```bash
sudo phpize && ./configure --enable-glfw
sudo make install
```

make sure to add `glfw.so` in the `php.ini` file.

You can figure out the path to your php.ini file using:

```bash
php -i | grep php.ini
```

Edit that file using you favorite editor:

```bash
sudo vim /usr/local/etc/php/8.1/php.ini
```

And add the following line at the end of the file

```ini
extension="glfw.so"
```