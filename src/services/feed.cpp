#include "feed.hpp"
#include "env/vars.hpp"
#include <HTTPClient.h>
#include <M5Unified.h>
#include <Rss.h>

namespace services::feed {
    std::vector<String> parse() {
        String body = rss::fetch(env::vars::RSS_FEED_URI);
        auto results = rss::extract(body, "title");

        return results;
    }
}; // namespace services::feed
