#include <atomic>
#include <functional>
#include <iostream>
#include <thread>

struct Account{
  std::atomic<int> balance{100};
};

void transferMoney(int amount, Account& from, Account& to){
  using namespace std::chrono_literals;
  if (from.balance >= amount){
    from.balance -= amount;  
    std::this_thread::sleep_for(1ns);
    to.balance += amount;
  }
}

int main(){
  
  std::cout << std::endl;

  Account account1;
  Account account2;
  
  std::thread thr1(transferMoney, 50, std::ref(account1), std::ref(account2));
  std::thread thr2(transferMoney, 130, std::ref(account2), std::ref(account1));
  
  thr1.join();
  thr2.join();

  std::cout << "account1.balance: " << account1.balance << std::endl;
  std::cout << "account2.balance: " << account2.balance << std::endl;
  
  std::cout << std::endl;

}

/*

And you see. Only the first function transferMoney was executed.
The second one was not performed because the balance was too small.
The reason is that the second withdrawal happened before
the first transfer of money was completed. 
Here we have our race condition.

Solving the data race is quite easy. 
The operations on the balance have to be protected 
with an atomic variable.

Of course, the atomic variable will not solve the race condition.
Only the data race is gone.

*/

// exemplo disponibilizado em
// https://www.modernescpp.com/index.php/race-condition-versus-data-race
