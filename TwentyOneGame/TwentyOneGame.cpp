#include <iostream>
#include <Windows.h>

using namespace std;
// game 21
void main_menu();
void step_game(int cards_first, int cards_next);
int random_issuance_of_cards();
int check_cards();
int player_turn();
int computer_turn();
bool win(int summa_user, int summa_comp);

int main()
{
	setlocale(LC_ALL, "");
	int first_card = check_cards(), second_card = check_cards();
	main_menu();
	step_game(first_card, second_card);

}

// интерфейс игры. Начало
void main_menu() {
	cout << "Добро пожаловать в игру 21!\n";
	cout << "Хотите начать? (y/n)\n";
	string flag;
	cin >> flag;
}
void step_game(int cards_first, int cards_next) {
	string flag;
	bool f = true;
	int summa_user = cards_first + cards_next, summa_comp = 0;
	cout << "Ваши карты: " << cards_first << ", " << cards_next << endl;
	cout << "Итоговая сумма: " << cards_first + cards_next << endl;
	cout << "Хотите взять еще одну карту?(y/n)\n";
	while (f) {
		cin >> flag;
		if (flag == "y") {
			if (summa_user >= 21) f = win(summa_user, summa_comp);
			else summa_user += player_turn();
		}
		else if (flag == "n") {
			summa_comp += computer_turn();
			f = win(summa_user, summa_comp);
		}
		else
		{
			cout << "Неверный ввод, повторите!";
		}
	}
}
// интерфейс игры. Конец

// рандомная выдача карт. Начало
int random_issuance_of_cards() {
	srand(time(NULL));
	int random_card = rand() % 10 + 2;
	while (random_card == 5) random_card = rand() % 10 + 2;
	return random_card;
}
// учет повторяющихся карт
int check_cards() {
	int arrayRepeatCards[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; // кол-во повторов
	int random_card = random_issuance_of_cards();
	do {
		if (arrayRepeatCards[random_card] > 4)
			random_card = random_issuance_of_cards();
		else {
			arrayRepeatCards[random_card]++;
			return random_card;
		}
	} while (true);
}
//рандомная выдача карт. Конец

//ход игрока
int player_turn() {
	return check_cards();
}
//ход компьютера
int computer_turn() {
	int summa = 0;
	summa += check_cards();
	summa += check_cards();
	srand(time(NULL));
	int a, b, c;
	a = rand() % 2; // 50%
	b = rand() % 5; // 25%
	c = rand() % 10;// 10%
	while (summa <= 21)
	{
		if (summa < 11) summa += check_cards();
		else if (10 < summa < 14) if (b < 4) summa += check_cards();
		else if (13 < summa < 16) if (a) summa += check_cards();
		else if (15 < summa < 18) if (b) summa += check_cards();
		else if (17 < summa < 20) if (c) summa += check_cards();
	}
	return summa;
}
//условия выйгрыша
bool win(int summa_user, int summa_comp) {
	if (summa_user == 21) cout << "Победа игрока\n";
	else if (summa_user > 21) cout << "Победа компьютера\n";
	else if (summa_user > summa_comp) cout << "Победа игрока\n";
	else if (summa_user < summa_comp) cout << "Победа компьютера\n";
	else if (summa_user == summa_comp) cout << "Ничья\n";
	return false;
}