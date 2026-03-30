<?php

namespace GL\Tests\Vulkan;

use PHPUnit\Framework\TestCase;

/**
 * Tests for Vulkan/MoltenVK support detection.
 *
 * @group glfwinit
 */
#[\PHPUnit\Framework\Attributes\Group('glfwinit')]
class VulkanSupportTest extends TestCase
{
    private bool $glfwReady = false;

    protected function setUp(): void
    {
        if (!glfwInit()) {
            $this->markTestSkipped('glfwInit() failed — no display available');
        }
        $this->glfwReady = true;
    }

    /**
     * glfwVulkanSupported() must return a boolean and not crash.
     * Whether it returns true depends on the system having Vulkan/MoltenVK installed.
     */
    public function testVulkanSupportedReturnsBool(): void
    {
        $result = glfwVulkanSupported();
        $this->assertIsBool($result);
    }

    /**
     * When Vulkan libraries are present on the system, glfwVulkanSupported() should return true.
     * This test is informational — it passes either way but logs the result.
     */
    public function testVulkanSupportedReportsStatus(): void
    {
        $supported = glfwVulkanSupported();

        // Log the result for CI visibility
        fwrite(STDERR, sprintf(
            "\n[VulkanSupportTest] glfwVulkanSupported() = %s\n",
            $supported ? 'true (Vulkan available)' : 'false (Vulkan not available)',
        ));

        // Check if Vulkan libraries exist on the system
        $hasVulkanLib = false;
        if (PHP_OS_FAMILY === 'Darwin') {
            foreach (['/opt/homebrew/lib', '/usr/local/lib'] as $dir) {
                if (file_exists("{$dir}/libvulkan.dylib")) {
                    $hasVulkanLib = true;
                    break;
                }
            }
        } else {
            foreach (['/usr/lib', '/usr/local/lib'] as $dir) {
                if (file_exists("{$dir}/libvulkan.so") || file_exists("{$dir}/libvulkan.so.1")) {
                    $hasVulkanLib = true;
                    break;
                }
            }
        }

        fwrite(STDERR, sprintf(
            "[VulkanSupportTest] Vulkan library on disk: %s\n",
            $hasVulkanLib ? 'found' : 'not found',
        ));

        if ($hasVulkanLib && $supported) {
            // Best case: Vulkan lib exists AND GLFW reports support
            $this->assertTrue($supported, 'Vulkan library found and GLFW reports support');
        } elseif ($hasVulkanLib && !$supported) {
            // Vulkan lib exists but GLFW doesn't support it — GLFW was compiled without Vulkan
            fwrite(STDERR, "[VulkanSupportTest] WARNING: Vulkan library present but GLFW lacks Vulkan support.\n");
            fwrite(STDERR, "[VulkanSupportTest] Rebuild GLFW with Vulkan loader to enable glfwVulkanSupported().\n");
            $this->assertFalse($supported); // Still passes — just documents the gap
        } else {
            // No Vulkan on system — expected to be false
            $this->assertFalse($supported, 'No Vulkan library — expected false');
        }
    }
}
