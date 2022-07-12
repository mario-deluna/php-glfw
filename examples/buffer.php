<?php 

$buffer = new \PGL\Buffer\FBuffer();
$buffer->reserve(42000000);

$arr = [];

var_dump(memory_get_usage(true));

for ($i = 0; $i < 42000000; $i++) {
    // $buffer->push($i);
    $arr[] = $i;
}


var_dump(memory_get_usage(true));

var_dump($buffer, $arr);