import cpu;

#include <gtest/gtest.h>

using rabbit::Cpu;

class MMU {};

TEST(Cpu, Constructs) {
    Cpu<MMU> cpu;
}