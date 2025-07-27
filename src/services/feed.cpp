#include "feed.hpp"
#include "env/vars.hpp"
#include "services/ai.hpp"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <M5Unified.h>
#include <Rss.h>

namespace services::feed {
    std::vector<String> parse() {
        std::vector<String> list;

        HTTPClient http;
        http.begin(env::vars::RSS_FEED_URI);

        int code = http.GET();
        if (code != 200) {
            M5.Lcd.printf("HTTP Error: %d\n", code);
            return list;
        }
        http.end();

        String body = http.getString();

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            M5.Display.println("JSON parse error");
            return list;
        }
        JsonArray items = doc["items"];

        for (JsonObject item : items) {
            String title = item["title"];
            String description = item["description"];
            String content = title + ".\n" + description;
            list.push_back(content);
        }
        return list;
    }
}; // namespace services::feed
