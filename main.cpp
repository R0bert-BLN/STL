#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
	ifstream inFile("input2.txt");

	if (!inFile.is_open())
	{
		cerr << "Eroare la deschiderea fisierului" << endl;

		return 1;
	}

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

	vector<string> busyDoctors;

	for (const auto& problem : problems)
	{
		for (const auto& doctor : doctors)
		{
			if (problem.speciality == doctor.speciality)
			{
				if (find(busyDoctors.begin(), busyDoctors.end(), doctor.idDoctor) == busyDoctors.end())
				{
					cout << doctor.idDoctor << " " << problem.idProblem << endl;

					busyDoctors.emplace_back(doctor.idDoctor);

					break;
				}
			}
		}
	}

	return 0;
}