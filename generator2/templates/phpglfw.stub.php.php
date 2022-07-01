
/** @generate-function-entries */

/**
 * Functions
 * ------------------------------------------------------------------
 */
<?php foreach($functions as $func) : ?>
<?php echo $func->getPHPStub(); ?>
<?php endforeach; ?>

/**
 * Constants
 */
<?php foreach($constants as $const) : //var_dump($const); die; ?>
<?php if ($const->isForwardDefinition) : ?>
//define('<?php echo $const->name; ?>', <?php echo $const->definitionValueString; ?>);
<?php else : ?>
//define('a', 'stable');
<?php endif; ?>
<?php endforeach; ?>

