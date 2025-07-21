#include "rss.hpp"
#include "openai.hpp"
#include "secrets.hpp"
#include <HTTPClient.h>
#include <M5Unified.h>

void parseRSSFeed() {
    HTTPClient http;
    http.begin(RSS_FEED_URI);

    int code = http.GET();
    if (code != 200) {
        M5.Lcd.printf("HTTP Error: %d\n", code);
        return;
    }

    String payload = http.getString();
    http.end();

    const String tagStart = "<title>";
    const String tagEnd = "</title>";
    int cursor = 0;
    int count = 0;

    while (true) {
        int startIdx = payload.indexOf(tagStart, cursor);
        if (startIdx == -1) {
            break;
        }
        int endIdx = payload.indexOf(tagEnd, startIdx + tagStart.length());
        if (endIdx == -1) {
            break;
        }
        if (count == 0) {
            count += 1;
            continue;
        }
        count += 1;

        String title = payload.substring(startIdx + tagStart.length(), endIdx);
        M5.Lcd.println(1);
        M5.Lcd.println(decodeHTMLEntities(title));
        speech(decodeHTMLEntities(title));

        cursor = endIdx + tagEnd.length();

        if (count > 5) {
            break;
        }
    }
}

String decodeHTMLEntities(const String &input) {
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
