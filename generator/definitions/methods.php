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
			'&major' => 'long',
			'&minor' => 'long',
			'&rev' => 'long' 
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
		];

		public function generateCall() : string 
		{
			return 'glClear(GL_COLOR_BUFFER_BIT);';
		}
	},
	/* ToDo */
];