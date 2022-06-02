#include <functional>
#include <iostream>
#include <thread>

struct Account{
  int balance{100};
};
                                                      // 2
void transferMoney(int amount, Account& from, Account& to){
  using namespace std::chrono_literals;
  if (from.balance >= amount){
    from.balance -= amount;  
    std::this_thread::sleep_for(1ns);                 // 3
    to.balance += amount;
  }
}

int main(){
  
  std::cout << std::endl;

  Account account1;
  Account account2;
                                                        // 1
  std::thread thr1(transferMoney, 50, std::ref(account1), std::ref(account2));
  std::thread thr2(transferMoney, 130, std::ref(account2), std::ref(account1));
  
  thr1.join();
  thr2.join();

  std::cout << "account1.balance: " << account1.balance << std::endl;
  std::cout << "account2.balance: " << account2.balance << std::endl;
  
  std::cout << std::endl;

}
/*

The calls of transferMoney will be executed concurrently (1). 
The arguments to a function, executed by a thread,
have to be moved or copied by value.
If a reference such as account1 or account2
needs to be passed to the thread function,
you have to wrap it in a reference wrapper
like std::ref. 
Because of the threads t1 and t2,
there is a data race on the balance of
the account in the function transferMoney (2). 
But where is the race condition? 
To make the race condition visible, 
I put the threads for a short period of time to sleep (3). 
The built-in literal 1ns in the expression 
std::this_thread::sleep_for(1ns) stands for a nanosecond.
In the post, Raw and Cooked are the details of
the new built-in literals. 
We have had them for time durations since C++14.

*/

// exemplo disponibilizado em 
// https://www.modernescpp.com/index.php/race-condition-versus-data-race
