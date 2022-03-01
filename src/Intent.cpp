#include "Intent.h"
#include <string>
#include <iostream>

using namespace std;

bool WeatherIntent::Handle() {
    cout << "Intent: Get Weather" << endl;
    return EXIT_SUCCESS;
}

bool WeatherCityIntent::Handle() {
    cout << "Intent: Get Weather City" << endl;
    return EXIT_SUCCESS;
}

bool FactIntent::Handle() {
    cout << "Intent: Get Fact" << endl;
    return EXIT_SUCCESS;
}

bool NotFoundIntent::Handle() {
#ifdef EXIT_AFTER_WRONG_INPUT
    cout << "Intent: Not found" << endl;
    return EXIT_FAILURE; // If exit after wrong input is the specification
#else
    cout << "Intent: Not Found, Please Try Again" << endl;
    return EXIT_SUCCESS; // If continue processing after wrong input is the specification
#endif
}