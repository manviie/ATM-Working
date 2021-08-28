//

// Copyright © 2020 Manvi Jain. All rights reserved.
//
#include <stdio.h>
struct account
{
  int account_no;
  char name[80];
  int balance;
  int pin;
};

struct transaction{
  char type[80];
  int amount;
};

int acc_count = 0;
int trans_count = 0;
struct account data[100];
struct transaction record[100];
int atm_current_balance = 0;
int atm_max_balance = 2600000;

int max_notes = 1000;
int stack2000[1000]= {0};
int top2000 = -1;
int stack500[1000]= {0};
int top500 = -1;
int stack100[1000]= {0};
int top100 = -1;

void login_type(void );
void check_old_acc(void );
void login_old_acc(void );
void check_pin(void );
void create_new_acc(void );
void deposit(int );
void withdraw(int );
int search(int );
void count_notes(int , char []);
void push(int [], int []);
void pop(int [], int []);
void display_current(int );
void display_history(int );
void trans_history(char [], int );
void quit(void );

int main()
{
  int choice, account_no;
  login_type();
  do
  {
    printf("**************************************\n");
    printf("WELCOME TO AUTOMATED TELLER MACHINE :\n");
    printf("**************************************\n");
    printf("Press 1 to deposit amount.\n");
    printf("Press 2 to withdraw amount.\n");
    printf("Press 3 to display current balance.\n");
    printf("Press 4 to display transaction history.\n");
    printf("Press 5 to go back. \n");
    printf("Press 0 to exit\n");
    printf("\nEnter choice(0-5) : ");
    scanf("%d", &choice);
  switch (choice)
  {
    case 1:
      printf("Enter account number : ");
      scanf("%d", &account_no);
      deposit(account_no);
      break;
    case 2:
      printf("Enter account number : ");
      scanf("%d", &account_no);
      withdraw(account_no);
      break;
    case 3:
      printf("Enter account number: ");
      scanf("%d", &account_no);
      display_current(account_no);
      break;
    case 4:
      printf("Enter account number: ");
      scanf("%d", &account_no);
      display_history(account_no);
      break;
    case 5:
      login_type();
  }
  }
  while (choice != 0);
    return 0;
  }
  void login_type(){
    int opt;
    printf("\n**************************************\n");
    printf("WELCOME TO AUTOMATED TELLER MACHINE :\n");
    printf("**************************************\n");
    printf("Press 1 to create a new account. \n");
    printf("Press 2 to login to existing account. \n");
    return 0;
}
void login_type(){
  int opt;
  printf("Enter option: ");
  scanf("%d", &opt);
  if (opt == 1)
    create_new_acc();
  else
    check_old_acc();
}
void create_new_acc()
{
  printf("\nEnter account_no: ");
  scanf("%d", &data[acc_count].account_no);
  printf("Enter first name: ");
  scanf("%s", data[acc_count].name);
  printf("Enter PIN: ");
  scanf("%d", &data[acc_count].pin);
  data[acc_count].balance = 0;
  acc_count++;
}
void check_old_acc(){
  if (acc_count == 0){
    printf("\nNo accounts stored in ATM.\n");
    login_type();
  }
  else
    login_old_acc();
}
void login_old_acc(){
  int search_acc, i, check_pin = 0, pin_val = 0;
  printf("Enter account number: ");
  scanf("%d", &search_acc);
  for (i = 0; i < acc_count; i++)
    if (data[i].account_no == search_acc){
    check_pin = data[i].pin;
    printf("Enter PIN: ");
    scanf("%d", &pin_val);
  }
  if(check_pin != pin_val){
  printf("Wrong PIN.");
  login_type();
  }
}
int search(int search_acc){
  int i;
  for (i = 0; i < acc_count; i++){
    if (data[i].account_no == search_acc){
      return i;
  }
  }
  return - 1;
}
void deposit(int acc_no){
  int index, amount=0;
  index = search(acc_no);
  if (index == - 1)
  {
    printf("Record not found : ");
  }
  else
  {
    printf("Enter amount to deposit : ");
    scanf("%d", &amount);
    if (amount % 100 != 0)
      printf("Enter amount in multiples of 100.");
    else{
      if(amount < (atm_max_balance - atm_current_balance)){
      count_notes(amount, "deposit");
      data[index].balance += amount;
      trans_history("Credited", amount);
      atm_current_balance += amount;
      printf("%d", amount);
      printf(" credited.\n");
  }
  else
    printf("Max balance of ATM reached.");
    }
  }
}
void withdraw(int acc_no)
{
  int index, amount=0;
  index = search(acc_no);
  if (index == - 1)
  {
    printf("Record not found : ");
  }
  else
  {
    printf("Enter amount to withdraw : ");
    scanf("%d", &amount);
    if (amount % 100 != 0)
      printf("Enter amount in multiples of 100.");
  else{
    if(amount < atm_current_balance){
    count_notes(amount, "withdraw");
    data[index].balance -= amount;
    trans_history("Debited", amount);
    atm_current_balance -= amount;
    printf("%d", amount);
    printf(" debited.\n");
  }
  else
    printf("0 balance in ATM.\n");
  }
  }
  }
  void count_notes(int amt, char type[20]) // count notes using Greedy approach
  {
    int notes[3] = { 2000, 500, 100};
    int note_counter[3] = { 0 };
    for (int i = 0; i < 3; i++) {
      if (amt >= notes[i]) {
        note_counter[i] = amt / notes[i];
        amt = amt - note_counter[i] * notes[i];
    }
  }
    if(strcmp(type, "deposit") == 0)
      push(notes, note_counter);
    else if(strcmp(type, "withdrawl") == 0)
      pop(notes, note_counter);
}
void push(int notes[3], int note_counter[3]){
  int i = 0;
  int space1 = max_notes - top2000;
  int space2 = max_notes - top500;
  if(note_counter[1] > space1){
    note_counter[2] += 4*(note_counter[1]-space1);
    note_counter[1] = max_notes - top2000;
    for(i=0; i<note_counter[1]; i++){
      stack2000[i] = 1;
      top2000 ++;
    }
  }
  else if(top2000 == max_notes){
    note_counter[2] += 4*note_counter[1];
  }
  else
    for(i=top2000; i < note_counter[1]-1; i++){
    stack2000[i] = 1;
    top2000 ++;
    }
  if(note_counter[2] > space2){
    note_counter[3] += 5*(note_counter[2]-space1);
    note_counter[2] = max_notes - top500;
    for(i=0; i<note_counter[1]; i++){
      stack2000[i] = 1;
      top2000 ++;
    }
  }
  else if(top500 == max_notes){
    note_counter[3] += 4*note_counter[2];
  }
  else
    for(i=top500; i < note_counter[2]-1; i++){
      stack500[i] = 1;
      top500 ++;
  }
  for(i=top100; i < note_counter[3]-1; i++){
  stack100[i] = 1;
  top100 ++;
  }
  printf("Currency Count ->");
    for (i = 0; i < 3; i++) {
    if (note_counter[i] != 0) {
      printf("%d", notes[i]);
      printf(": ");
      printf("%d", note_counter[i]);
      printf("\n");
    }
  }
}
void pop(int notes[3], int note_counter[3]){
int i = 0;
  if(note_counter[1] > top2000){
  note_counter[2] += 4*(note_counter[1]-top2000);
  for(i=top2000-1; i>=0; i--){
    stack2000[i] = 0;
    top2000 --;
}
}
else if(top2000 == -1){
  note_counter[2] += 4*note_counter[1];
}
else
  for(i=top2000-1; i>=0; i--){
  stack2000[i] = 0;
  top2000 --;
}
if(note_counter[2] > top500){
  note_counter[3] += 4*(note_counter[1]-top500);
  for(i=top500-1; i>=0; i--){
    stack500[i] = 0;
    top500--;
  }
}
else if(top2000 == -1){
  note_counter[3] += 4*note_counter[2];
}
else
  for(i=top2000-1; i>=0; i--){
    stack2000[i] = 0;
    top2000 --;
}
printf("Currency Count ->");
for (i = 0; i < 3; i++) {
  if (note_counter[i] != 0) {
    printf("%d", notes[i]);
    printf(": ");
    printf("%d", note_counter[i]);
  }
}
}
void display_current(int acc_no)
{
int index;
index = search(acc_no);
if (index == - 1)
{
  printf("Record not found : ");
}
else
{
  printf("\n\nA/c No\tName\tBalance\n");
  printf("%d\t%s\t%d\n", data[index].account_no, data[index].name, data[index].balance);
  }
}
void trans_history(char type[20], int amt){
record[trans_count].amount = amt;
strcpy(record[trans_count].type, type);
trans_count++;
}
void display_history(int acc_no){
int i, index;
index = search(acc_no);
if (index == - 1)
{
  printf("Record not found : ");
}
else
{
  printf("\n\nA/c No\tName\tAmount\tType\n");
  for(i = 0; i < trans_count; i++)
    printf("%d\t%s\t%d\t%s\n", data[index].account_no,data[index].name, record[i].amount, record[i].type);
}
}
void quit(){
  printf("Goodbye!");
}
