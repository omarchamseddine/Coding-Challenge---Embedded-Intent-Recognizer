#include "IntentFactory.h"

// IntentFactory returns the same instance to adapt singleton pattern
IntentFactory &IntentFactory::GetHandler() {
    static IntentFactory handler;
    return handler;
}

std::unique_ptr<Intent> IntentFactory::GetIntent(std::unique_ptr<std::set<int>> intentIDList) {
    if (intentIDList->size() == 1) {
        switch (*intentIDList->begin()) { // Take first element from set
            case 1:
                return std::make_unique<WeatherIntent>();
            case 3:
                return std::make_unique<FactIntent>();
            default:
                return std::make_unique<NotFoundIntent>();
        }
    } else if (intentIDList->size() == 2) {
        bool isWeatherInSet = intentIDList->find(1) != intentIDList->end();
        bool isCityInSet = intentIDList->find(2) != intentIDList->end();
        if (isWeatherInSet && isCityInSet)
            return std::make_unique<WeatherCityIntent>();
    }
    return std::make_unique<NotFoundIntent>(); // not recognized
}
