#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount{
    private:
        string accountNumber;
        string accountHolderName;
        double balance;
    public:
        BankAccount(string accNum, string accName, double initBalance){
            accountNumber=accNum;
            accountHolderName=accName;
            balance=initBalance;
        }
        BankAccount(){
            accountNumber="";
            accountHolderName="";
            balance=0.0;
        }
        void deposit(double amount){
            if(amount>0){
                balance+=amount;
                cout<<"Deposited: Rs."<<amount<<"| New Balance is: Rs."<<balance<<endl;
            }else{
                cout<<"Deposit amount must be positive!"<<endl;
            }
        }
        void withdraw(double amount){
            if(amount>0 && amount<=balance){
                balance-=amount;
                cout<<"Withdrawn: Rs."<<amount<<"| New Balance is: Rs."<<balance<<endl;
            }else{
                cout<<"Insufficient funds or invalid amount!"<<endl;
            }
        }
        void checkBalance() const{
            cout<< "Account Balance: Rs."<<balance<<endl;
        }
        void saveToFile() const{
            ofstream file(accountNumber + ".txt");
            if(file.is_open()){
                file<<accountNumber<<endl;
                file<<accountHolderName<<endl;
                file<<balance<<endl;
                file.close();
                cout<<"Account details saved to "<< accountNumber <<".txt"<<endl;
            }else{
                cout<<"Unable to open file!"<<endl;
            }
        }
        static BankAccount loadFromFile(string accNum){
            ifstream file(accNum+ ".txt");
            string accName;
            double bal;
            if(file.is_open()){
                getline(file,accNum);
                getline(file,accName);
                file>>bal;
                file.close();
                
                return BankAccount(accNum,accName,bal);
            }else{
                cout<<"No existing account found with that number. You need to create a new account."<<endl;
                return BankAccount();
            }
        }
        bool isValid() const{
            return !accountNumber.empty();
        }
};
int main() {
    cout << "\n";
    cout << "=========================================\n";
    cout << "      BANK MANAGEMENT SYSTEM\n";
    cout << "=========================================\n";
    cout << "   Welcome to Secure Banking Services\n";
    cout << "=========================================\n\n";
    string accNum;
    cout << "Enter Account Number: ";
    cin>>accNum;

    BankAccount account=BankAccount::loadFromFile(accNum);

    if(!account.isValid()){
        string accName;
        double initialBalance;
        cout << "\nCreating a new account...\n";
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin,accName);
        cout << "Enter Initial Balance: Rs.";
        cin >> initialBalance;
        account=BankAccount(accNum,accName,initialBalance);
    }
    int choice;
    do{
       cout << "\n=========================================\n";
       cout << "              MAIN MENU\n";
       cout << "=========================================\n";
       cout << "1. Deposit Amount\n";
       cout << "2. Withdraw Amount\n";
       cout << "3. Check Balance\n";
       cout << "4. Save Account\n";
       cout << "5. Exit\n";
       cout << "=========================================\n";
       cout << "Choose an option: ";
       cin >> choice;
        
        switch(choice){
            case 1:{
                double amount;
                cout << "Enter amount to deposit: Rs.";
                cin >> amount;
                account.deposit(amount);
                break;
            }
            case 2:{
                double cash;
                cout << "Enter amount to withdraw: Rs.";
                cin >> cash;
                account.withdraw(cash);
                break;
            }
            case 3:{
                account.checkBalance();
                break;
            }
            case 4:{
                account.saveToFile();
                break;
            }
            case 5:{
                account.saveToFile();
                cout << "\n============================================\n";
                cout << " Thank You for Using Bank Management System\n";
                cout << "============================================\n";
                cout << "Have a Nice Day!\n";
                break;
            }        
            default:
                cout << "Invalid option! Try again."<<endl;                 
        }
    }while(choice!=5);
    return 0;
}