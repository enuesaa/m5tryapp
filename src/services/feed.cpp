#include "feed.hpp"
#include "env/vars.hpp"
#include <ArduinoJson.h>
#include <M5Unified.h>
#include <Httpc.h>

namespace services::feed {
    std::vector<String> parse() {
        std::vector<String> list;

        auto res = httpc::getj(env::vars::RSS_FEED_URI);
        if (res.err == true) {
            M5.Lcd.println("aHTTP Error");
            M5.Lcd.println(res.status);
            return list;
        }
        JsonArray items = res.data["items"];

        for (JsonObject item : items) {
            String title = item["title"];
            String description = item["description"];
            String content = title + ".\n" + description;
            list.push_back(content);
        }
        return list;
    }
}; // namespace services::feed
