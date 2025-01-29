//
// Created by anwar on 1/19/2025.
//



#pragma once

#include "Character.h"
#include <map>
#include <memory>

#define RESPONSIBLE "Responsible"
#define RISKTAKING "RiskTaking"



class CharachterFactory {

    std::map<std::string, std::shared_ptr<Character>> CharactersMap =
           {{RESPONSIBLE, std::make_shared<Responsible>()},
            {RISKTAKING,  std::make_shared<RiskTaking>()},
           };

public:
    std::shared_ptr<Character> charachterCreator(const std::string &characterName) const;

};


