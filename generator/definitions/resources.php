<?php
/**
 * This file returns an array of Resources that will be made available
 */
return 
[
	/**
	 * GLFWwindow
	 */
	new class extends Resource {
		public $type = 'GLFWwindow *';
		public $name = "glfwwindow";

		public function generateDestroy() : string {
			return "glfwDestroyWindow($this->name);";
		}
	},

	/**
	 * STB Image
	 */
	new class extends Resource {
		public $type = 'unsigned char *';
		public $name = "stbimagedata";

		public function generateDestroy() : string {
			return "stbi_image_free($this->name);";
		}
	},
];