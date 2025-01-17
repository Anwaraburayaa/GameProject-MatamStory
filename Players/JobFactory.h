#ifndef JOBFACTORY_H
#define JOBFACTORY_H
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
        {WARRIOR, std::shared_ptr<Warrior>()},
        {MAGICIAN, std::shared_ptr<Magician>()},
        {ARCHER, std::make_shared<Archer>()},
    };
    public:
    std::shared_ptr<Job> createJob(const std::string& jobName) const;
};


#endif //JOBFACTORY_H
