#pragma once

namespace env::vars {

    static const char *WIFI_SSID = "your_ssid";
    static const char *WIFI_PASSWORD = "your_password";
    static const char *INFLUX_URL = "http://<ip>:8086/api/v2/write?org=m5tryapp&bucket=m5tryapp&precision=s";
    static const char *OPENAI_APIKEY = "";
    // required JSON format. not XML
    static const char *RSS_FEED_URI = "https://api.rss2json.com/v1/api.json?rss_url=https%3A%2F%2Faws.amazon.com%2Fabout-aws%2Fwhats-new%2Frecent%2Ffeed%2F";

} // namespace env::vars
