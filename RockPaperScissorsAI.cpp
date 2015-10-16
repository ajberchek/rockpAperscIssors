/*
*Author: Avery Berchek
*Date: 1/25/15
*Name: RockPaperScissorsAI.cpp
*Description: THis program is based off the premise that some people
*favor one play in rock paper scissors over the others so the random
*play generator's probablity in selecting rock, paper or scissors is
*altered.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime> 
#include <cstdlib> 

using namespace std;

int RandNum, number_games, wins_computer, wins_user, Rrange, Prange, Srange, choice, pastChoice, userStreak, compStreak;
float Rcount, Pcount, Scount, Rpercent, Ppercent, Spercent, Tcount, PForRandom, PTotal;
bool playAgain = true;
string question;

//Initial message displaying rules of the game and promting for the number of games the user
//wants to play.
void message()
{
	cout << "This is rock paper scissors, please enter number of " << endl;
	cout << "games you want to play(number needs to be odd): ";
	cin >> number_games;
	if ((number_games % 2) == 0)
	{
		number_games++;
	}
	cout << "The game will be best ";
	cout << ((number_games + 1) / 2);
	cout << " out of ";
	cout << number_games << endl;
}

//Method that changes probability of choosing one of the moves based on past move count.
//It returns an integer value pertaining to the move it selects.
int compChoice()
{
	//Calculate probablity then generate a random number
	Tcount = Rcount + Scount + Pcount;
	Rpercent = (((Rcount / Tcount)*(PForRandom)) + (PTotal/3.0))/100.0;
	Spercent = (((Scount / Tcount)*(PForRandom)) + (PTotal/3.0))/100.0;
	Ppercent = (((Pcount / Tcount)*(PForRandom)) + (PTotal/3.0))/100.0;
	Rrange = (int)(10000.0*Rpercent);
	Srange = (int)(10000.0*Spercent);
	Prange = (int)(10000.0*Ppercent);
	RandNum = rand() % 10000 + 1;


	if ((0 <= RandNum) && (RandNum <= Rrange))
	{
		return 1; //For Rock
	}
	
	else if ((Rrange < RandNum) && (RandNum <= (Rrange+Srange)))
	{
		return 2; //For Scissors
	}
	
	else if (((Rrange+Srange) < RandNum) && (RandNum <= (Rrange+Srange+Prange)))
	{
		return 3; //For Paper
	}
	else
	{
		return compChoice();
	}
}

int nonAIComputerChoice()
{
	//This computer is going to mimic a human, stastics show that 
	//people only choose scissors about 30% of time.
	
	Rpercent = 0.35;
	Spercent = 0.3;
	Ppercent = 0.35;
	Rrange = (int)(10000.0*Rpercent);
	Srange = (int)(10000.0*Spercent);
	Prange = (int)(10000.0*Ppercent);
	RandNum = rand() % 10000 + 1;


	if ((0 <= RandNum) && (RandNum <= Rrange))
	{
		return 1; //For Rock
	}

	else if ((Rrange < RandNum) && (RandNum <= (Rrange + Srange)))
	{
		return 2; //For Scissors
	}

	else if (((Rrange + Srange) < RandNum) && (RandNum <= (Rrange + Srange + Prange)))
	{
		return 3; //For Paper
	}
	else
	{
		return compChoice();
	}
}

int UserImput()
{
	cout << "Choose 1 for Rock, 2 for Scissors, or 3 for Paper: ";
	cin >> choice;
	cout << "" << endl;
	if ((choice > 0) || (choice <= 3))
	{
		return choice;
	}
	else
	{
		cout << "Imput not recognized, try again" << endl;
		return UserImput();
	}
}

void Comparison(int user, int computer)
{
	/*
	1 = Rock
	2 = Scissors
	3 = Paper
	*/

	if (user == 1)
	{
		Pcount++;
	}
	else if (user == 2)
	{
		Rcount++;
	}
	else if (user == 3)
	{
		Scount++;
	}

	if (user == computer)
	{
		cout << "draw" << endl;
	}
	else if ((user == 1) && (computer == 3))
	{
		cout << "You imput Rock, the computer imput Paper therefore computer wins" << endl;
		wins_computer++;
	}
	else if ((user == 1) && (computer == 2))
	{
		cout << "You imput Rock, the computer imput Scissors therefore you win" << endl;
		wins_user++;
	}
	else if ((user == 2) && (computer == 1))
	{
		cout << "You imput Scissors, the computer imput rock therefore the computer wins" << endl;
		wins_computer++;
	}
	else if ((user == 2) && (computer == 3))
	{
		cout << "You imput Scissors, the computer imput Paper therefore you win" << endl;
		wins_user++;
	}
	else if ((user == 3) && (computer == 1))
	{
		cout << "You imput Paper, the computer imput Rock therefore you win" << endl;
		wins_user++;
	}
	else if ((user == 3) && (computer == 2))
	{
		cout << "You imput Paper, the computer imput Scissors therefore the computer wins" << endl;
		wins_computer++;
	}
	/*
	1 = computer win
	2 = draw
	3 = user win
	*/

}

void result()
{
	cout << "" << endl;
	cout << "The computer won: ";
	cout << wins_computer;
	cout << " and you won: ";
	cout << wins_user;
	cout << " out of ";
	cout << number_games;
	cout << " games, therefore: ";

	if (wins_computer > wins_user)
	{
		cout << "The Computer Wins!" << endl;
	}

	else
	{
		cout << "You Win!" << endl;
	}

	cout << "" << endl;
	cout << "Number of rocks user imput: ";
	cout << (Rcount - 1) << endl;
	cout << "Number of papers user imput: ";
	cout << (Pcount - 1) << endl;
	cout << "Number of scissors user imput: ";
	cout << (Scount - 1) << endl;
	cout << "" << endl;

}

void replay()
{
	cout << "Would You Like To Play Again? (1 for Y / 2 for N): ";
	cin >> choice;
	cout << "" << endl;
	choice = (int)choice;
	if (choice == 1)
	{
		playAgain = true;
	}
	else
	{
		playAgain = false;
	}

}

int main()
{

	while (playAgain)
	{
		srand(time(NULL));
		wins_computer = 0;
		wins_user = 0;
		Rcount = 1;
		Pcount = 1;
		Scount = 1;
		PForRandom = 70;
		PTotal = 100 - PForRandom;
		message();


		while (((((number_games)+1) / 2) > wins_computer) && ((((number_games)+1) / 2) > wins_user))
		{
			Comparison(UserImput(), compChoice());
		}

		result();
		replay();
	}
}