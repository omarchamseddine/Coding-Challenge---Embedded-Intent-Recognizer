#ifndef EMBEDDEDINTENTRECOGNIZER_INTENT_H
#define EMBEDDEDINTENTRECOGNIZER_INTENT_H

class Intent {
public:
    virtual bool Handle() = 0;

    virtual ~Intent() = default;
};

// Simply add new intent recognizers if introduced
class WeatherIntent : public Intent {
public:
    bool Handle();
};

class WeatherCityIntent : public Intent {
public:
    bool Handle();
};

class FactIntent : public Intent {
public:
    bool Handle();
};

class NotFoundIntent : public Intent {
public:
    bool Handle();
};

#endif //EMBEDDEDINTENTRECOGNIZER_INTENT_H
