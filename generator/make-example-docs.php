<?php

require __DIR__ . '/bootstrap.php';

// scan the example directory for VG examples
$vgExamples = [];
$vgExamplesPath = GEN_PATH_EXT . '/examples/vg';

class VGExample {
    public function __construct(
        public readonly string $name,
        public readonly string $path,
        public string $description,
        public string $text,
        public array $parameters = [],
        public ?string $thumbnail = null,
    )
    {}

    public function getDocName() : string {
        $docfile = basename($this->path);
        return substr($docfile, 0, -4);
    }

    public function getDocPath() : string {
        return GEN_PATH_EXT . '/docs/examples/vector-graphics/' . $this->getDocName() . '.md';
    }

    public function getImagePath() : string {
        if ($image = $this->parameters['image'] ?? null) {
            return "./../../docs-assets/php-glfw/{$image}";
        }

        return "./../../docs-assets/php-glfw/examples/vg/{$this->getDocName()}.png";
    }

    public function getImagePathAbs() : string {
        $path = $this->getImagePath();
        if ($this->parameters['thumbnail'] ?? false) {
            $path = "./../../docs-assets/php-glfw/{$this->parameters['thumbnail']}";

            // replace {example} with the example name
            $path = str_replace('{example}', $this->getDocName(), $path);
        }
        return GEN_PATH_EXT . '/docs/' . substr($path, 8);
    }
}

foreach (scandir($vgExamplesPath) as $file) {
    if (substr($file, -4) !== '.php') {
        continue;
    }

    $name = substr($file, 0, -4);
    $path = $vgExamplesPath . '/' . $file;

    // open the file and scan for the first comment block
    $fileContent = file_get_contents($path);
    $commentStart = strpos($fileContent, '/**');
    $commentEnd = strpos($fileContent, '*/', $commentStart);

    if ($commentStart === false || $commentEnd === false) {
        continue;
    }

    $comment = trim(substr($fileContent, $commentStart + 3, $commentEnd - $commentStart - 3));

    // if the comment is the stupid "example helper" comment then skip
    if (strpos($comment, 'We utilize the example helpers here') !== false) {
        continue;
    }

    $lines = explode("\n", $comment);
    $lines = array_map(fn($line) => preg_replace('/^\ ?+\* ?/', '', $line), $lines);

    if (count($lines) === 0) {
        continue;
    }

    // first line is the title
    $title = array_shift($lines);

    // look for annotations
    $paramters = [];
    foreach($lines as $k => $line) {
        if (preg_match("/^\@([a-zA-Z0-9\.\:_-]+) +(.*)/", $line, $matches)) {
            $paramters[$matches[1]] = $matches[2];

            // remove the line
            unset($lines[$k]);
        }
    }

    // rest is text
    $text = trim(implode("\n", $lines));
    $lines = explode("\n\n", $text);

    // first line is the description
    $desc = array_shift($lines);

    $text = implode("\n\n", $lines);

    $vgExamples[] = new VGExample(
        name: $title,
        path: $path,
        description: $desc,
        text: $text,
        parameters: $paramters,
    );
}

// now create the example docs files
foreach($vgExamples as $example) 
{
    // build a thumbnail for the example
    $thumbPath = GEN_PATH_EXT . '/docs/docs-assets/php-glfw/examples/vg/' . $example->getDocName() . '_thumb.png';
    $example->thumbnail = './../../docs-assets/php-glfw/examples/vg/' . $example->getDocName() . '_thumb.png';
    $imageSysPath = $example->getImagePathAbs();

    if (!file_exists($thumbPath)) 
    {
        // use imagemagick to create a thumbnail
        $cmd = "convert {$imageSysPath}[0] -thumbnail 512x512 {$thumbPath}";
        passthru($cmd);
    }


    $mkbuffer = "";
    
    // title
    $mkbuffer .= "# {$example->name}\n\n";

    $mkbuffer .= "{$example->description}\n\n";

    // image 
    $mkbuffer .= "<figure markdown>\n";
    $mkbuffer .= "![{$example->name} Example (PHP-GLFW VG)]({$example->getImagePath()}){ width=\"600\" }\n";
    $mkbuffer .= "</figure>\n\n";

    // code
    $mkbuffer .= "<div style=\"text-align: center;\" markdown>\n";
    $mkbuffer .= "[Check out the Code](https://github.com/mario-deluna/php-glfw/blob/master/examples/vg/{$example->getDocName()}.php){ .md-button .md-button--primary }\n";
    $mkbuffer .= "</div>\n\n";

    // run command
    $mkbuffer .= "Run this example:\n\n";
    $mkbuffer .= "```\n";
    $mkbuffer .= "php examples/vg/{$example->getDocName()}.php\n";
    $mkbuffer .= "```\n\n";

    // description
    $mkbuffer .= "{$example->text}\n\n";

    // write 
    file_put_contents($example->getDocPath(), $mkbuffer);
}

// next up, open the 00-about-examples.md file and update the list of examples
$aboutExamplesPath = GEN_PATH_EXT . '/docs/examples/00-about-examples.md';
$aboutExamplesContent = file_get_contents($aboutExamplesPath);

// we have a marker inside of the MK file
// <!-- VGEXAMPLES BEGIN -->
// <!-- VGEXAMPLES END -->
$markerStart = strpos($aboutExamplesContent, '<!-- VGEXAMPLES BEGIN -->');
$markerEnd = strpos($aboutExamplesContent, '<!-- VGEXAMPLES END -->', $markerStart);

if ($markerStart === false || $markerEnd === false) {
    throw new \Exception('Could not find marker in about examples file');
}

$markerStart += strlen('<!-- VGEXAMPLES BEGIN -->');

$docHead = substr($aboutExamplesContent, 0, $markerStart);
$docTail = substr($aboutExamplesContent, $markerEnd);

$newContent = $docHead . PHP_EOL;

// group the examples by category
$categories = [];
foreach($vgExamples as $example) {
    $categories[$example->parameters['category'] ?? 'Uncategorized'][] = $example;
}

foreach($categories as $category => $examples) {
    $newContent .= "### {$category}\n\n";

    $newContent .= "<div class=\"grid cards\" markdown>\n\n";
    $newContent .= implode("\n\n", array_map(function($example) {
        return "-   __{$example->name}__\n\n    ---\n\n    [![Example]({$example->thumbnail})](./vector-graphics/{$example->getDocName()}.md)";
    }, $examples));
    $newContent .= "\n\n</div>\n\n";
}

$newContent .= $docTail;

file_put_contents($aboutExamplesPath, $newContent);