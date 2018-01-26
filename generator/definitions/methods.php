<?php
/**
 * This file returns an array of Method objects that
 * will be converted into PHP functions.
 */
return 
[
	/**
	 * 
	 * MAIN
	 * -----------------------------------------------------------
	 */

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
	 * glfwGetVersion
	 */
	new class extends Method {
		public $name = 'glfwGetVersion';
		public $arguments = [
			'&major:int' => 'long',
			'&minor:int' => 'long',
			'&rev:int' => 'long' 
		];
	},

	/**
	 * glfwGetVersionString
	 */
	new class extends Method {
		public $name = 'glfwGetVersionString';
		public $returns = 'string';
	},

	/**
	 * 
	 * Context
	 * -----------------------------------------------------------
	 */
	/**
	 * glfwMakeContextCurrent
	 */
	new class extends Method {
		public $name = 'glfwMakeContextCurrent';
		public $arguments = [
			'window' => 'window',
		];

		public function generateCall() : string
		{
			$b = parent::generateCall();

			$b .= "if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {" . PHP_EOL;
			$b .= 'zend_error(E_ERROR, "Could not load glad.");' . PHP_EOL;
			$b .= "}" . PHP_EOL;

			return  $b;
		}
	},

	/**
	 * glfwGetCurrentContext
	 */
	new class extends Method {
		public $name = 'glfwGetCurrentContext';
		
		// custom call
		public function generateCall() : string 
		{
			$b = 'GLFWwindow* window = glfwGetCurrentContext();' . PHP_EOL;
			$b .= 'if (!window) RETURN_FALSE;' . PHP_EOL;
		    $b .= 'PHPGLFW_RETURN_RESOURCE(window, phpglfw_window_context);' . PHP_EOL;

		    return $b;
		}
	},

	/**
	 * glfwSwapInterval
	 */
	new class extends Method {
		public $name = 'glfwSwapInterval';
		public $arguments = [
			'interval' => 'long',
		];
	},

	/**
	 * glfwExtensionSupported
	 */
	new class extends Method {
		public $name = 'glfwExtensionSupported';
		public $returns = 'bool';
		public $arguments = [
			'extension' => 'string',
		];
	},

	/**
	 * glfwGetProcAddress
	 */
	new class extends Method {
		public $name = 'glfwGetProcAddress';
		public $arguments = [
			'procname' => 'string',
		];
		/* ToDo */
	},

	

	/**
	 * 
	 * Window
	 * -----------------------------------------------------------
	 */

	/**
	 * glfwDefaultWindowHints
	 */
	new class extends Method {
		public $name = 'glfwDefaultWindowHints';
	},

	/**
	 * glfwWindowHint
	 */
	new class extends Method {
		public $name = 'glfwWindowHint';
		public $arguments = [
			'hint' => 'long',
			'value' => 'long',
		];
	},

	/**
	 * glfwDestroyWindow
	 */
	new class extends Method {
		public $name = 'glfwDestroyWindow';
		public $arguments = [
			'window' => 'window',
		];

		// no window fetching here
		protected function generateWindowResourceFetchCode() : string { return ''; }

		// custom call
		public function generateCall() : string 
		{
			return 'zend_list_close(Z_RES_P(window_resource));';
		}
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

		public function generateCall() : string 
		{
			$b = 'GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);' . PHP_EOL;
		    $b .= 'if (!window) RETURN_FALSE;' . PHP_EOL;
		    $b .= 'PHPGLFW_RETURN_RESOURCE(window, phpglfw_window_context);' . PHP_EOL;

		    return $b;
		}
	},

	/**
	 * glfwWindowShouldClose
	 */
	new class extends Method {
		public $name = 'glfwWindowShouldClose';
		public $returns = 'bool';
		public $arguments = [
			'window' => 'window',
		];
	},

	/**
	 * glfwSetWindowShouldClose
	 */
	new class extends Method {
		public $name = 'glfwSetWindowShouldClose';
		public $arguments = [
			'window' => 'window',
			'value' => 'bool',
		];
	},

	/**
	 * glfwSwapBuffers
	 */
	new class extends Method {
		public $name = 'glfwSwapBuffers';
		public $arguments = [
			'window' => 'window'
		];
	},

	/**
	 * glfwPollEvents
	 */
	new class extends Method {
		public $name = 'glfwPollEvents';
		public $arguments = [
		];
	},

	
	/**
	 * 
	 * OpenGL
	 * -----------------------------------------------------------
	 */


	/**
	 * glClearColor
	 */
	new class extends Method {
		public $name = 'glClearColor';
		public $arguments = [
			'r' => 'double',
			'g' => 'double',
			'b' => 'double',
			'a' => 'double',
		];
	},

	/**
	 * glClearColor
	 */
	new class extends Method {
		public $name = 'glClear';
		public $arguments = [
			'mask' => 'long',
		];
	},

	/**
	 * glGenBuffers
	 */
	new class extends Method {
		public $name = 'glGenBuffers';
		public $arguments = [
			'n' => 'long',
			'&buffers:GLuint' => 'long',
		];
	},

	/**
	 * glGenVertexArrays
	 */
	new class extends Method {
		public $name = 'glGenVertexArrays';
		public $arguments = [
			'n' => 'long',
			'&buffers:GLuint' => 'long',
		];
	},

	/**
	 * glBindBuffer
	 */
	new class extends Method {
		public $name = 'glBindBuffer';
		public $arguments = [
			'target' => 'long',
			'buffer' => 'long',
		];
	},

	/**
	 * glBindVertexArray
	 */
	new class extends Method {
		public $name = 'glBindVertexArray';
		public $arguments = [
			'target' => 'long',
		];
	},

	/**
	 * glBufferData
	 */
	new class extends Method {
		public $name = 'glBufferData';
		public $arguments = [
			'target' => 'long',
			'size' => 'long',
			'data' => 'ht',
			'usage' => 'long',
		];

		public function generateCall() : string 
		{
			return 'zend_error(E_ERROR, "This method is unavailable in PHP-GLFW. Please use `glBufferDataFloat(long target, array data, long usage)`, `glBufferDataDouble(long target, array data, long usage)`, `glBufferDataInt(long target, array data, long usage)` or `glBufferDataLong(long target, array data, long usage)`");';
		}
	},

	/**
	 * glBufferDataFloat
	 */
	new class extends Method {
		public $name = 'glBufferDataFloat';
		public $arguments = [
			'target' => 'long',
			'data' => 'ht',
			'usage' => 'long',
		];

		public function generateCall() : string 
		{
			$b = 'float cdata[zend_hash_num_elements(data)];' . PHP_EOL;
		    $b .= 'int i = 0;' . PHP_EOL;
		    $b .= 'ZEND_HASH_FOREACH_VAL(data, data_data)' . PHP_EOL;
		    $b .= '  ZVAL_DEREF(data_data);' . PHP_EOL;
		    $b .= '  convert_to_double(data_data);' . PHP_EOL;
		    $b .= '  cdata[i] = (float) Z_DVAL_P(data_data);' . PHP_EOL;
		    $b .= 'ZEND_HASH_FOREACH_END();' . PHP_EOL;
		    $b .= 'glBufferData(target, sizeof(cdata), cdata, usage);' . PHP_EOL;

		    return $b;
		}
	},

	/**
	 * 
	 * OpenGL Shaders
	 * -----------------------------------------------------------
	 */
	/**
	 * glCreateShader
	 */
	new class extends Method {
		public $name = 'glCreateShader';
		public $returns = 'long';
		public $arguments = [
			'target' => 'long',
		];
	},

	/**
	 * glShaderSource
	 */
	new class extends Method {
		public $name = 'glShaderSource';
		public $arguments = [
			'shader' => 'long',
			'count' => 'long',
			'source' => '&string',
			'length' => 'null',
		];
	},

	/**
	 * glCompileShader
	 */
	new class extends Method {
		public $name = 'glCompileShader';
		public $arguments = [
			'shader' => 'long'
		];
	},

	/**
	 * glGetShaderiv
	 */
	new class extends Method {
		public $name = 'glGetShaderiv';
		public $arguments = [
			'shader' => 'long',
			'pname' => 'long',
			'&params' => 'long'
		];
	},
];