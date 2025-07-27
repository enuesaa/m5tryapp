#include "rss.hpp"
#include "app/ai.hpp"
#include "env/vars.hpp"
#include "utils/htmlentities.hpp"
#include <HTTPClient.h>
#include <M5Unified.h>

namespace app::rss {
    void parse() {
        HTTPClient http;
        http.begin(env::vars::RSS_FEED_URI);

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
            // app::ai::speech(utils::htmlentities::decode(title));

            cursor = endIdx + tagEnd.length();

            if (count > 5) {
                break;
            }
        }
    }
}; // namespace app::rss
