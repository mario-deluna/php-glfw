
# Installing PHP-GLFW on Windows

!!! error "Unfinished"
    
    Sorry, we are still working on the windows build. These are just leftover notes 
    from the processs when we tested PHP-GLFW on windows. You might get it to work 
    but this is still a work in progress for now!


PHP-GLFW will not run properly under WSL (Windows Subsystem) so make sure you install PHP nativley to windows. If you already done so you can skip the next section.

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

## Download DLL

---

## Build from Source

In order to build PHP-GLFW we need to the "Development Package".

1. Go to https://windows.php.net/download#php-8.1 and download the x64 thread safe "Development package (SDK to develop PHP extensions)".
2. Place the contents of the downloaded zip into `C:\php`. **If that directory does not exist, please follow the steps "Install PHP"**.
3. Follow the following guide https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2.
4. In the `php-sdk` directory run the following:
    1. run one of the `bat` files for your setup. I used: `phpsdk-vs17-x64.bat`.
    1. phpsdk_deps --update --branch master
    3. Copy PHP-GLFW source into `ext/glfw` of the cloned PHP source code.
5. run: `buildconf && configure --disable-all --enable-cli --enable-glfw=shared && nmake`


### Install Dev Package



### Install the extension

Now we can finally build the actual extension.

1. Download or clone PHP-GLFW and open the directory up in a power shell or CMD.
2. run `phpize`
3. run `./configure --enable-glfw`
