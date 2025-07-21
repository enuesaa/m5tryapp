#include "htmlentities.hpp"

namespace utils::htmlentities {
    String decode(const String &input) {
        String output;
        int len = input.length();

        for (int i = 0; i < len;) {
            if (input[i] == '&' && i + 3 < len && input[i + 1] == '#' && input[i + 2] == 'x') {
                int semi = input.indexOf(';', i);
                if (semi != -1) {
                    String hexStr = input.substring(i + 3, semi);
                    uint16_t codepoint = strtol(hexStr.c_str(), nullptr, 16);

                    // UTF-8 に変換して追加
                    if (codepoint < 0x80) {
                        output += (char)codepoint;
                    } else if (codepoint < 0x800) {
                        output += (char)(0xC0 | (codepoint >> 6));
                        output += (char)(0x80 | (codepoint & 0x3F));
                    } else {
                        output += (char)(0xE0 | (codepoint >> 12));
                        output += (char)(0x80 | ((codepoint >> 6) & 0x3F));
                        output += (char)(0x80 | (codepoint & 0x3F));
                    }

                    i = semi + 1;
                    continue;
                }
            }

            output += input[i];
            i++;
        }

        return output;
    }
} // namespace utils::htmlentities
