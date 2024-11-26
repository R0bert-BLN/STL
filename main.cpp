#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Problem
{
	string idProblem;
	string speciality;
	int time;
	int priority;

	bool operator<(const Problem& otherProblem) const
	{
		return priority < otherProblem.priority;
	}
};

struct Doctor
{
	string idDoctor;
	string speciality;
	string problemsList = "";
	int time = 8;
	int solvedProblems = 0;
};

int main()
{
	ifstream file("input2.txt");

	if (!file.is_open())
	{
		cerr << "Error opening file" << endl;
		return 1;
	}

	int noProblems;
	int noDoctors;

	file >> noProblems;
	priority_queue<Problem> problems;

	for (int i = 0; i < noProblems; i++)
	{
		Problem problem;
		file >> problem.idProblem >> problem.speciality >> problem.time >> problem.priority;
		problems.push(problem);
	}

	file >> noDoctors;
	vector<Doctor> doctors(noDoctors);

	for (int i = 0; i < noDoctors; i++)
	{
		file >> doctors[i].idDoctor >> doctors[i].speciality;
	}

	while (!problems.empty())
	{
		Problem problem = problems.top();
		problems.pop();

		auto it = find_if(begin(doctors), end(doctors), [&problem](Doctor& doctor)
			{
				return (problem.speciality == doctor.speciality && problem.time <= doctor.time);
			});

		if (it != end(doctors))
		{
			it->problemsList += problem.idProblem + " ";
			it->solvedProblems++;
			it->time -= problem.time;
		}
	}

	for (const Doctor& doctor : doctors)
	{
		if (doctor.solvedProblems != 0)
		{
			cout << doctor.idDoctor << " " << doctor.solvedProblems << " " << doctor.problemsList << endl;
		}
	}

	return 0;
}