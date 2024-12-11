#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define NAME_LENGTH 100

typedef struct {
    int accountnumber;
    char accountholder[NAME_LENGTH];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountcount = 0;

void clearInputBuffer() {
    while (getchar() != '\n');
}

void createAccount() {
    if (accountcount >= MAX_ACCOUNTS) {
        printf("The account limit has been reached.\n");
        return;
    }

    Account newAccount;
    newAccount.accountnumber = accountcount + 1;

    printf("Enter the account holder name: ");
    getchar(); // Clear leftover newline from previous input
    fgets(newAccount.accountholder, NAME_LENGTH, stdin);
    newAccount.accountholder[strcspn(newAccount.accountholder, "\n")] = 0; // Remove trailing newline

    newAccount.balance = 0.0;
    accounts[accountcount] = newAccount;
    accountcount++;

    printf("Account created successfully! Your account number is %d.\n", newAccount.accountnumber);
}

void deposit() {
    int accountnumber;
    float amount;

    printf("Enter the account number: ");
    if (scanf("%d", &accountnumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (accountnumber <= 0 || accountnumber > accountcount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Enter the amount to be deposited: ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (amount <= 0) {
        printf("Invalid amount. Cannot be deposited.\n");
        return;
    }

    accounts[accountnumber - 1].balance += amount;
    printf("Amount deposited successfully! New balance: %.2f\n", accounts[accountnumber - 1].balance);
}

void withdraw() {
    int accountnumber;
    float amount;

    printf("Enter the account number: ");
    if (scanf("%d", &accountnumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (accountnumber <= 0 || accountnumber > accountcount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Enter the amount to be withdrawn: ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (amount <= 0) {
        printf("Invalid amount. Cannot be withdrawn.\n");
        return;
    }

    if (accounts[accountnumber - 1].balance < amount) {
        printf("Insufficient funds.\n");
        return;
    }

    accounts[accountnumber - 1].balance -= amount;
    printf("Amount withdrawn successfully! New balance: %.2f\n", accounts[accountnumber - 1].balance);
}

void transfer() {
    int fromAccountNumber, toAccountNumber;
    float amount;

    printf("Enter the source account number: ");
    if (scanf("%d", &fromAccountNumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter the destination account number: ");
    if (scanf("%d", &toAccountNumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (fromAccountNumber <= 0 || fromAccountNumber > accountcount ||
        toAccountNumber <= 0 || toAccountNumber > accountcount ||
        fromAccountNumber == toAccountNumber) {
        printf("Invalid account number(s).\n");
        return;
    }

    printf("Enter the amount to be transferred: ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (amount <= 0 || amount > accounts[fromAccountNumber - 1].balance) {
        printf("Invalid transfer amount.\n");
        return;
    }

    accounts[fromAccountNumber - 1].balance -= amount;
    accounts[toAccountNumber - 1].balance += amount;
    printf("Amount transferred successfully! New balance of source account: %.2f, destination account: %.2f\n",
           accounts[fromAccountNumber - 1].balance, accounts[toAccountNumber - 1].balance);
}

void checkBalance() {
    int accountnumber;

    printf("Enter the account number: ");
    if (scanf("%d", &accountnumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (accountnumber <= 0 || accountnumber > accountcount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Current balance: %.2f\n", accounts[accountnumber - 1].balance);
}

void menu() {
    int choice;

    do {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                transfer();
                break;
            case 5:
                checkBalance();
                break;
            case 6:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
