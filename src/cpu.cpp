export module cpu;

namespace rabbit {

export template <typename MMU>
class Cpu {
public:
    Cpu() {}

private:
    MMU m_mmu;

    // CPU Registers
    unsigned short m_AF; // Accumulator and flags
    unsigned short m_BC; // BC register
    unsigned short m_DE; // DE register
    unsigned short m_HL; // HL register
    unsigned short m_SP; // Stack pointer
    unsigned short m_PC; // Program file
};
}