#include "feed.hpp"
#include "env/vars.hpp"
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

        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            M5.Display.println("JSON parse error");
            return;
        }

        const char* url = doc["feed"]["url"]; 
        M5.Display.println("url:");
        M5.Display.println(url);
    }
}; // namespace services::feed
