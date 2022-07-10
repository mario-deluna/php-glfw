
/** @generate-function-entries */
/** @generate-class-entries */
/**
 * Classes
 */
namespace PGL\Math 
{
    class Vec3 {
        public function length() : float {}
        public function normalize() : Vec3 {}
        public function abs() : Vec3 {}
        public function __toString() : string {}
    }    
};

namespace {
    /**
     * Constants
     * ----------------------------------------------------------------------------
     */
<?php foreach($constants as $const) : //var_dump($const); die; ?>
<?php if ($const->isForwardDefinition) : ?>
    // const <?php echo $const->name; ?> = <?php echo $const->definitionValueString; ?>;
<?php else : ?>
    //define('a', 'stable');
<?php endif; ?>
<?php endforeach; ?>

    /**
     * Functions
     * ----------------------------------------------------------------------------
     */
<?php foreach($functions as $func) : ?>
<?php echo tabulate($func->getFunctionPHPCommentBlock()); ?> 
    <?php echo $func->getPHPStub(); ?> 
<?php endforeach; ?> 
}
