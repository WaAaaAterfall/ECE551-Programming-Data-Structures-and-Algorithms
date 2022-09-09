#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge,          //in months
                double initial,        //initial saving in dollars
                retire_info working,   //info about working
                retire_info retire) {  // info about being retired
  int working_months = working.months;
  double current_balance = initial;
  int current_age = startAge;
  for (int i = 0; i < working_months; i++) {
    printf("Age %3d month %2d you have $%.2f\n",
           current_age / 12,
           current_age % 12,
           current_balance);
    current_age++;
    current_balance += (current_balance * working.rate_of_return);
    current_balance += working.contribution;
  }
  int retire_months = retire.months;
  for (int j = 0; j < retire_months; j++) {
    printf("age %3d month %2d you have $%.2f\n",
           current_age / 12,
           current_age % 12,
           current_balance);
    current_age++;
    current_balance += current_balance * retire.rate_of_return;
    current_balance += retire.contribution;
  }
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retire;
  retire.months = 384;
  retire.contribution = -4000;
  retire.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retire);
  return 0;
}
