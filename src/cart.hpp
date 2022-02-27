#pragma once

#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>
#include <ranges>
#include <vector>

namespace rabbit {

extern const std::uint8_t NINTENDO_LOGO_DATA[];
constexpr std::size_t CART_INFO_SIZE = 80u;

enum class CartType {
    ROM_ONLY = 0x0,
    MBC1 = 0x1,
    MBC1_RAM = 0x2,
    MBC1_RAM_BATTERY = 0x3,
    MBC2 = 0x5,
    MBC2_BATTERY = 0x6,
    ROM_RAM = 0x8,
    ROM_RAM_BATTERY = 0x9,
    MMM01 = 0x0b,
    MMM01_RAM = 0xc
};

class CartInfo {
public:
    CartInfo(std::span<const std::uint8_t> infoBytes);

    std::string_view title() const;
    bool hasNintendoLogoData() const;
    CartType cartType() const;

    bool isHeaderChecksumValid() const;
    friend std::ostream& operator<<(std::ostream& os, const CartInfo& cartInfo);

private:
    std::uint8_t headerChecksum() const;

    const std::span<const std::uint8_t> m_infoBytes;
};

std::ostream& operator<<(std::ostream& os, const CartInfo& cartInfo);

class Cart {
public:
    Cart(const std::vector<std::uint8_t>& rom);

    CartInfo cartInfo() const { return m_cartInfo; }

private:
    const CartInfo m_cartInfo;
    const std::vector<std::uint8_t>& m_rom;
};

}