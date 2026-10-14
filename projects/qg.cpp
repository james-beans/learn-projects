#include <iostream>

using std::string;

using std::cin;
using std::cout;

namespace qg {
  void info() {
    /*
     * QG - A Quiz Game.
     */

    cout << "QG - A Quiz Game.\n";
  }
} // namespace qg

void n();

int main() {
  qg::info();

  string questions[] = {"1. What year was C++ created?: ", "2. Who invented C++?: ",
                        "3. What is the predecessor of C++?: ", "4. Is the Earth flat?: "};

  string options[][4] = {
    {"A. 1969", "B. 1975", "C. 1985", "D. 1989"},
    {"A. Guido van Rossum", "B. Bjarne Stroustrup", "C. John Carmack", "D. Dennis Ritche"},
    {"A. C", "B. C+", "C. C--", "D. B++"},
    {"A. Yes", "B. No", "C. Sometimes", "D. What's Earth?"}};

  char answerKey[] = {'C', 'B', 'A', 'B'};

  int size = sizeof(questions) / sizeof(questions[0]);
  char guess;
  int score;

  for (int i = 0; i < size; i++) {
    n();
    cout << questions[i] << "\n";
    n();

    for (int j = 0; j < sizeof(options[i]) / sizeof(options[i][0]); j++) {
      cout << options[i][j] << "\n";
    }
    n();

    cin >> guess;
    n();
    guess = toupper(guess);

    if (guess == answerKey[i]) {
      cout << "CORRECT\n";
      score++;
    } else {
      cout << "WRONG\n";
      cout << "Answer: " << answerKey[i] << "\n";
    }
  }

  n();

  cout << "RESULTS:\n";
  cout << "CORRECT GUESSES: " << score << "\n";
  cout << "# of QUESTIONS: " << size << "\n";
  cout << "SCORE: " << (score / (double)size) * 100 << "%\n";

  return 0;
}

void n() { cout << '\n'; }
