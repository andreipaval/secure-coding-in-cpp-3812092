// Secure Coding in C++
// Challenge 02_05
// Secure a data parsing function, by Eduardo Corpeño

#include <iostream>
#include <string>
#include <map>
#include <sstream>

std::map<std::string, std::string> parseSettings(const std::string& input){
    std::map<std::string, std::string> result;
    std::istringstream ss(input);
    std::string pair;

    while (std::getline(ss, pair, ',')){
        size_t eq = pair.find('=');

        if (eq == std::string::npos){
            std::cerr << "Error: Missing '=' in pair: " << pair << "\n";
            continue; // Skip invalid pair
        }

        // Unsafe: no check for missing '=', empty keys or values, 
        // duplicate keys, spaces, or non-numeric values.
        std::string key = pair.substr(0, eq);
        std::string value = pair.substr(eq + 1);

        if (key.empty() || value.empty()){
            std::cerr << "Error: Empty key or value in pair: " << pair << "\n";
            continue; // Skip empty pair
        }
        if (key.find(' ') != std::string::npos || value.find(' ') != std::string::npos){
            std::cerr << "Error: Spaces are not allowed in key or value: " << pair << "\n";
            continue; // Skip pair with spaces
        }
        if (result.find(key) != result.end()){
            std::cerr << "Error: Duplicate key found: " << key << "\n";
            continue; // Skip duplicate key
        }
        int i = 0;
        try {
            i = std::stoi(value); // Check if value is numeric
        } catch (...) {
            std::cerr << "Error: Non-numeric value for key " << key << ": " << value << "\n";
            continue; // Skip non integer pair value
        }
        if (i < 0){
            std::cerr << "Error: Negative value for key " << key << ": " << value << "\n";
            continue; // Skip negative values
        }

        result[key] = value; // silently overwrites
    }
    return result;
}

int main(){
    std::string rawInput;
    std::cout << "Enter settings (key=value,key=value,...): ";
    std::getline(std::cin, rawInput);

    auto settings = parseSettings(rawInput);

    std::cout << "Parsed settings:\n";
    for (const auto& [k, v] : settings)
        std::cout << k << ": " << v << "\n";

    std::cout << std::endl;
    return 0;
}
