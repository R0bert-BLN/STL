#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Problem
{
	int arrivalTime = 0;
	int duration = 0;
	int priority = 0;
	string idProblem;
	string speciality;

	bool operator<(const Problem& otherProblem) const
	{
		if (this->arrivalTime == otherProblem.arrivalTime)
			return this->priority < otherProblem.priority;

		return this->arrivalTime > otherProblem.arrivalTime;
	}
};

struct Doctor
{
	int noSpeciality = 0;
	int program = 9;
	int solvedProblems = 0;
	string idDoctor;
	string problemList;
	unordered_set<string> speciality;
};

void read_doctors(vector<Doctor>& doctors, ifstream& file, const int& noDoctors);
void read_problems(priority_queue<Problem>& problems, ifstream& file, const int& noProblems);
void print_doctors(const vector<Doctor>& doctors);
void assign_doctor(vector<Doctor>& doctors, const Problem& problem);

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
	read_problems(problems, file, noProblems);

	file >> noDoctors;
	vector<Doctor> doctors;
	read_doctors(doctors, file, noDoctors);

	while (!problems.empty())
	{
		assign_doctor(doctors, problems.top());
		problems.pop();
	}

	print_doctors(doctors);

	return 0;
}

void read_doctors(vector<Doctor>& doctors, ifstream& file, const int& noDoctors)
{
	for (int i = 0; i < noDoctors; i++)
	{
		Doctor doctor;
		file >> doctor.idDoctor >> doctor.noSpeciality;

		for (int j = 0; j < doctor.noSpeciality; j++)
		{
			string speciality;
			file >> speciality;
			doctor.speciality.insert(speciality);
		}

		doctors.emplace_back(doctor);
	}
}

void read_problems(priority_queue<Problem>& problems, ifstream& file, const int& noProblems)
{
	for (int i = 0; i < noProblems; i++)
	{
		Problem problem;
		file >> problem.idProblem >> problem.speciality >> problem.arrivalTime >> problem.duration >> problem.priority;
		problems.emplace(problem);
	}
}

void print_doctors(const vector<Doctor>& doctors)
{
	for (const Doctor& doctor : doctors)
	{
		if (doctor.solvedProblems)
		{
			cout << doctor.idDoctor << " " << doctor.solvedProblems << " " << doctor.problemList << endl;
		}
	}
}

void assign_doctor(vector<Doctor>& doctors, const Problem& problem)
{
	auto it = find_if(begin(doctors), end(doctors), [&problem](const Doctor& doctor)
		{
			return (
				doctor.speciality.find(problem.speciality) != end(doctor.speciality) &&
				problem.arrivalTime >= doctor.program &&
				problem.duration <= 17 - doctor.program);
		});

	if (it != end(doctors))
	{
		it->program = problem.duration + problem.arrivalTime;
		it->problemList += problem.idProblem + " " + to_string(problem.arrivalTime) + " ";
		it->solvedProblems++;
	}
}
