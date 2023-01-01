# <?php echo $mat->name; ?> - GL Math

PHP-GLFW comes with a built-in math library this is a quick reference for the `<?php echo $mat->name; ?>` class.
The `<?php echo $mat->name; ?>` represents a matrix 4x4 Matrix with 16 values.

The values hold by the Mat4 object are stored internally as real float values, and can be accessed in an array like fashion:

```php
$mat = new <?php echo $mat->name; ?>();
$mat[0] = 42.0;
$mat[15] = 42.0;

echo $mat[0];
echo $mat[15];
```

## Methods

<?php foreach([
    '__construct', 
    'fromArray',
    'inverted'
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Math\\' . $mat->name . '::' . $funcName); ?> 
<?php endforeach; ?>