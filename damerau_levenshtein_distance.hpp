//
//  damlevdist.hpp
//  Damerau_Levenshtein_distance
//
//  Created by Боев Вячеслав on 22.11.2020.
//

#ifndef damerau_levenshtein_distance_hpp
#define damerau_levenshtein_distance_hpp

#include <string>

class DamLevDist {
public:
    using costType = unsigned long;

    DamLevDist(costType insertCost = 1, costType deleteCost = 1,
               costType replaceCost = 1, costType transposeCost = 1);
    costType operator()(const std::string &a, const std::string &b) const;

private:
    costType insertCost;
    costType deleteCost;
    costType replaceCost;
    costType transposeCost;
};

#endif /* damerau_levenshtein_distance_hpp */
