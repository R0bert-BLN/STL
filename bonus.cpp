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
	int time;
};

struct Doctor
{
	string idDoctor;
	string speciality;
};

int main()
{
	ifstream file("input4_bonus.txt");

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
		file >> problems[i].idProblem >> problems[i].speciality >> problems[i].time;
	}

	file >> noDoctors;
	vector<Doctor> doctors(noDoctors);

	for (int i = 0; i < noDoctors; i++)
	{
		file >> doctors[i].idDoctor >> doctors[i].speciality;
	}

	for_each(begin(doctors), end(doctors), [&problems](Doctor& doctor)
		{
			int hours = 8;
			int count = 0;
			string solvedProblems = "";

			while (hours > 0)
			{
				auto it = find_if(begin(problems), end(problems), [&doctor, &hours](Problem& problem)
					{
						return problem.speciality == doctor.speciality && problem.time <= hours;
					});

				if (it != end(problems))
				{
					count++;
					solvedProblems += it->idProblem + " ";
					hours -= it->time;

					problems.erase(it);
				}
				else
				{
					break;
				}
			}

			if (count > 0)
			{
				cout << doctor.idDoctor << " " << count << " " << solvedProblems << endl;
			}
		});

	return 0;
}