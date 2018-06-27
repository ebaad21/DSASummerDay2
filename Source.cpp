#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

//Global variables
int maxAgeBunny = 5;
int adultAge = 2;
int maxPopulation = 20;


class Bunny{
	//specified attributes
public:
	string gender;
	string name;
	string color;
	int age;

	Bunny *next;
	bool alive;

	//Constructor

	Bunny()
	{
		gender = genders();
		name = names(gender);
		color = colors();
		age = 0;
		alive = true;
		next = NULL;
	}

	string genders()
	{
		int randomNumber = rand() % 2 + 1;
		string gender = "";

		if (randomNumber == 1)
		{
			gender = "female";
		}
		else
		{
			gender = "male";
		}
		return gender;
	}

	string names(string gender)
	{
		int randomNumber = rand() % 4 + 1;
		string name = "";

		if (gender == "male")
		{
			switch (randomNumber)
			{
			case 1: name = "Roger";
				break;

			case 2: name = "Peter";
				break;

			case 3: name = "Dumper";
				break;

			case 4: name = "Ken";
				break;

			};
		}
		else if (gender == "female")
		{
			switch (randomNumber)
			{
			case 1: name = "Elsa";
				break;

			case 2: name = "Anna";
				break;

			case 3: name = "Cammy";
				break;

			case 4: name = "Sakura";
				break;
			};
		}
		return name;
	}

	string colors()
	{
		int randomNumber = rand() % 4 + 1;
		string color = "";
		switch (randomNumber)
		{
		case 1: color = "white";
			break;

		case 2: color = "brown";
			break;

		case 3: color = "black";
			break;

		case 4: color = "spotted";
			break;
		};

		return color;
	}




};

void announcements(Bunny *bunny, char announcementType = 'd')
{
	fstream outfile("BunnyData1.txt", ios::in | ios::out | ios::app);
	
	if (!outfile.is_open())
	{
		cout << "error writing to file" << endl;
	}
	else
	{

		if (announcementType == 'b')
		{
			cout << "New bunny " << bunny->name << " was born!" << endl;
			outfile << "New bunny " << bunny->name << " was born!" << endl;
		}
		else if (bunny->alive)
		{
			cout << "Bunny " << bunny->name << " has passed away!" << endl;
			outfile << "Bunny " << bunny->name << " has passed away!" << endl;
		}

	}
	outfile.close();

}



void incrementAllBunniesAge(Bunny *first) {
	while (first != NULL)
	{
		first->age = first->age + 1;
		first = first->next;
	}
}

void addBunny(Bunny *bunny)
{
	int maleCount = 0;
	int totalPopulation = 0;
	Bunny *first = bunny;
	Bunny *mother;


	while (bunny != NULL)
	{
		totalPopulation++;
		if (bunny->gender == "male" && bunny->age >= adultAge && bunny->alive)
			maleCount++;
		bunny = bunny->next;
	}

	while (first != NULL)
	{
		Bunny *temp = new Bunny();
		if (maleCount > 0 && first->gender == "female" && first->age >= adultAge  && first->alive)
		{
			mother = first;
			temp->color = mother->color;
			temp->next = mother->next;
			mother->next = temp;
			first = temp->next;
			announcements(temp, 'b');
		}
		else
		{
			first = first->next;
		}
	}
}



void printAllBunnies(Bunny *first) {
	int i = 1;
	fstream outfile("BunnyData.txt", ios::in | ios::out | ios::app);

	if (!outfile.is_open())
	{
		cout << "Error writing to file" << endl;
	}
	else
	{
		while (first != NULL)
		{
			if (first->alive)
			{
				cout << "[" << i++ << "] " << first->name << '\t' << first->gender << '\t' << "Age: " << first->age << '\t' << first->color << endl;
				outfile << "[" << i << "] " << first->name << '\t' << first->gender << '\t' << "Age: " << first->age << '\t' << first->color << endl;
			}
			first = first->next;
		}
	}
	outfile.close();
}

void killBunnies(Bunny *first)
{
	bool alive = true;

	while (first != NULL)
	{
		if (first->age > maxAgeBunny)
		{
			announcements(first);
			first->alive = false;

		}
		first = first->next;
	}

}


bool terminates(Bunny *first)
{
	bool terminate = false;
	int countDead = 0;
	int totalPopulation = 0;

	while (first != NULL)
	{
		totalPopulation++;

		if (!first->alive)
		{
			countDead++;
		}

		first = first->next;
	}

	//if (countDead == totalPopulation)
	if (totalPopulation==20)
	{
		terminate = true;
	}

	return terminate;
};




int main()
{
	
	srand(time(0));
	Bunny *b1 = new Bunny();
	Bunny *b2 = new Bunny();
	b1->next = b2;
	Bunny *b3 = new Bunny();
	b2->next = b3;
	Bunny *b4 = new Bunny();
	b3->next = b4;
	Bunny *b5 = new Bunny();
	b4->next = b5;

	fstream outfile("BunnyData1.txt", ios::in | ios::out | ios::app);

	if (!outfile.is_open())
	{
		cout << "Error writing to file" << endl;
	}
	else
	{

		while (!terminates(b1))
		{
			killBunnies(b1);
			addBunny(b1);
			printAllBunnies(b1);
			cout << "==================================================" << endl;
			incrementAllBunniesAge(b1);
			cin.get();
		}
	}

	outfile << "Program has ended!" << endl << endl << endl;

	cin.get();
	
	outfile.close();
}