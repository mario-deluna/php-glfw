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
			'glfwwindow' => 'resource',
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
			$b = 'GLFWwindow* glfwwindow = glfwGetCurrentContext();' . PHP_EOL;
			$b .= 'if (!glfwwindow) RETURN_FALSE;' . PHP_EOL;
			$b .= Resource::getReturnCall('glfwwindow');

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
			'glfwwindow' => 'resource',
		];

		// no window fetching here
		protected function generateWindowResourceFetchCode() : string { return ''; }

		// custom call
		public function generateCall() : string 
		{
			return 'zend_list_close(Z_RES_P(glfwwindow_resource));';
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
			$b = 'GLFWwindow* glfwwindow = glfwCreateWindow(width, height, title, NULL, NULL);' . PHP_EOL;
		    $b .= 'if (!glfwwindow) RETURN_FALSE;' . PHP_EOL;
			$b .= Resource::getReturnCall('glfwwindow');

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
			'glfwwindow' => 'resource',
		];
	},

	/**
	 * glfwSetWindowShouldClose
	 */
	new class extends Method {
		public $name = 'glfwSetWindowShouldClose';
		public $arguments = [
			'glfwwindow' => 'resource',
			'value' => 'bool',
		];
	},

	/**
	 * glfwSwapBuffers
	 */
	new class extends Method {
		public $name = 'glfwSwapBuffers';
		public $arguments = [
			'glfwwindow' => 'resource'
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
	 * glfwGetTime
	 */
	new class extends Method {
		public $name = 'glfwGetTime';
		public $returns = 'double';
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
	 * glDeleteBuffers
	 */
	new class extends Method {
		public $name = 'glDeleteBuffers';
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
	 * glDeleteVertexArrays
	 */
	new class extends Method {
		public $name = 'glDeleteVertexArrays';
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
		    $b .= '  i++;' . PHP_EOL;
		    $b .= 'ZEND_HASH_FOREACH_END();' . PHP_EOL;
		    $b .= 'glBufferData(target, sizeof(cdata), cdata, usage);' . PHP_EOL;

		    return $b;
		}
	},

	/**
	 * glVertexAttribPointer
	 */
	new class extends Method {
		public $name = 'glVertexAttribPointer';
		public $arguments = [
			'index' => 'long',
			'size' => 'long',
			'type' => 'long',
			'normalized' => 'long',
			'stride' => 'long',
			'pointer' => 'long',
		];

		public function generateCall() : string 
		{
			$b = 'glVertexAttribPointer(index, size, type, normalized, stride * sizeof(float), (void*)(pointer * sizeof(float)));' . PHP_EOL;

		    return $b;
		}
	},

	/**
	 * glEnableVertexAttribArray
	 */
	new class extends Method {
		public $name = 'glEnableVertexAttribArray';
		public $arguments = [
			'index' => 'long',
		];
	},

	/**
	 * glDrawArrays
	 */
	new class extends Method {
		public $name = 'glDrawArrays';
		public $arguments = [
			'mode' => 'long',
			'first' => 'long',
			'count' => 'long',
		];
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
	 * glCreateProgram
	 */
	new class extends Method {
		public $name = 'glCreateProgram';
		public $returns = 'long';
		public $arguments = [
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
	 * glDeleteShader
	 */
	new class extends Method {
		public $name = 'glDeleteShader';
		public $arguments = [
			'shader' => 'long'
		];
	},

	/**
	 * glAttachShader
	 */
	new class extends Method {
		public $name = 'glAttachShader';
		public $arguments = [
			'program' => 'long',
			'index' => 'long'
		];
	},
	
	/**
	 * glGetUniformLocation
	 */
	new class extends Method {
		public $name = 'glGetUniformLocation';
		public $arguments = [
			'program' => 'long',
			'name' => 'string'
		];
	},

	/**
	 * glUniform1i
	 */
	new class extends Method {
		public $name = 'glUniform1i';
		public $arguments = [
			'location' => 'long',
			'value' => 'long'
		];
	},

	/**
	 * glUniform1f
	 */
	new class extends Method {
		public $name = 'glUniform1f';
		public $arguments = [
			'location' => 'long',
			'value' => 'double'
		];
	},

	/**
	 * glLinkProgram
	 */
	new class extends Method {
		public $name = 'glLinkProgram';
		public $arguments = [
			'program' => 'long'
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

	/**
	 * glGetProgramiv
	 */
	new class extends Method {
		public $name = 'glGetProgramiv';
		public $arguments = [
			'program' => 'long',
			'pname' => 'long',
			'&params' => 'long'
		];
	},
	
	/**
	 * glUseProgram
	 */
	new class extends Method {
		public $name = 'glUseProgram';
		public $arguments = [
			'program' => 'long'
		];
	},
	
	// /**
	//  * 
	//  * Linmath  // This currently just want work out..
	//  * -----------------------------------------------------------
	//  */
	// /**
	//  * vec2create()
	//  */
	// new class extends Method {
	// 	public $name = 'vec2_add';
	// 	public $arguments = [
	// 		'vector1' => 'ht',
	// 		'vector2' => 'ht',
	// 	];

	// 	public function generateCall() : string 
	// 	{
	// 		return "";
	// 	}
	// },
];