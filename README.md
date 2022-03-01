# Embedded Intent Recognizer
Embedded Intent Recognizer is a simple, small, case-insensitive intent recognition command line tool using modern C++. User can fill the human-readable .json file easily with "word": "intent" pairs as in sample file to handle user-specific word-intent pairs. 

## Compilation
Run the following commands to test the project:
```bash
 mkdir build && cd build && cmake .. && make
 cd src
./EmbeddedIntentRecognizer 
```
## Usage
Example usage is given below: 


![video](https://user-images.githubusercontent.com/60155886/156179075-aed95dd0-3d74-49b4-9321-e983238c3d1e.gif)

## Files explanation 
**Readme.md** is a readme file to describe how to code act and how to compile and run.

**CMakeList.txt** file contains a set of directives and instructions describing the project's source files and targets (
executable, library, or both).

**IntentRecognizer (.cpp, .h)** is the class for handling the command line inputs and recognize the intents. If intent
can not be found, requests a new input. Single enter (without query) and Linux escape (ctrl+c) are handled as an exit.
IntentRecognizer follows the singleton and factory design approaches. The singleton design approach is used because
exactly one intent recognizer is needed to coordinate command-line actions across the system. IntentRecognizer first
initializes the modified Trie using TrieWithIntents class with the inputs in Word2Intent.json handled using nlohmann::
json library.

**IntentRecognizerInterface.h** is the header file for Intent Recognizer Interface class, it consists of a pure virtual
class and any change on the intent recognizer handler can be handled thanks to the adapter design pattern.

**IntentFactory (.cpp, .h)** is the class for getting Intent objects. This class has a Simple factory pattern that it
has one creation method with a large conditional that based on method parameters chooses which product class to
instantiate and then return. The returned Intent objects can be called with their handle methods in IntentRecognizer. By
the advantage of this pattern, any new inserted query can be called easily.

**Intent (.cpp, .h)** is the class for creating Intent objects. Current supported intents are {"Weather","Weather City"
, "Fact"}. A new intent can be inserted with its handle to enlarge recognition capability to be called in IntentFactory.

**TrieWithIntents (.cpp, .h)** is the class to create modified Trie which is a Trie having ID on their bottom leaf.

**testIntentRecognizer (.cpp,)** is the test file for IntentRecognizer class using Google Test.
