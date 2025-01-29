
#pragma once

#include "Job.h"
#include <map>
#include <memory>

#define WARRIOR "Warrior"
#define ARCHER "Archer"
#define MAGICIAN "Magician"


class JobFactory {
private:
    std::map<std::string, std::shared_ptr<Job> > jobsMap =
    {
        {WARRIOR, std::make_shared<Warrior>()},
        {MAGICIAN, std::make_shared<Magician>()},
        {ARCHER, std::make_shared<Archer>()},
    };
    public:
    std::shared_ptr<Job> jobCreator(const std::string& jobName) const;
};
