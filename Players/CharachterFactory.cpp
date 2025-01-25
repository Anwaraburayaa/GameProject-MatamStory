//
// Created by anwar on 1/19/2025.
//

#include "CharachterFactory.h"


std::shared_ptr<Character> CharachterFactory::charachterCreator(const std::string &characterName) const {
    auto it = CharactersMap.find(characterName);
    if (it != CharactersMap.end())
        return it->second;
    else
        return nullptr;
}
