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
	ifstream file("input3.txt");

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

		transform(begin(problems[i].idProblem) + 1, end(problems[i].idProblem), begin(problems[i].idProblem) + 1, tolower);
		transform(begin(problems[i].speciality) + 1, end(problems[i].speciality), begin(problems[i].speciality) + 1, tolower);
	}

	file >> noDoctors;
	vector<Doctor> doctors(noDoctors);

	for (int i = 0; i < noDoctors; i++)
	{
		file >> doctors[i].idDoctor >> doctors[i].speciality;

		transform(begin(doctors[i].idDoctor) + 1, end(doctors[i].idDoctor), begin(doctors[i].idDoctor) + 1, tolower);
		transform(begin(doctors[i].speciality) + 1, end(doctors[i].speciality), begin(doctors[i].speciality) + 1, tolower);
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