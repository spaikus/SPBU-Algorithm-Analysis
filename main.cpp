//
//  main.cpp
//  Damerau_Levenshtein_distance
//
//  Created by Боев Вячеслав on 22.11.2020.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "tests.hpp"

int main(int argc, const char * argv[]) {
    const size_t from = 400;
    const size_t to = 2000;
    const size_t step = 200;
    const size_t randTestsNum = 1;

    DamLevDist damLevDist;

    std::__fs::filesystem::create_directory("tests");

    std::ofstream worstCasesFile("tests/worst_cases.txt");
    if (!worstCasesFile.is_open()) {
        std::cout << "cannot open file tests/worst_cases.txt" << std::endl;
        return 1;
    }

    std::ofstream bestCasesFile("tests/best_cases.txt");
    if (!bestCasesFile.is_open()) {
        std::cout << "cannot open file tests/best_cases.txt" << std::endl;
        return 1;
    }

    std::ofstream randTestsFile("tests/rand_tests.txt");
    if (!randTestsFile.is_open()) {
        std::cout << "cannot open file tests/rand_tests.txt" << std::endl;
        return 1;
    }

    //idle run
    Test::averageTestExecutionTime(damLevDist, Test::getRandomString(-1), Test::getRandomString(-1));

    for (size_t N = from; N <= to; N += step) {
        for (size_t M = from; M <= to; M += step) {
            size_t testSize = N * M;

            worstCasesFile << testSize << ' ';
            worstCasesFile << N << ' ' << M << ' ';
            worstCasesFile << Test::averageCaseExecutionTime(Test::badCaseExecutionTime,
                                                             damLevDist, N, M) << '\n';

            bestCasesFile << testSize << ' ';
            bestCasesFile << N << ' ' << M << ' ';
            bestCasesFile << Test::averageCaseExecutionTime(Test::bestCaseExecutionTime,
                                                             damLevDist, N, M) << '\n';

            for (int i = 0; i < randTestsNum; ++i) {
                std::string a = Test::getRandomString(N);
                std::string b = Test::getRandomString(M);

                randTestsFile << testSize << ' ';
                randTestsFile << N << ' ' << M << ' ';
                randTestsFile << Test::averageTestExecutionTime(damLevDist, a, b) << '\n';
            }

            std::cout << testSize << ' ';
            std::cout << N << ' ' << M << '\n';
        }
    }


    bestCasesFile.close();
    worstCasesFile.close();

    return 0;
}
