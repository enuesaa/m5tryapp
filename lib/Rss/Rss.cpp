#include "Rss.hpp"
#include <HTTPClient.h>
#include <M5Unified.h>

namespace rss {
    String fetch(const String& url) {
        HTTPClient http;
        http.begin(url);

        int code = http.GET();
        if (code != 200) {
            // M5.Lcd.printf("HTTP Error: %d\n", code);
            return "";
        }
        http.end();

        String body = http.getString();

        return body;
    }

    std::vector<String> extract(const String& body, const String& tag) {
        std::vector<String> list;
        String tagStart = "<" + tag + ">";
        String tagEnd = "</" + tag + ">";

        int cursor = 0;
        while (true) {
            int startIdx = body.indexOf(tagStart, cursor);
            if (startIdx == -1) {
                break;
            }
            int endIdx = body.indexOf(tagEnd, startIdx + tagStart.length());
            if (endIdx == -1) {
                break;
            }

            String title = body.substring(startIdx + tagStart.length(), endIdx);
            list.push_back(title);

            cursor = endIdx + tagEnd.length();
        }
        return list;
    }
} // namespace app::rss
