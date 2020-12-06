//
//  tests.hpp
//  Damerau_Levenshtein_distance
//
//  Created by Боев Вячеслав on 23.11.2020.
//

#ifndef tests_hpp
#define tests_hpp

#include "damerau_levenshtein_distance.hpp"

namespace Test
{
using timeType = unsigned long long;
const int averagingTestsNum = 10;
const std::string alphabet =
    "abcdefghijklmnopqrstuvwxyz";

std::string getRandomString(size_t length);

timeType testExecutionTime(const DamLevDist &damLevDist, const std::string &a, const std::string &b);

timeType worstCaseExecutionTime(const DamLevDist &damLevDist, size_t N, size_t M);
timeType badCaseExecutionTime(const DamLevDist &damLevDist, size_t N, size_t M);
timeType bestCaseExecutionTime(const DamLevDist &damLevDist, size_t N, size_t M);

timeType averageTestExecutionTime(const DamLevDist &damLevDist, const std::string &a, const std::string &b);
timeType averageCaseExecutionTime(timeType (*caseFun)(const DamLevDist &damLevDist, size_t N, size_t M),
                                  const DamLevDist &damLevDist, size_t N, size_t M);

std::string testCorrectness(const DamLevDist &damLevDist);
}

#endif /* tests_hpp */
