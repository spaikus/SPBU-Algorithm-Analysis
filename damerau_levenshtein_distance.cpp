//
//  damerau_levenshtein_distance.cpp
//  Damerau_Levenshtein_distance
//
//  Created by Боев Вячеслав on 22.11.2020.
//

#include "damerau_levenshtein_distance.hpp"
#include <vector>

DamLevDist::DamLevDist(
                       costType insertCost, costType deleteCost,
                       costType replaceCost, costType transposeCost
                       ): insertCost(insertCost), deleteCost(deleteCost),
                          replaceCost(replaceCost), transposeCost(transposeCost)
{
    if (2 * transposeCost < deleteCost + insertCost) {
        /*
         this algorithm requires doubled transpose cost to be higher
         than sum of insert and delete costs
         */
        throw "incorrect cost values initialization: 2 * transposeCost < deleteCost + insertCost";
    }
}

DamLevDist::costType DamLevDist::operator()(const std::string &a, const std::string &b) const
{
    const std::string *l, *g;

    costType insertCost, deleteCost;
    if (a.length() < b.length())
    {
        l = &a; g = &b;
        insertCost = this->insertCost;
        deleteCost = this->deleteCost;
    }
    else
    {
        l = &b; g = &a;
        insertCost = this->deleteCost;
        deleteCost = this->insertCost;
    }


    //container of indices of l-prefix last letters equal to g-prefix last letter
    size_t lLasts[26];
    for (size_t i = 0; i < 26; ++i) {
        lLasts[i] = -1;
    }
    //index of g-prefix last letter equal to l-prefix last letter
    size_t gLast;

    std::vector<std::vector<costType>> dp(l->length()+1, std::vector<costType>(g->length()+1));
    dp[0][0] = 0;
    dp[0][g->length()] = g->length() * insertCost;


    for (size_t i = 0; i < l->length(); ++i)
    {
        dp[i+1][0] = dp[i][0] + deleteCost;
        gLast = -1;

        for (size_t j = 0; j < g->length(); ++j)
        {
            dp[0][j+1] = dp[0][j] + insertCost;

            if ((*l)[i] == (*g)[j])
            {
                gLast = j;
                dp[i+1][j+1] = dp[i][j];
            }
            else
            {
                size_t lLast = lLasts[(*g)[j] - 'a'];

                costType dpVal = dp[i][j] + replaceCost;
                costType insVal = dp[i+1][j] + insertCost;
                costType delVal = dp[i][j+1] + deleteCost;

                dpVal = std::min(dpVal, std::min(insVal, delVal));
                if ((lLast + 1 != 0) and (gLast + 1 != 0))
                {
                    costType transVal = dp[lLast][gLast] + (i-lLast-1)*deleteCost +
                                        (j-gLast-1)*insertCost + transposeCost;
                    dpVal = std::min(dpVal, transVal);
                }
                dp[i+1][j+1] = dpVal;
            }
        }

        lLasts[(*l)[i] - 'a'] = i;
    }

    return dp[l->length()][g->length()];
}
