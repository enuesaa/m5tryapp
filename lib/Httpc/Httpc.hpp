#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <map>

namespace httpc {
    using Headers = std::map<String, String>;

    struct Response {
        int status;
        bool err; // include status is not 200
        String body;
    };
    struct ResponseJSON {
        int status;
        bool err;
        JsonDocument data;
    };

    Response get(const String& url, const Headers& headers = {});
    ResponseJSON getj(const String& url, const Headers& headers = {});
} // namespace httpc
