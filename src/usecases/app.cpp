#include "app.hpp"

#include "services/ai.hpp"
#include "services/feed.hpp"
#include <ArduinoJson.h>
#include <M5Unified.h>
#include <vector>

namespace usecases::app {
    void start() {
        std::vector<String> feeditems = services::feed::parse();
        const String &aihead = "この AWS NEWS を日本語で20文字程度にまとめて。不要な文言は出力しないで。";

        for (const String &item : feeditems) {
            String input = aihead + "\n" + item;
            String output = services::ai::chat(input);
            M5.Display.println(output);
            services::ai::speech(output);
        }
    }
} // namespace usecases::app
