#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
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
	ifstream file("input.txt");

	if (!file.is_open())
	{
		cerr << "Error opening file" << endl;

		return 1;
	}

	int noProblems;
	int noDoctors;

	file >> noProblems;
	vector<Problem> problems(noProblems);

	for (int i = 0; i < noProblems; i++)
	{
		file >> problems[i].idProblem >> problems[i].speciality;
	}

	file >> noDoctors;
	vector<Doctor> doctors(noDoctors);

	for (int i = 0; i < noDoctors; i++)
	{
		file >> doctors[i].idDoctor >> doctors[i].speciality;
	}

	for_each(begin(doctors), end(doctors), [&problems](Doctor& doctor)
		{
			auto it = find_if(begin(problems), end(problems), [&doctor](Problem& problem)
				{
					return problem.speciality == doctor.speciality;
				});

			if (it != end(problems))
			{
				cout << doctor.idDoctor << " " << it->idProblem << endl;

				problems.erase(it);
			}
		});

	return 0;
}