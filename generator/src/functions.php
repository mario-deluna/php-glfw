<?php

function commentifyString(string $text, string $linePrefix = ' * ', int $maxLength = 80) : string
{
    $lines = explode("\n", $text);
    foreach($lines as &$line) {
        $line = wordwrap($line, $maxLength - strlen($linePrefix));
    }
    
    // rebuild and split again into seperate lines
    $lines = implode("\n", $lines);
    $lines = explode("\n", $lines);

    // add the prefix 
    foreach($lines as &$l) {
        $l = $linePrefix . $l;
    }

    return implode("\n", $lines);
}
