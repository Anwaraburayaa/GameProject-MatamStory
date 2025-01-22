//
// Created by anwar on 1/19/2025.
//

#include "CharachterFactory.h"


std::shared_ptr<Character> CharachterFactory::CreateCharachter(const std::string &characterName) const {
    auto it = mapCharacters.find(characterName);
    if (it != mapCharacters.end())
        return it->second;
    else
        return nullptr;
}
