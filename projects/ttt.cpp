#include <iostream>
#include <ctime>

using std::string;

using std::cin;
using std::cout;

namespace ttt {
  void info() {
    /*
     * TTT - A basic Tic Tac Toe game.
     */

    cout << "TTT - A basic Tic Tac Toe game.\n";
  }

  void drawBoard(char* spaces) {
    cout << "\n     |     |     \n";
    cout << "  " << spaces[0] << "  |  " << spaces[1] <<"  |  " << spaces[2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[3] << "  |  " << spaces[4] <<"  |  " << spaces[5] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[6] << "  |  " << spaces[7] <<"  |  " << spaces[8] << "  \n";
    cout << "     |     |     \n\n";
  }

  bool isTaken(char* spaces, int number) {
    return spaces[number] != (number + '1');
  }

  void playerMove(char* spaces, char player) {
    int number;

    do {
      cout << "Enter a spot to place a marker (1-9): ";
      cin >> number;
      number--;

      // Check if the input is out of bounds first
      if (number < 0 || number > 8) {
        cout << "Invalid input! Please enter a number between 1 and 9.\n";

      // Check if the spot is already taken (if it's no longer its original number)
      } else if (isTaken(spaces, number)) {
        cout << "That spot is already taken!\n";

      // Otherwise, valid move
      } else {
        spaces[number] = player;
        break;
      }
    } while (true);
  }

  void computerMove(char* spaces, char computer) {
    int number;

    while (true) {
      number = rand() % 9;
      if (!isTaken(spaces, number)) {
        spaces[number] = computer;
        break;
      }
    }
  }

  bool checkLine(char a, char b, char c, char target) {
    return ((a == target) && (b == target) && (c == target));
  }

  // Returns the winning character
  char checkWinner(char* spaces, char player, char computer) {
    char marks[2] = {player, computer};

    for (char mark : marks) {
      if (
          // Check rows
          checkLine(spaces[0], spaces[1], spaces[2], mark) ||
          checkLine(spaces[3], spaces[4], spaces[5], mark) ||
          checkLine(spaces[6], spaces[7], spaces[8], mark) ||

          // Check columns
          checkLine(spaces[0], spaces[3], spaces[6], mark) ||
          checkLine(spaces[1], spaces[4], spaces[7], mark) ||
          checkLine(spaces[2], spaces[5], spaces[8], mark) ||

          // Check diagonals
          checkLine(spaces[0], spaces[4], spaces[8], mark) ||
          checkLine(spaces[2], spaces[4], spaces[6], mark)) {

        return mark;
      }
    }

    return '\0';
  }

  bool checkTie(char* spaces) {
    for (int i = 0; i < 9; i++) {
      if (!isTaken(spaces, i)) {
        return false; // Found an open spot, not a tie yet
      }
    }
    return true; // All spots are taken, it's a tie
  }
} // namespace ttt

void n();

int main() {
  ttt::info();

  srand(time(0));

  const int SIZE = 9;
  char spaces[SIZE];
  char player = 'P';
  char computer = 'C';
  bool running = true;

  // Fill in the spaces with placeholders 1-9
  // as a guide
  for (int i = 0; i < SIZE; i++) {
    spaces[i] = '1' + i;
  }

  ttt::drawBoard(spaces);

  while (running) {
    ttt::playerMove(spaces, player);

    // Check if the player won on their turn
    char winner = ttt::checkWinner(spaces, player, computer);
    if (winner != '\0') {
      ttt::drawBoard(spaces); // Draw the final board first
      if (winner == player) {
        cout << "You win!\n";
      } else {
        cout << "You lose!\n";
      }
      running = false;
      break;
    } else if (ttt::checkTie(spaces)) {
      cout << "\nIt's a tie!\n";
      running = false;
      break;
    }

    ttt::computerMove(spaces, computer);
    ttt::drawBoard(spaces);

    // Check if the computer won on its turn
    winner = ttt::checkWinner(spaces, player, computer);
    if (winner != '\0') {
      if (winner == player) {
        cout << "You win!\n";
      } else {
        cout << "You lose!\n";
      }
      running = false;
      break;
    } else if (ttt::checkTie(spaces)) {
      cout << "\nIt's a tie!\n";
      running = false;
      break;
    }
  }

  cout << "Thanks for playing!\n";

  return 0;
}

void n() { cout << '\n'; }
