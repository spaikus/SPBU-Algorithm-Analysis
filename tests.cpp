//
//  tests.cpp
//  Damerau_Levenshtein_distance
//
//  Created by Боев Вячеслав on 23.11.2020.
//

#include "tests.hpp"
#include <vector>
#include <chrono>

std::string Test::getRandomString(size_t length)
{
    if (length + 1 == 0) {
        length = rand() % 1000 + 1;
    }

    std::string randomString;
    while (length) {
        randomString.push_back(alphabet[rand() % alphabet.length()]);
        --length;
    }

    return randomString;
}


Test::timeType Test::testExecutionTime(const DamLevDist &damLevDist, const std::string &a, const std::string &b)
{
    auto start = std::chrono::high_resolution_clock::now();
    damLevDist(a, b);
    auto stop = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

Test::timeType Test::worstCaseExecutionTime(const DamLevDist &damLevDist, size_t N, size_t M)
{
    std::string a = N ? "z" + std::string(N-1, 'a') : "";
    std::string b = M ? "a" + std::string(M-1, 'z') : "";

    return testExecutionTime(damLevDist, a, b);
}
Test::timeType Test::badCaseExecutionTime(const DamLevDist &damLevDist, size_t N, size_t M)
{
    std::string shakenAlphabet = "jnfkxugzclrawbomvepsdyhtiq";
    std::string a;
    while (a.length() < N) {
        a.append(shakenAlphabet);
    }
    a.resize(N);

    shakenAlphabet = "ycxjfgrlamksvzbiwdohptqeun";
    std::string b;
    while (b.length() < M) {
        b.append(shakenAlphabet);
    }
    b.resize(M);


    return testExecutionTime(damLevDist, a, b);
}
Test::timeType Test::bestCaseExecutionTime(const DamLevDist &damLevDist, size_t N, size_t M)
{
    std::string a = std::string(N, 'a');
    std::string b = std::string(M, 'a');

    return testExecutionTime(damLevDist, a, b);
}


Test::timeType Test::averageTestExecutionTime(const DamLevDist &damLevDist, const std::string &a, const std::string &b)
{
    timeType averageTime = 0;
    for (int i = 0; i < averagingTestsNum; ++i) {
        averageTime += testExecutionTime(damLevDist, a, b);
    }

    return averageTime / averagingTestsNum;
}

Test::timeType Test::averageCaseExecutionTime(Test::timeType (*caseFun)(const DamLevDist &damLevDist, size_t N, size_t M),
                                              const DamLevDist &damLevDist, size_t N, size_t M)
{
    timeType averageTime = 0;
    for (int i = 0; i < averagingTestsNum; ++i) {
        averageTime += caseFun(damLevDist, N, M);
    }

    return averageTime / averagingTestsNum;
}


std::string Test::testCorrectness(const DamLevDist &damLevDist)
{
    struct PredefinedTest
    {
        PredefinedTest(const std::string &a, const std::string &b, DamLevDist::costType cost):
            a(a), b(b), cost(cost){}
        std::string a, b;
        DamLevDist::costType cost;
    };

    const std::vector<PredefinedTest> predefinedTests = {
        PredefinedTest("abc","abc",0),
        PredefinedTest("","abc",3),
        PredefinedTest("mom","dad",3),
        PredefinedTest("dog","dogs",1),
        PredefinedTest("true","false",4),
        PredefinedTest("abc","ca",2),
        PredefinedTest("tee","tree",1),
        PredefinedTest("email","mails",2),
        PredefinedTest("profit","gifts",5)
    };

    std::string response;

    //predefined tests
    for (const auto & test: predefinedTests)
    {
        auto cost = damLevDist(test.a, test.b);
        response.append("Test: '"+test.a+"' <-"+std::to_string(cost)+"-> '"+test.b+"': "+
                        (cost == test.cost ? "ok" : "FAIL")+"\n");
    }

    //symmetry tests
    bool f = true;
    for (int i = 0; i < 5; ++i)
    {
        std::string a, b;
        a = getRandomString(-1);
        b = getRandomString(-1);

        if (damLevDist(a, b) != damLevDist(b, a)) {
            f = false;
            break;
        }
    }
    response.append((std::string)"Test(symmetry): " + (f ? "ok" : "FAIL") + "\n");

    //test trinagle inequality
    f = true;
    for (int i = 0; i < 5; ++i)
    {
        std::string a, b, c;
        a = getRandomString(-1);
        b = getRandomString(-1);
        c = getRandomString(-1);

        if (damLevDist(a, b) + damLevDist(b, c) < damLevDist(a, c)) {
            f = false;
            break;
        }
    }
    response.append((std::string)"Test(trinagle inequality): " + (f ? "ok" : "FAIL") + "\n");


    return response;
}
