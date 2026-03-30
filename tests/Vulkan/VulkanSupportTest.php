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
    protected function setUp(): void
    {
        if (!glfwInit()) {
            $this->markTestSkipped('glfwInit() failed — no display available');
        }
    }

    /**
     * glfwVulkanSupported() must return a valid value (int 0/1 or bool) without crashing.
     */
    public function testVulkanSupportedDoesNotCrash(): void
    {
        $result = glfwVulkanSupported();
        $this->assertTrue(
            $result === true || $result === false || $result === 0 || $result === 1,
            'glfwVulkanSupported() must return a boolean-compatible value, got: ' . var_export($result, true),
        );
    }

    /**
     * Log Vulkan support status for CI diagnostic visibility.
     */
    public function testVulkanSupportedReportsStatus(): void
    {
        $supported = (bool) glfwVulkanSupported();

        fwrite(STDERR, sprintf(
            "\n[VulkanSupportTest] glfwVulkanSupported() = %s\n",
            $supported ? 'true (Vulkan available)' : 'false (Vulkan not available)',
        ));

        // This test always passes — it's purely diagnostic.
        // The actual value depends on the system's Vulkan installation.
        $this->addToAssertionCount(1);
    }
}
