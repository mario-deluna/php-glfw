
<div class="grid cards" markdown>

-   :material-apple:{ .lg .middle } __Install on MacOS__

    ---

    [:octicons-arrow-right-24: MacOS Installation](./install-macos.md)

-   :fontawesome-brands-windows:{ .lg .middle } __Install on Windows__

    ---

    [:octicons-arrow-right-24: Windows Installation](./install-windows.md)
</div>


# Installing PHP-GLFW on Linux

We currently do not have a installer script like on MacOS but the "manual" installation should be straight forward for you linux users.

## Manual installation

Ensure you have installed the required `php-dev`, `git` and `cmake` packages.

```bash
sudo apt install -y cmake git 
```

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
sudo vi /usr/local/etc/php/8.1/php.ini
```

And add the following line at the end of the file

```ini
extension="glfw.so"
```