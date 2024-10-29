#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Problem
{
    string idProblem;
    string speciality;
};

struct Doctor
{
    string idDoctor;
    string speciality;
};

int main()
{
    ifstream inFile("input.txt");

    int no_problems;
    int no_doctors;
    bool ok;

    inFile >> no_problems;
    vector<Problem> problems(no_problems);

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> problems[i].idProblem;
        inFile >> problems[i].speciality;
    }

    inFile >> no_doctors;
    vector<Doctor> doctors(no_doctors);

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> doctors[i].idDoctor;
        inFile >> doctors[i].speciality;
    }

    for (int i = 0; i < no_problems; i++)
    {
        ok = false;

        for (int j = 0; j < no_doctors; j++)
        {
            if (problems[i].speciality == doctors[j].speciality)
            {
                cout << problems[i].idProblem << " Acceptat" << endl;
                ok = true;

                break;
            }
        }

        if (!ok)
        {
            cout << problems[i].idProblem << " Respins" << endl;
        }
    }

    return 0;
}