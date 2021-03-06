// task1find_max.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindMax.h"
#include <iostream>
#include <string>

struct Athlete
{
	std::string fullName;
	float growth;
	float weight;
};

Athlete FindAthleteWithMaxGrowth(const std::vector<Athlete>& athletes);
Athlete FindAthleteWithMaxWeight(const std::vector<Athlete>& athletes);
void PrintAthleteInfo(const Athlete athlete, const std::string& infoString);

int main()
{
	std::vector<Athlete> athletes{ { "Vacya1", 6.3f, 50.1f },
		{ "Vacya2", 8.3f, 0.1f },
		{ "Vacya3", 7.3f, 100.1f } };

	PrintAthleteInfo(FindAthleteWithMaxGrowth(athletes), "maxGrowthAthlete: ");
	PrintAthleteInfo(FindAthleteWithMaxWeight(athletes), "maxWeightAthlete: ");

	return 0;
}

void PrintAthleteInfo(const Athlete athlete, const std::string& infoString)
{
	std::cout << infoString << athlete.fullName << " " << athlete.growth << " " << athlete.weight << std::endl;
}

Athlete FindAthleteWithMaxGrowth(const std::vector<Athlete>& athletes)
{
	Athlete maxGrowthAthlete;
	FindMax(athletes, maxGrowthAthlete, [](const auto& x, const auto& y) {
		return x.growth < y.growth;
	});

	return maxGrowthAthlete;
}

Athlete FindAthleteWithMaxWeight(const std::vector<Athlete>& athletes)
{
	Athlete maxWeightAthlete;
	FindMax(athletes, maxWeightAthlete, [](const auto& x, const auto& y) {
		return x.weight < y.weight;
	});

	return maxWeightAthlete;
}
