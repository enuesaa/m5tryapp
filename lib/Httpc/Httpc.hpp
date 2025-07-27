#pragma once

#include <Arduino.h>

namespace httpc {
    struct Response {
        int status;
        String body;
    };
    struct ResponseJSON {
        int status;
        String body;
    };

    Response get(const String& url);
    ResponseJSON getj(const String& url);
} // namespace httpc
