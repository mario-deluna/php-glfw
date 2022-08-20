# <?php echo $vec->name; ?> - GL Math

PHP-GLFW comes with built in fixed size vector classes. `<?php echo $vec->name; ?>` represents a vector with <?php echo $vec->size; ?> components (
<?php foreach($vec->getPropIt() as $i => $prop) : ?>`<?php echo $prop; ?>`, <?php endforeach; ?>).

```php 
namespace GL\Math
{
    class <?php echo $vec->name; ?> {
<?php foreach($vec->getPropIt() as $i => $prop) : ?>
        public float $<?php echo $prop; ?>;
<?php endforeach; ?>
    }
}
```

The properties of this class are virtual, meaning in this case they are not real PHP properties. But rather values stored internally that 
can be accessed like a property. The same values can be read and written using different names for convience:

```php
$vec = new <?php echo $vec->name; ?>;
<?php foreach($vec->getPropIt() as $i => $prop) : ?>
$vec-><?php echo $prop; ?> = 42.0;
<?php endforeach; ?>
```

Is exactly the same as:

```php
$vec = new <?php echo $vec->name; ?>;
<?php foreach($vec->getAltPropIt() as $i => $prop) : ?>
$vec-><?php echo $prop; ?> = 42.0;
<?php endforeach; ?>
```

## Methods

<?php foreach(['__construct', 'length', 'dot', 'distance', 'distance2', 'normalize', 'abs'] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Math\\' . $vec->name . '::' . $funcName); ?> 
<?php endforeach; ?>