#include <Arduino.h>
#include <unity.h>
#include <Rss.h>

void test_extract() {
    String xml =
        "<rss><channel>"
        "<title>Feed Title</title>"
        "<item><title>Item 1</title></item>"
        "<item><title>Item 2</title></item>"
        "<item><title>Item 3</title></item>"
        "</channel></rss>";

    auto results = rss::extract(xml, "title");

    TEST_ASSERT_EQUAL(4, results.size());
    TEST_ASSERT_EQUAL_STRING("Feed Title", results[0].c_str());
    TEST_ASSERT_EQUAL_STRING("Item 1", results[1].c_str());
    TEST_ASSERT_EQUAL_STRING("Item 2", results[2].c_str());
    TEST_ASSERT_EQUAL_STRING("Item 3", results[3].c_str());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_extract);
    UNITY_END();
}

void loop() {}
