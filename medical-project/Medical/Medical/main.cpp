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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
