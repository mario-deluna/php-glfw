<?php

/**
 * Base argument
 */
abstract class Argument {
	public $name;
	public $charid;
	public function __construct(string $name) { $this->name = $name; }
	abstract public function generateVariable() : string;
	public function getReferences() {
		return '&' . $this->name;
	}
}

/**
 * Argument types
 */
class LongArgument extends Argument {
	public $charid = 'l';
	public function generateVariable() : string {
		return "zend_long {$this->name};";
	}
}
class FloatArgument extends Argument {
	public $charid = 'f';
	public function generateVariable() : string {
		return "zend_float {$this->name};";
	}
}
class BoolArgument extends Argument {
	public $charid = 'b';
	public function generateVariable() : string {
		return "zend_bool {$this->name};";
	}
}
class StringArgument extends Argument {
	public $charid = 's';
	public function generateVariable() : string {
		return "char *{$this->name};\nsize_t {$this->name}_size;";
	}
	public function getReferences() {
		return '&' . $this->name . ', &' . $this->name . '_size';
	}
}
class WindowArgument extends Argument {
	public $charid = 'r';
	public function generateVariable() : string {
		return "zval *{$this->name}_resource;";
	}
	public function getReferences() {
		return "&{$this->name}_resource";
	}
}

/**
 * Base method
 */
abstract class Method 
{
	public $name = null;
	public $returns = 'void';
	public $arguments = [];

	/**
	 * Does the method have arguments
	 */
	public function hasArguments() {
		return !empty($this->arguments);
	}

	/**
	 * Get an array of argument objects
	 */
	public function getArguments() : array
	{
		$args = [];

		foreach ($this->arguments as $name => $type) 
		{
			switch ($type) 
			{
				case 'long': $args[] = new LongArgument($name); break;
				case 'float': $args[] = new FloatArgument($name); break;
				case 'bool': $args[] = new BoolArgument($name); break;
				case 'string': $args[] = new StringArgument($name); break;
				case 'window': $args[] = new WindowArgument($name); break;
			}
		}

		return $args;
	}

	/**
	 * Prefix every line of the given text
	 *
	 * @param string 		$test
	 * @param string 		$prefix
	 */
	private function tabulate(string $text, string $prefix = '    ') : string
	{
		$lines = explode("\n", $text);
		foreach($lines as &$line) 
		{
			$line = $prefix . $line;
		}

		return implode("\n", $lines);
	}

	/**
	 * Generate the argument definition name
	 */
	protected function generateArgInfoName(string $name) : string
	{
		return "arginfo_{$name}";
	}

	/**
	 * Generate the function entry
	 */
	public function generateFE() : string
	{
		$arginfo = 'NULL';
		if ($this->hasArguments()) {
			$arginfo = $this->generateArgInfoName($this->name);
		}

		return "PHP_FE({$this->name}, {$arginfo})";
	}

	/**
	 * Generates the argument info definition
	 */
	public function generateArgInfo() : string
	{
		$arginfo = $this->generateArgInfoName($this->name);

		$b = "ZEND_BEGIN_ARG_INFO_EX({$arginfo}, 0, 0, 1)" . PHP_EOL;
		foreach($this->getArguments() as $argument)
		{
			$b .= "    ZEND_ARG_INFO(0, $argument->name)" . PHP_EOL;
		}

		$b .= "ZEND_END_ARG_INFO()" . PHP_EOL;
		
		return $b;
	}

	public function generateArgumentParser() : string
	{
		$b = "";

		$typecharlist = '';
		$referencelist = [];

		// generate the vars
		foreach($this->getArguments() as $argument)
		{
			$typecharlist .= $argument->charid;
			$referencelist[] = $argument->getReferences();

			// add the variable
			$b .= $argument->generateVariable() . "\n";
		}

		// create the parser method
		$b .= 'if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "'.$typecharlist.'", '.implode(', ', $referencelist).') == FAILURE) {' . PHP_EOL;
		$b .= '   return;' . PHP_EOL;
		$b .= '}';

		return $b. "\n";
	}

	/**
	 * Generate the method call
	 */
	public function generateCall() : string
	{
		
	}

	/**
	 * Generates the method 
	 */
	public function generateMethod() : string
	{
		$b = "PHP_FUNCTION($this->name)\n{\n";
		if ($this->hasArguments()) {
			$b .= $this->tabulate($this->generateArgumentParser());
		}

		$b .= $this->tabulate($this->generateCall());

		$b .= "\n}\n";

		return $b;
	}

	/**
	 * Main generator call
	 */
	public function generate()
	{
		if (!$this->hasArguments()) {
			return $this->generateMethod();
		}

		return $this->generateArgInfo() . PHP_EOL . $this->generateMethod();
	}
}



/**
 * Return types
 */
abstract class ReturnType { public $id; }

class VoidReturn extends ReturnType { public $id = 'void'; }
class LongReturn extends ReturnType { public $id = 'long'; }
class BoolReturn extends ReturnType { public $id = 'bool'; }

/**
 *
 */
return 
[
	/**
	 * glfwInit
	 */
	new class extends Method {
		public $name = 'glfwInit';
		public $returns = 'bool';
	},

	/**
	 * glfwTerminate
	 */
	new class extends Method {
		public $name = 'glfwTerminate';
	},

	/**
	 * glfwDestroyWindow
	 */
	new class extends Method {
		public $name = 'glfwDestroyWindow';
		public $arguments = [
			'window' => 'window',
		];
	},

	/**
	 * glfwCreateWindow
	 */
	new class extends Method
	{
		public $name = 'glfwCreateWindow';
		public $arguments = [
			'width' => 'long',
			'height' => 'long',
			'title' => 'string'
		];

		public function returns() {
			return new WindowReference();
		}
	}
];