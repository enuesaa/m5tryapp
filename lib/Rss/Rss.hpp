#pragma once

#include <Arduino.h>
#include <vector>

namespace rss {
    String fetch(const String& url);
    std::vector<String> extract(const String& body, const String& tag);
} // namespace rss
