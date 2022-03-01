#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H

#include "IntentRecognizerInterface.h"
#include "TrieWithIntents.h"
#include "IntentFactory.h"
#include "Intent.h"

#include "json.hpp"

#include <string>
#include <vector>
#include <set>

// Handle command line commands
// DESIGN PATTERN: Singleton Design Pattern
class IntentRecognizer : public IntentRecognizerInterface {
private:
    const int maxArgNum = 15;

    inline static const std::string Word2IntentFile = "Word2Intent.json";

    inline static const std::vector<std::string> definedIntents{"not_found", "weather", "city", "fact"};

private:
    std::unique_ptr<TrieWithIntents> headTrie = std::make_unique<TrieWithIntents>();

    IntentFactory &intentFactory = IntentFactory::GetHandler();

public:
    static IntentRecognizer &GetHandler();

    IntentRecognizer(const IntentRecognizer &orig) = delete;

    bool RecognizeIntents(std::string line) override;

    virtual ~IntentRecognizer() = default;

private:
    IntentRecognizer();

    bool ReadJsonFile(nlohmann::json &jsonObject, std::string fileName);

    bool InitTrie();

    bool CheckInputString(std::string inputStr);

    std::unique_ptr<std::set<int>> GetIntentIDList(std::string inputStr);

    void MakeLowerCase(std::string &inputStr);

    void PrintWrongInput();
};

#endif //EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H