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

        String input = "最新の AWS NEWS なんだけど、ざっくり日本語でまとめて。";
        JsonArray items = doc["items"];

        for (JsonObject item : items) {
            const char* title = item["title"];
            input = input + title + "\n";
        }

        String output = services::ai::chat(input);
        M5.Display.println(output);
        M5.Display.println("chat");

        services::ai::speech(output);
    }
}; // namespace services::feed
