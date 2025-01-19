//
// Created by anwar on 1/19/2025.
//

#ifndef CHARACHTERFACTORY_H
#define CHARACHTERFACTORY_H

#pragma once

#include "Character.h"
#include <map>
#include <memory>

#define RESPONSIBLE "Responsible"
#define RISKTAKING "RiskTaking"



class CharachterFactory {

    std::map<std::string, std::shared_ptr<Character>> mapCharacters =
           {{RESPONSIBLE, std::make_shared<Responsiple>()},
            {RISKTAKING,  std::make_shared<RiskTaking>()},
           };

public:
    std::shared_ptr<Character> Create(const std::string &characterName) const;

};



#endif //CHARACHTERFACTORY_H
