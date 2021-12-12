/**
 * Constants
 */
namespace {
<?php foreach($constants as $const) : //var_dump($const); die; ?>
<?php if ($const->isForwardDefinition) : ?>
    //define('<?php echo $const->name; ?>', <?php echo $const->definitionValueString; ?>);
<?php else : ?>
    //define('a', 'stable');
<?php endif; ?>
<?php endforeach; ?>
}

