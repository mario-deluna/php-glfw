# <?php echo $quat->name; ?> - GL Math

PHP-GLFW comes with a built-in math library this is a quick reference for the `<?php echo $quat->name; ?>` class.
The `<?php echo $quat->name; ?>` represents a vector with <?php echo $quat->size; ?> components (<?php foreach($quat->getPropIt() as $i => $prop) : ?>`<?php echo $prop; ?>`, <?php endforeach; ?>),
which can be and is generally used to represent rotations.

```php 
namespace GL\Math
{
    class <?php echo $quat->name; ?> {
<?php foreach($quat->getPropIt() as $i => $prop) : ?>
        public float $<?php echo $prop; ?>;
<?php endforeach; ?>
    }
}
```

The properties of this class are virtual, meaning in this case they are not real PHP properties. But rather values stored internally that 
can be accessed like a property. The same values can be read and written using different names:

```php
$quat = new <?php echo $quat->name; ?>;
<?php foreach($quat->getPropIt() as $i => $prop) : ?>
$quat-><?php echo $prop; ?> = 42.0;
<?php endforeach; ?>
```

Is exactly the same as:

```php
$quat = new <?php echo $quat->name; ?>;
<?php foreach($quat->getAltPropIt() as $i => $prop) : ?>
$quat[<?php echo $i; ?>] = 42.0;
<?php endforeach; ?>
```

## Methods

<?php foreach([
    '__construct', 
    'fromVec4', 
    'fromMat4',
    'inverted',
    'normalized',
    'mix',
    'slerp', 
    'dot',
    'normalize',
    'length',
    'eulerAngles',
    'rotate',
    'inverse',
    'mat4',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Math\\' . $quat->name . '::' . $funcName); ?> 
<?php endforeach; ?>