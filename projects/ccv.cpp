#include <iostream>

using std::string;

using std::cin;
using std::cout;

namespace ccv {
  void info() {
    /*
     * CCV - A credit card validator.
     * Credits to: https://www.paypalobjects.com/en_GB/vhelp/paypalmanager_help/credit_card_numbers.htm
     */

    cout << "CCV - A credit card validator.\n";
    cout << "Credits to: https://www.paypalobjects.com/en_GB/vhelp/paypalmanager_help/credit_card_numbers.htm\n\n";
  }

  int getDigit(const int number) {
    return number % 10 + (number / 10 % 10);
  }

  int sumOddDigits(const string cardNumber) {
    int sum = 0;

    for (int i = cardNumber.size() - 1; i >= 0; i -= 2) {
      sum += cardNumber[i] - '0';
    }

    return sum;
  }

  int sumEvenDigits(const string cardNumber) {
    int sum = 0;

    for (int i = cardNumber.size() - 2; i >= 0; i -= 2) {
      sum += getDigit((cardNumber[i] - '0') * 2);
    }

    return sum;
  }
} // namespace ccv

void n();

int main() {
  ccv::info();

  string cardNumber;
  int result = 0;

  cout << "Enter a credit card #: ";
  cin >> cardNumber;

  result = ccv::sumEvenDigits(cardNumber) + ccv::sumOddDigits(cardNumber);

  if (result % 10 == 0) {
    cout << cardNumber << " is valid\n";
  } else {
    cout << cardNumber << " is not valid\n";
  }

  return 0;
}

void n() { cout << '\n'; }
