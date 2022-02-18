#include "cart.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

using rabbit::CART_INFO_SIZE;
using rabbit::CartType;
using rabbit::CartInfo;
using std::uint8_t;
using std::span;
using std::string;
using std::vector;

namespace {
const vector<uint8_t> blankCartInfo(CART_INFO_SIZE);
const vector<uint8_t> testCartInfo = {
    0x00, 0xc3, 0x50, 0x01, 0xce, 0xed, 0x66, 0x66,
    0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
    0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f,
    0x88, 0x89, 0x00, 0x0e, 0xdc, 0xcc, 0x6e, 0xe6,
    0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63,
    0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f,
    0xbb, 0xb9, 0x33, 0x3e, 0x53, 0x55, 0x50, 0x45,
    0x52, 0x20, 0x4d, 0x41, 0x52, 0x49, 0x4f, 0x4c,
    0x41, 0x4e, 0x44, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x01, 0x00, 0x00, 0x01, 0x00, 0x9e, 0x41, 0x6b
};
}

TEST(CartInfo, hasNintendoLogoData) {
    CartInfo cartInfo(blankCartInfo);
    EXPECT_FALSE(cartInfo.hasNintendoLogoData());
}

TEST(CartInfo, hasNintendoLogoDataTrue) {
    CartInfo cartInfo(testCartInfo);
    EXPECT_TRUE(cartInfo.hasNintendoLogoData());
}

TEST(CartInfo, title) {
    CartInfo cartInfo(testCartInfo);
    string expected("SUPER MARIOLAND");
    EXPECT_EQ(expected, cartInfo.title());
}

TEST(CartInfo, titleBlank) {
    CartInfo cartInfo(blankCartInfo);
    string expected("");
    EXPECT_EQ(expected, cartInfo.title());
}

TEST(CartInfo, cartType) {
    CartInfo cartInfo(testCartInfo);
    EXPECT_EQ(CartType::MBC1, cartInfo.cartType());
}

TEST(CartInfo, cartTypeRomOnly) {
    CartInfo cartInfo(blankCartInfo);
    EXPECT_EQ(CartType::ROM_ONLY, cartInfo.cartType());
}

TEST(CartInfo, headerChecksumValid) {
    CartInfo cartInfo(testCartInfo);
    EXPECT_TRUE(cartInfo.isHeaderChecksumValid());
}

TEST(CartInfo, headerChecksumInvalid) {
    CartInfo cartInfo(blankCartInfo);
    EXPECT_FALSE(cartInfo.isHeaderChecksumValid());
}