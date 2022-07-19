# GLFW Window

## `glfwCreateWindow`

   This function creates a window and its associated OpenGL or OpenGL ES
   context.  Most of the options controlling how the window and its context
   should be created are specified with [window hints](@ref window_hints).
 
   Successful creation does not change which context is current.  Before you
   can use the newly created context, you need to
   [make it current](@ref context_current).  For information about the `share`
   parameter, see @ref context_sharing.
 
   The created window, framebuffer and context may differ from what you
   requested, as not all parameters and hints are
   [hard constraints](@ref window_hints_hard).  This includes the size of the
   window, especially for full screen windows.  To query the actual attributes
   of the created window, framebuffer and context, see @ref
   glfwGetWindowAttrib, @ref glfwGetWindowSize and @ref glfwGetFramebufferSize.
 
   To create a full screen window, you need to specify the monitor the window
   will cover.  If no monitor is specified, the window will be windowed mode.
   Unless you have a way for the user to choose a specific monitor, it is
   recommended that you pick the primary monitor.  For more information on how
   to query connected monitors, see @ref monitor_monitors.
 
   For full screen windows, the specified size becomes the resolution of the
   window's _desired video mode_.  As long as a full screen window is not
   iconified, the supported video mode most closely matching the desired video
   mode is set for the specified monitor.  For more information about full
   screen windows, including the creation of so called _windowed full screen_
   or _borderless full screen_ windows, see @ref window_windowed_full_screen.
 
   Once you have created the window, you can switch it between windowed and
   full screen mode with @ref glfwSetWindowMonitor.  This will not affect its
   OpenGL or OpenGL ES context.
 
   By default, newly created windows use the placement recommended by the
   window system.  To create the window at a specific position, make it
   initially invisible using the [GLFW_VISIBLE](@ref GLFW_VISIBLE_hint) window
   hint, set its [position](@ref window_pos) and then [show](@ref window_hide)
   it.
 
   As long as at least one full screen window is not iconified, the screensaver
   is prohibited from starting.
 
   Window systems put limits on window sizes.  Very large or very small window
   dimensions may be overridden by the window system on creation.  Check the
   actual [size](@ref window_size) after creation.
 
   The [swap interval](@ref buffer_swap) is not set during window creation and
   the initial value may vary depending on driver settings and defaults.
 
   @param[in] width The desired width, in screen coordinates, of the window.
   This must be greater than zero.
   @param[in] height The desired height, in screen coordinates, of the window.
   This must be greater than zero.
   @param[in] title The initial, UTF-8 encoded window title.
   @param[in] monitor The monitor to use for full screen mode, or `NULL` for
   windowed mode.
   @param[in] share The window whose context to share resources with, or `NULL`
   to not share resources.
   @return The handle of the created window, or `NULL` if an
   [error](@ref error_handling) occurred.
 
   @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
   GLFW_INVALID_ENUM, @ref GLFW_INVALID_VALUE, @ref GLFW_API_UNAVAILABLE, @ref
   GLFW_VERSION_UNAVAILABLE, @ref GLFW_FORMAT_UNAVAILABLE and @ref
   GLFW_PLATFORM_ERROR.

```php
function glfwCreateWindow(
    int $width, 
    int $height, 
    string $title, 
    ?GLFWmonitor $monitor = NULL, 
    ?GLFWwindow $share = NULL
) : GLFWwindow {};
```

## `glfwDestroyWindow`
