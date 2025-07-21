#include <HTTPClient.h>
#include <M5Unified.h>
#include "rss.hpp"
#include "secrets.hpp"

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

    while (true) {
        int startIdx = payload.indexOf(tagStart, cursor);
        if (startIdx == -1) {
            break;
        }
        int endIdx = payload.indexOf(tagEnd, startIdx + tagStart.length());
        if (endIdx == -1) {
            break;
        }
        String title = payload.substring(startIdx + tagStart.length(), endIdx);
        M5.Lcd.println(1);
        M5.Lcd.println(title);

        cursor = endIdx + tagEnd.length();
        break;
    }
}