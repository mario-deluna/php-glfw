<?php

function printColor(string $text, string $color) : void {
    $colors = [
        'red' => "\033[0;31m",
        'green' => "\033[0;32m",
        'yellow' => "\033[0;33m",
        'blue' => "\033[0;34m",
        'magenta' => "\033[0;35m",
        'cyan' => "\033[0;36m",
        'white' => "\033[0;37m",
        'reset' => "\033[0m",
        'bold' => "\033[1m",
    ];
    echo $colors[$color] . $text . $colors['reset'];
}

$collen = exec('tput cols');
if (!is_numeric($collen)) {
    $collen = 80;
} else {
    $collen = intval($collen);
}

function printSeperator(string $char = '-') : void {
    echo str_repeat($char, $GLOBALS['collen']) . "\n";
}

printColor(<<<'EOT'
                                       
_____ _____ _____     _____ __    _____ _ _ _ 
|  _  |  |  |  _  |___|   __|  |  |   __| | | |
|   __|     |   __|___|  |  |  |__|   __| | | |
|__|  |__|__|__|      |_____|_____|__|  |_____|

Installler for macOS


EOT, 'blue');

echo "checking requirements...\n";

$requiredPHPVersion = '8.0.0';

$requirements = [];

// check PHP 
$requirements['php'] = [
    'ok' => version_compare(PHP_VERSION, $requiredPHPVersion, '>='),
    'description' => 'PHP >= ' . $requiredPHPVersion,
];

// check phpize
$requirements['phpize'] = [
    'ok' => shell_exec('which phpize') !== NULL,
    'description' => '"phpize" is available',
];

// check if git is installed
$requirements['git'] = [
    'ok' => shell_exec('which git') !== NULL,
    'description' => '"git" is available',
];

// check if cmake is installed
$requirements['cmake'] = [
    'ok' => shell_exec('which cmake') !== NULL,
    'description' => '"cmake" is available',
];

// check if homebrew is installed
$requirements['homebrew'] = [
    'ok' => shell_exec('which brew') !== NULL,
    'description' => '"homebrew" is available',
];

// check if xcode command line tools are installedv
$requirements['xcode'] = [
    'ok' => trim(shell_exec('xcode-select -p 1>/dev/null;echo $?')) === '0',
    'description' => 'XCode command line tools are available',
];

printSeperator('-');

foreach($requirements as $name => $result) {
    if($result['ok']) {
        $line = ' ✓ ' . $result['description'];
        $line .= str_repeat(' ', ($collen - strlen($line)) - strlen($name));
        $line .= $name;
        printColor($line, 'green');
    } else {
        $line = ' ✗ ' . $result['description'];
        $line .= str_repeat(' ', ($collen - strlen($line)) - strlen($name));
        $line .= $name;
        printColor($line, 'red');
    }
    echo "\n";
}

printSeperator('-');

// fatal exits if specifc requirements are not met

// we do not install php for the user so check
if(!$requirements['php']['ok']) {
    printColor("PHP >= {$requiredPHPVersion} is required to continue!\n", 'red');
    exit(1);
}

// we do not install the phpize for the user so check
if(!$requirements['phpize']['ok']) {
    printColor("\"phpize\" is required to continue!\n", 'red');
    exit(1);
}

// xcode tools also have to be installed manually by the user
if(!$requirements['xcode']['ok']) {
    printColor("XCode command line tools are required to continue!\n", 'red');
    printColor("run \"xcode-select --install\" to install them\n", 'reset');
    exit(1);
}

// ask the user to install missing dependencies if homebrew is installed
$hasMissingDependencies = false;
foreach($requirements as $name => $result) {
    if(!$result['ok']) {
        $hasMissingDependencies = true;
    }
}

if ($hasMissingDependencies && $requirements['homebrew']['ok'] === false) {
    printColor("\nYou have missing dependencies!\n", 'yellow');
    printColor("Homebrew is not installed on your Mac so we cannot install them automatically.", 'red');
    printColor("\nPlease install homebrew: https://brew.sh\n", 'reset');
    exit(1);
}

foreach(['cmake', 'git'] as $name) {
    if(!$requirements[$name]['ok']) {
        printColor("\"{$name}\" is required to continue!\n", 'red');
        printColor("Do you want to install it now? [y/n]\n", 'yellow');
        $answer = trim(fgets(STDIN));
        if($answer === 'y') {
            passthru('sudo brew install ' . $name);
        } else {
            printColor("Please install \"{$name}\" and try again!\n", 'red');
            exit(1);
        }
    }
}

printColor("\nEverything is ready to go! beginning installation...\n", 'green');

printColor("\nCloning PHP-GLFW...\n", 'bold');

passthru('git clone https://github.com/mario-deluna/php-glfw');

printSeperator('*');

printColor("Building PHP-GLFW...\n", 'bold');

passthru("cd php-glfw && sudo phpize && ./configure --enable-glfw && make && sudo make install");

printSeperator('*');

printColor("Checking if glfw module is already loaded...\n", 'bold');

$loaded = trim(shell_exec('php -m | grep glfw')) === 'glfw';

if (!$loaded) {
    printColor("Adding glfw extension to php.ini\n", 'bold');
    // getting path to php.ini
    $phpini = trim(shell_exec('php -i | grep "Loaded Configuration File"'));
    $phpini = trim(substr($phpini, strrpos($phpini, '=> ') + 3));

    if (!file_exists($phpini)) {
        printColor("Could not find php.ini!\n", 'red');
        exit(1);
    }

    $iniContents = file_get_contents($phpini);
    $iniContents .= "\n\n[glfw]\nextension=glfw.so\n";
    file_put_contents($phpini, $iniContents);
} else {
    printColor("glfw extension is already loaded\n", 'green');
}

printSeperator('*');

$loaded = trim(shell_exec('php -m | grep glfw')) === 'glfw';

if ($loaded) {
    printColor("\nInstallation finished!\n", 'green');
} else {
    printColor("\nInstallation failed!\n", 'red');
}


