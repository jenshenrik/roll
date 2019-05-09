#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <time.h>

using namespace std;

// returns a random int in range 1-{faces}
int rollDie(int faces);
// rolls a number of dice of a given type, and saves results in given array
void rollAllDice(int numDice, int faces, int results[]);
// returns the sum of the elements in the array. numDice == size of array
int sum(int rolls[], int numDice);
// parses the input and saves it in the given string
void parseInput(int *numDice, int *faces, int *modifier, string input);

int main(int argc, char* argv[])
{
    // Check for only a single argument. Probably print usage.
    if (argc != 2)
    {
        cout << "Wrong, dummy. One argument only." << endl;
        return 1;
    }

    // initialize random seed
    srand(time(NULL));
    
    // parse input string into number of dice, 
    // type (faces) of dice, and modifier
    string inputString(argv[1]);
    int numDice = 1;
    int* numDicePtr = &numDice;
    int faces;
    int* facesPtr = &faces;
    int modifier;
    int* modifierPtr = &modifier;
    parseInput(numDicePtr, facesPtr, modifierPtr, inputString);

    // rolling dice
    int results[numDice];
    rollAllDice(numDice, faces, results);
    int sumOfRolls = sum(results, numDice);
    int finalResult = sumOfRolls + modifier;

    cout << "Input received: " << inputString << endl;
    cout << "Rolled " << numDice << "d" << faces;
    cout << " for a result of" << endl;
    for (int r : results)
    {
        cout << r << " ";
    }
    cout << endl;
    cout << "Resulting in a sum of " << sumOfRolls;
    cout <<", modified to " << finalResult << endl;
    return 0;
}

int rollDie(int faces)
{
    return rand() % faces + 1;
}
void rollAllDice(int numDice, int faces, int results[])
{
    int i;
    for (i = 0; i < numDice; i++)
    {
        results[i] = rollDie(faces);
    }
}
int sum(int rolls[], int numDice)
{
    int i, sum = 0;
    for (i = 0; i < numDice; i++)
    {
        sum += rolls[i];
    }
    return sum;
}
void parseInput(int *numDice, int *faces, int *modifier, string input)
{
    regex re("^(\\d+)d(\\d+)([\\+|-]\\d+)?");
    smatch m;
    regex_search(input, m, re);

    *numDice = stoi(m[1]);
    *faces = stoi(m[2]);
    *modifier = 0;
    // length of m seems to vary depending on the number of
    // digits. Should probably look into regex match.
    if (m.length() >= 4)
    {
        *modifier = stoi(m[3]);
    }
}
