#include "IntentRecognizer.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// IntentRecognizer returns the same instance to adapt singleton pattern
IntentRecognizer &IntentRecognizer::GetHandler() {
    static IntentRecognizer handler;
    return handler;
}

bool IntentRecognizer::RecognizeIntents(std::string line) {
    if (CheckInputString(line)) {
        return EXIT_FAILURE; // Exit sequence is entered
    }
    std::unique_ptr<std::set<int>> listIntentID = GetIntentIDList(line);
    std::unique_ptr<Intent> intent = intentFactory.GetIntent(std::move(listIntentID));
    return intent->Handle();
}

IntentRecognizer::IntentRecognizer() {
    try {
        if (InitTrie()) {
            throw; // Can not initialize
        }
    }
    catch (...) {
        cout << "Intent recognizer cannot be initialized!" << endl;
    }
}

bool IntentRecognizer::ReadJsonFile(nlohmann::json &jsonObject, std::string fileName = Word2IntentFile) {
    ifstream jsonStream("../../data/" + fileName);
    if (!jsonStream.is_open()) {
        return EXIT_FAILURE;
    } else {
        jsonStream >> jsonObject;
        jsonStream.close();
        return EXIT_SUCCESS;
    }
}

bool IntentRecognizer::InitTrie() {
    int intentID;
    nlohmann::json jsonObject;
    string word = "", intent = "";

    if (ReadJsonFile(jsonObject)) {
        return EXIT_FAILURE; // No file
    }

    auto GetIndex = [](vector<string> list, std::string wanted) {
        int Index = 0;
        for (auto element: list) {
            if (element == wanted)
                return Index;
            Index++;
        }
        return -1; // If not in vector
    };

    auto PrintIntentHandleNotExist = [](std::string word, std::string intent) {
        cout << "JSON Input: " << word << " for intent " << intent << " can not handled" << endl;
    };

    for (auto &el: jsonObject.items()) {
        word = el.key();
        intent = el.value();
        MakeLowerCase(word);
        MakeLowerCase(intent);

        intentID = GetIndex(definedIntents, intent);
        if (intentID != -1) {
            headTrie->insert(word, intentID);
        } else {
            PrintIntentHandleNotExist(word, intent);
        }
    }
    return EXIT_SUCCESS;
}

bool IntentRecognizer::CheckInputString(std::string inputStr) {
    stringstream stream(inputStr);
    string word = "";
    int numArg = 0;
    while (stream >> word) {
        numArg++;
    }

    if (numArg == 0) { // Enter returns as exit function
        return EXIT_FAILURE;   // Return to command line, Exit Function
    } else if (numArg >= maxArgNum) {
        PrintWrongInput();
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

std::unique_ptr<std::set<int>> IntentRecognizer::GetIntentIDList(std::string inputStr) {
    stringstream stream(inputStr);
    string word;
    std::unique_ptr<std::set<int>> intentIDList = std::make_unique<std::set<int>>();
    int intentID;

    intentIDList->clear();
    while (stream >> word) {
        MakeLowerCase(word);
        intentID = headTrie->search(word);
        if (intentID)
            intentIDList->insert(intentID);
    }
    return intentIDList;
}

void IntentRecognizer::MakeLowerCase(std::string &inputStr) {
    int j = 0;
    for (int i = 0; i < inputStr.size(); i++) {
        // Store only letters until non-alphabet characters {'.',',',';',...)
        if (inputStr[i] >= 'A' && inputStr[i] <= 'Z') {
            inputStr[j] = inputStr[i] - 'Z' + 'z';
            j++;
        } else if (inputStr[i] >= 'a' && inputStr[i] <= 'z') {
            inputStr[j] = inputStr[i];
            j++;
        } else {
            inputStr = inputStr.substr(0, j);
            break;
        }
    }
}

void IntentRecognizer::PrintWrongInput() {
    cout << "Wrong input" << endl;
}
