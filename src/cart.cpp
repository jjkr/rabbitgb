#include "cart.hpp"
#include <algorithm>
#include <utility>

using std::uint8_t;
using std::span;
using std::end;
using std::ranges::find;
using std::begin;
using std::move;
using std::ostream;
using std::string_view;
using std::equal;
using std::vector;

namespace {
constexpr int CART_INFO_OFFSET = 0x100;
constexpr int CART_INFO_LOGO_OFFSET = 4;
constexpr int CART_INFO_TITLE_OFFSET = 0x34;
constexpr int CART_INFO_TITLE_LENGTH = 16;
constexpr int CART_INFO_TYPE_OFFSET = 0x47;
constexpr int CART_INFO_HEADER_CHECKSUM_OFFSET = 0x4d;
constexpr int CART_INFO_HEADER_CHECKSUM_DATA_OFFSET = 0x34;
constexpr int CART_INFO_HEADER_CHECKSUM_DATA_LENGTH = 0x19;
}

namespace rabbit {
const uint8_t NINTENDO_LOGO_DATA[] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
};

CartInfo::CartInfo(span<const uint8_t> infoBytes)
        : m_infoBytes(move(infoBytes)) {
}

bool CartInfo::hasNintendoLogoData() const {
    return equal(begin(NINTENDO_LOGO_DATA), end(NINTENDO_LOGO_DATA),
        m_infoBytes.begin() + CART_INFO_LOGO_OFFSET);
}

string_view CartInfo::title() const {
    auto titleRange = m_infoBytes.subspan(CART_INFO_TITLE_OFFSET, CART_INFO_TITLE_LENGTH);
    auto titleEnd = find(titleRange, '\0');
    return string_view(
        reinterpret_cast<const char*>(titleRange.data()),
        titleEnd - titleRange.begin());
}

bool CartInfo::isHeaderChecksumValid() const {
    return m_infoBytes[CART_INFO_HEADER_CHECKSUM_OFFSET] == headerChecksum();
}

uint8_t CartInfo::headerChecksum() const {
    uint8_t checksum = 0;
    for (int i = 0; i < CART_INFO_HEADER_CHECKSUM_DATA_LENGTH; ++i) {
        checksum = checksum - m_infoBytes[CART_INFO_HEADER_CHECKSUM_DATA_OFFSET + i] - 1;
    }
    return checksum;
}

CartType CartInfo::cartType() const {
    return CartType(m_infoBytes[CART_INFO_TYPE_OFFSET]);
}

ostream& operator<<(ostream& os, const CartInfo& cartInfo) {
    return os << "CartInfo{title: \"" << cartInfo.title()
              << "\", hasNintendoLogo: " << cartInfo.hasNintendoLogoData()
              << ", headerChecksumValid: " << cartInfo.isHeaderChecksumValid() << "}";
}

Cart::Cart(const std::vector<std::uint8_t>& rom)
    : m_cartInfo(span<const uint8_t>(rom.begin() + CART_INFO_OFFSET, CART_INFO_SIZE)),
      m_rom(rom) {
}
}