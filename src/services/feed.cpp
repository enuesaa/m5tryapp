#include "feed.hpp"
#include "env/vars.hpp"
#include "services/ai.hpp"
#include <HTTPClient.h>
#include <M5Unified.h>
#include <Rss.h>
#include <ArduinoJson.h>

namespace services::feed {
    void parse() {
        HTTPClient http;
        http.begin(env::vars::RSS_FEED_URI);

        int code = http.GET();
        if (code != 200) {
            M5.Lcd.printf("HTTP Error: %d\n", code);
            return;
        }
        http.end();

        String body = http.getString();

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            M5.Display.println("JSON parse error");
            return;
        }

        JsonArray items = doc["items"];

        for (JsonObject item : items) {
            const char* title = item["title"];
            M5.Display.println(title);
            services::ai::speech(title);
        }
    }
}; // namespace services::feed
