#include "IntentRecognizer.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

IntentRecognizerInterface *pIntentRecognizer = &IntentRecognizer::GetHandler();

std::string RecordRecognizeIntentsMethod(std::string inputLine) {
    testing::internal::CaptureStdout();
    pIntentRecognizer->RecognizeIntents(inputLine);
    return testing::internal::GetCapturedStdout();
}

TEST(IntentRecognizerInterface_UnitTests, Weather) {
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("What is the weather like today?"));
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("Is it rainy?"));
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("Will it be calm, tomorrow?"));
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("Was it calm, yesterday?"));
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("How is the weather?"));
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("weather forecast"));
    EXPECT_EQ("Intent: Get Weather\n", RecordRecognizeIntentsMethod("weather in celcius"));
}

TEST(IntentRecognizerInterface_UnitTests, WeatherCity) {
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("What is the weather like in Paris today?"));
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("Is Berlin rainy?"));
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("Will Ulm be calm, tomorrow?"));
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("Was Kuala Lumpur calm, yesterday?"));
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("How is the weather in Ankara?"));
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("weather forecast for Dortmund"));
    EXPECT_EQ("Intent: Get Weather City\n", RecordRecognizeIntentsMethod("weather in celcius for Munich"));
}

TEST(IntentRecognizerInterface_UnitTests, Fact) {
    EXPECT_EQ("Intent: Get Fact\n", RecordRecognizeIntentsMethod("Tell me an interesting fact."));
    EXPECT_EQ("Intent: Get Fact\n", RecordRecognizeIntentsMethod("What is the fact?"));
}

TEST(IntentRecognizerInterface_UnitTests, NotFound) {
    EXPECT_EQ("Intent: Not Found, Please Try Again\n", RecordRecognizeIntentsMethod("Make me a joke."));
    // There is no "Fact City" intent so not found
    EXPECT_EQ("Intent: Not Found, Please Try Again\n",
              RecordRecognizeIntentsMethod("Tell me an interesting fact about Ulm"));
    EXPECT_EQ("Intent: Not Found, Please Try Again\n", RecordRecognizeIntentsMethod("How are you?"));
}

TEST(IntentRecognizerInterface_UnitTests, WrongInput) {
    string input = "input", inputLine = "";
    for (int i = 0; i < 15; i++) {
        inputLine += input + " ";
    }
    EXPECT_EQ("Wrong input\n", RecordRecognizeIntentsMethod(inputLine));
}

TEST(IntentRecognizerInterface_UnitTests, Exit) {
    EXPECT_EQ("", RecordRecognizeIntentsMethod("\n"));
}