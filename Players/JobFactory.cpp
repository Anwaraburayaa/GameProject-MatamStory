//
// Created by anwar on 1/18/2025.
//

#include "JobFactory.h"
std::shared_ptr<Job> JobFactory::createJob(const std::string &jobName) const{
    auto it = jobsMap.find(jobName);
    if (it != jobsMap.end())
        return it->second;
    else
        return nullptr;
}