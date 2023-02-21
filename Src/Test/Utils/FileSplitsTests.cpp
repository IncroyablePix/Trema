#include <catch2/catch_test_macros.hpp>
#include <Utils/FileSplits.h>

using namespace Trema::Utils;

namespace Trema::Test::Utils
{
    TEST_CASE("Unix-like path extensionless file")
    {
        // Given
        std::string file("/etc/fstab");

        // When
        FileSplit fs(file);

        // Then
        REQUIRE(fs.FileExtension.empty());
        REQUIRE(fs.FilePath == "/etc");
        REQUIRE(fs.FileWithoutExtension == "fstab");
        REQUIRE(fs.FileName == "fstab");
        REQUIRE(fs.FileWithoutExtensionLowered == "fstab");
    }

    TEST_CASE("Windows extensionless file")
    {
        // Given
        std::string file(R"(C:\Windows\System32\drivers\etc\hosts)");

        // When
        FileSplit fs(file);

        // Then
        REQUIRE(fs.FileExtension.empty());
        REQUIRE(fs.FilePath == "C:\\Windows\\System32\\drivers\\etc");
        REQUIRE(fs.FileWithoutExtension == "hosts");
        REQUIRE(fs.FileName == "hosts");
        REQUIRE(fs.FileWithoutExtensionLowered == "hosts");
    }

    TEST_CASE("Filename with extension")
    {
        // Given
        std::string file("/etc/dhcp/dhcpd.conf");

        // When
        FileSplit fs(file);

        // Then
        REQUIRE(fs.FileExtension == "conf");
        REQUIRE(fs.FilePath == "/etc/dhcp");
        REQUIRE(fs.FileWithoutExtension == "dhcpd");
        REQUIRE(fs.FileName == "dhcpd.conf");
        REQUIRE(fs.FileWithoutExtensionLowered == "dhcpd");
    }

    TEST_CASE("Filename with multiple dots")
    {
        // Given
        std::string file("/home/test/some-random-project/webpack.config.js");

        // When
        FileSplit fs(file);

        // Then
        REQUIRE(fs.FileName == "webpack.config.js");
        REQUIRE(fs.FileWithoutExtension == "webpack.config");
        REQUIRE(fs.FileExtension == "js");
        REQUIRE(fs.FilePath == "/home/test/some-random-project");
    }
}