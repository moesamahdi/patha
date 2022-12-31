// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "CSVParser.h"
#include "Database.h"
#include "DBController.h"

int main()
{
    // Here we parse the CSVs and initialise the Maps
    CSVParser parser;
    std::string bloodResultsText = parser.readFile("../../data/blood-results.csv");
    parser.parseBloodResultsCSV(bloodResultsText);
    std::string combinationsText = parser.readFile("../../data/combinations.csv");
    parser.parseCombinationsCSV(combinationsText);

    // test some bloodresult values and print outcome ranking
    DBController controller;
    controller.setBloodResultValue("B1", 20);
    controller.setBloodResultValue("B2", 29);
    controller.setBloodResultValue("B3", 9);
    controller.rankOutcomes();
    for (std::string& outcomeID : DB::HighestRankedOutcomes)
    {
        Outcome& outcome = DB::Outcomes[outcomeID];
        std::cout << outcomeID << " , Outcome Text - " << outcome.getOutcomeText() << " , Suggestion Text - " << outcome.getSuggestionText() << std::endl;
    }

}
