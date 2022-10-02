<?php
/**
 * This example shows all the window and input callback at work
 * by simply printing the eventс to the console.
 */
require __DIR__ . '/99_example_helpers.php';


// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

glfwSetKeyCallback($window, function ($key1, $scancode2, $action3, $mods4) use ($window) {
    if ($key1 == GLFW_KEY_ESCAPE && $action3 == GLFW_PRESS) {
        glfwSetWindowShouldClose($window, GL_TRUE);
    }
});

glfwSetWindowPosCallback($window, function($x, $y) {
    echo "Window moved to: " . $x . ", " . $y . PHP_EOL;
});

glfwSetWindowSizeCallback($window, function($width, $height) {
    echo "Window resized to: " . $width . ", " . $height . PHP_EOL;
});

glfwSetWindowCloseCallback($window, function() {
    echo "Window close requested" . PHP_EOL;
});

glfwSetWindowRefreshCallback($window, function() {
    echo "Window refresh requested" . PHP_EOL;
});

glfwSetWindowFocusCallback($window, function($focused) {
    echo "Window focus changed to: " . $focused . PHP_EOL;
});

glfwSetWindowIconifyCallback($window, function($iconified) {
    echo "Window iconified changed to: " . $iconified . PHP_EOL;
});

glfwSetFramebufferSizeCallback($window, function($width, $height) {
    echo "Framebuffer resized to: " . $width . ", " . $height . PHP_EOL;
});

glfwSetWindowContentScaleCallback($window, function($x, $y) {
    echo "Window content scale changed to: " . $x . ", " . $y . PHP_EOL;
});

glfwSetCharModsCallback($window, function($codepoint, $mods) {
    echo "Character: " . mb_chr($codepoint) . ' with mods: ' . $mods . PHP_EOL;
});

glfwSetMouseButtonCallback($window, function($button, $action, $mods) {
    echo "Mouse button: " . $button . ' action: ' . $action . ' with mods: ' . $mods . PHP_EOL;
});

glfwSetCursorPosCallback($window, function($x, $y) {
    echo "Mouse cursor moved to: " . $x . ", " . $y . PHP_EOL;
});

glfwSetCursorEnterCallback($window, function($entered) {
    if ($entered) {
        echo "Mouse cursor entered window" . PHP_EOL;
    } else {
        echo "Mouse cursor left window" . PHP_EOL;
    }
});

glfwSetScrollCallback($window, function($x, $y) {
    echo "Mouse scrolled: " . $x . ", " . $y . PHP_EOL;
});

glfwSetDropCallback($window, function($count, $paths) {
    echo "Dropped " . $count . " files:" . PHP_EOL;
    for ($i = 0; $i < $count; $i++) {
        echo " -> File " . $i . ": " . $paths[$i] . PHP_EOL;
    }
});

// print some help to the console
echo str_repeat('-', 80) . PHP_EOL;
echo '-> Press ESC to close the window' . PHP_EOL;
echo '-> This example shows all the window and input callback at work' . PHP_EOL;
echo str_repeat('-', 80) . PHP_EOL;

while (!glfwWindowShouldClose($window))
{
    glfwPollEvents();
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers($window);
}

ExampleHelper::stop($window);
