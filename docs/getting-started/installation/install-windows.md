<div class="grid cards" markdown>

-   :fontawesome-brands-linux:{ .lg .middle } __Install on Linux__

    ---

    [:octicons-arrow-right-24: Linux Installation](./install-linux.md)

-   :material-apple:{ .lg .middle } __Install on MacOS__

    ---

    [:octicons-arrow-right-24: MacOS Installation](./install-macos.md)
</div>

# Installing PHP-GLFW on Windows

PHP-GLFW will not run properly under WSL (Windows Subsystem) so make sure you install PHP natively on windows. 
If you haven't already done so, check out the [Installing PHP natively on Windows](#installing-php-natively-on-windows) section.


## Download DLL

For Windows, we provide a prebuilt `DLL` which you can simply download and place into your PHP extension folder.

 1. See the releases page for the latest `DLL` downloads: [PHP-GLFW Releases](https://github.com/mario-deluna/php-glfw/releases)
 2. Download the zip that matches your local PHP installation. The file names look like this:
    ```
    php_glfw-<release>-8.5-ts-vs17-x64.zip
                       │   │  │    └ architecture
                       │   │  └ Visual Studio version PHP was built with
                       │   └ thread safety: "ts" or "nts"
                       └ PHP version
    ```
    Run `php -v` to find the values for your PHP. It tells you the version, `ZTS` (thread safe, pick `ts`) or `NTS` (pick `nts`), and the Visual C++ version. If you are following this guide, you want the `ts` build for your PHP version.
 3. Extract `php_glfw.dll` from the zip into your PHP's `ext` folder. Usually that's `C:\php\ext\php_glfw.dll`.
 4. Enable the extension in your `php.ini` (usually at `C:\php\php.ini`)
    ```ini
    extension=glfw
    ```

!!! success ""
    
    **That's it**, You can check if the extension is loaded properly with `php -m`.

!!! tip "Seeing \"Can't load module ... as it's linked with 14.xx, but the core is linked with 14.yy\"?"

    This means the `DLL` was built for a different PHP than the one you are running. Double check that the PHP version and the `ts`/`nts` part of the zip name match the output of `php -v`. If you are on an older PHP-GLFW release, grab the latest one: releases before 2.4.1 shipped PHP 8.4 and 8.5 builds that were linked with a too new compiler.

---

## Installing PHP natively on Windows

PHP-GLFW will not run properly under WSL (Windows Subsystem) so make sure you install PHP natively on windows. If you have already done so you can skip the next section.

1. Go to https://windows.php.net/download#php-8.1 and download a x64 thread safe version of PHP.
2. Extract the zip file and move the contents to `C:\php`. (You have to create that directory)
3. Ensure this path is valid now, and points to an executable: `C:\php\php.exe`.
4. Add `C:\php` to the `Path` environment variable. 
    1. Press on windows start and search for environment.
    2. "Edit the system environment variables" should popup, open it.
    3. In the dialog, click on the tab "Advanced" and then on the button "Environment Variables..."
    4. In the "System Variables" list scroll down and edit the `Path` variable.
    5. In the edit dialog, click on the "New" and enter `C:\php`.
5. Open up a **NEW** powershell or CMD and type `php -v` to verify the installation.


## Build from Source

In order to build PHP-GLFW we need to the "Development Package".

<!--
1. Go to https://windows.php.net/download#php-8.1 and download the x64 thread safe "Development package (SDK to develop PHP extensions)".
2. Place the contents of the downloaded zip into `C:\php`. **If that directory does not exist, please follow the steps "Install PHP"**.
3. Follow the following guide https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2.
4. In the `php-sdk` directory run the following:
    1. run one of the `bat` files for your setup. I used: `phpsdk-vs17-x64.bat`.
    1. phpsdk_deps --update --branch master
    3. Copy PHP-GLFW source into `ext/glfw` of the cloned PHP source code.
5. run: `buildconf && configure --disable-all --enable-cli --enable-glfw=shared && nmake`

another go -->

1. Clone the php-sdk: `git clone https://github.com/php/php-sdk-binary-tools.git php-sdk`, to drive root (`C:\`)
2. `cd C:\php-sdk`
3. Run the setup bat file, in my case I use the same architecture and SDK version as the downloaded precompiled PHP for windows. (`phpsdk-vs16-x64.bat`)
4. `phpsdk_buildtree phpmaster` 
5. `git clone https://github.com/php/php-src.git && cd php-src`
6. `phpsdk_deps --update --branch 8.1`
7. Copy PHP-GLFW source into `ext/glfw` of the cloned PHP source code.
8. run: `buildconf && configure --disable-all --enable-cli --enable-glfw=shared && nmake`
9. the resulting `dll` should be located depending on your choosen build under `x64\Release_TS\php_glfw.dll`. 

