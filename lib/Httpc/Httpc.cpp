#include "Httpc.hpp"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5Unified.h>

namespace httpc {
    Response get(const String& url, const Headers& headers) {
        Response res;

        HTTPClient http;
        http.begin(url);

        for (const auto& [key, value] : headers) {
            http.addHeader(key, value);
        }

        res.status = http.GET();

        if (res.status != 200) {
            M5.Lcd.printf("HTTP Error: %d\n", res.status);
            res.err = true;
            http.end();
            return res;
        }
        res.err = false;
        res.body = http.getString();
        http.end();

        return res;
    }

    ResponseJSON getj(const String& url, const Headers& headers) {
        ResponseJSON res;

        Response plain = get(url, headers);
        if (plain.err) {
            res.err = true;
            return res;
        }

        JsonDocument doc;
        DeserializationError err = deserializeJson(doc, plain.body);
        if (err) {
            M5.Lcd.println("JSON Decode Error");
            res.err = true;
            return res;
        }
        res.err = false;
        res.data = doc;

        return res;
    }

} // namespace httpc
