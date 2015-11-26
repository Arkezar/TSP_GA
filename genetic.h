#ifndef GA_H
#define GA_H
#include <vector>
#include <unordered_map>
#include "data.h"
#include "dataloader.h"
// INIT - create random candidate solutions
// EVALUATE each candidate
// WHILE( I < GENERATION NUMBER  )
//	SELECT PARENTS
//	RECOMBINE PAIRS OF PARENTS
//	MUTATE OFFSPRING
//	EVALUATE NEW CANDIDATES
//	SELECT CANDIDATES FOR NEXT GENERATION

std::vector<City> generateRandomCandidate(std::vector<City> cities);
double candidateEvaluation(const std::vector<City>& candidate, const std::unordered_map< std::pair<City, City>, double, pairhash>& distances);

#endif
