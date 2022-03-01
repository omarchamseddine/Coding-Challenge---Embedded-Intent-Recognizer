#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTFACTORY_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTFACTORY_H

#include "IntentFactory.h"
#include "Intent.h"

#include <string>
#include <set>
#include <vector>
#include <memory>

// DESIGN PATTERN: Singleton and Factor Design Patterns
class IntentFactory {
public:
    IntentFactory() = default;

    static IntentFactory &GetHandler();

    std::unique_ptr<Intent> GetIntent(std::unique_ptr<std::set<int>> intentIDList);
};


#endif //EMBEDDEDINTENTRECOGNIZER_INTENTFACTORY_H
