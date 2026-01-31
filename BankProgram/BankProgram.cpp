#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

const string fileName = "ClientsData.txt";
const string UsersfileName = "UsersData.txt";

// structure contain clients data
struct stClientData
{
    string accountNumber;
    string pinCode;
    string clientName;
    string phone;
    double accountBalance;
};

// structure contain users data
struct stUserData
{
    string userName;
    int password;
    short permission;
};

// enum contain main menu choices
enum enMainMenuChoices {
    ShowClientslist = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Trancaction = 6, ManageUsers = 7, Logout = 8
};

// enum contain main menu choices
enum enManageUsersMenuChoices {
    UsersList = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, menu = 6
};

// enum contain transaction menu choices
enum enTransactionMenuChoices {
    Deposit = 1, Withdraw = 2, TotalBalances = 3, Menu = 4
};

// enum contain permission choices
enum enPermissionChoices {
    ShowClientslistPermission = 1, AddNewClientPermission = 2, DeleteClientPermission = 4, UpdateClientInfoPermission = 8, FindClientPermission = 16, TrancactionPermission = 32, ManageUsersPermission = 64,
};

void mainMenu();
stUserData loginCheck(vector <stUserData>& usersData);
void loginScreen();
void manageUsersMenu();
void showSelectedChoiceInManageUsersMenu(vector <stUserData>& usersData);
void showTransactionSelectedChoice(vector <stClientData>& clientsData, vector <stUserData> usersData, stUserData user);
vector <stUserData> getUsersData(string delim = "/##/");
void usersList(vector <stUserData>& usersData);

// function to insert the account number you want to find it
string enterString(string enteredString)
{
    string word;
    cout << enteredString;
    getline(cin >> ws, word);
    return word;
}

// function to split client data in string to structure
stClientData splitDataFileToRecord(string fileDataString, string delim = "/##/")
{
    stClientData clientDataRecord;
    vector <string> clientData;
    int pos = 0;
    string word = "";

    while ((pos = fileDataString.find(delim)) != std::string::npos)
    {
        word = fileDataString.substr(0, pos);
        clientData.push_back(word);
        fileDataString.erase(0, pos + delim.length());
    }

    if (fileDataString != "")
    {
        clientData.push_back(fileDataString);
    }

    clientDataRecord.accountNumber = clientData[0];
    clientDataRecord.pinCode = clientData[1];
    clientDataRecord.clientName = clientData[2];
    clientDataRecord.phone = clientData[3];
    clientDataRecord.accountBalance = stod(clientData[4]);

    return clientDataRecord;
}

// function to find client you looking for by account number in file
stClientData findClientByAccountNumber(vector <stClientData>& clientsData, string accountNumber)
{
    stClientData clientData;

    for (int i = 0; i < clientsData.size(); i++)
    {
        if (clientsData[i].accountNumber == accountNumber)
        {
            clientData = clientsData[i];

            return clientData;
        }
    }
    return {};
}

// function to fill vector with clients data that exist in file
vector <stClientData> getClientsData(string delim = "/##/")
{
    vector <stClientData> clientsData;
    string clientDataString = "";
    fstream dataFile;

    dataFile.open(fileName, ios::in);


    if (dataFile.is_open())
    {
        while (getline(dataFile, clientDataString))
        {
            clientsData.push_back(splitDataFileToRecord(clientDataString));
        }
    }

    dataFile.close();

    return clientsData;
}

// function to add table header
void clientsTableHeader()
{
    cout << "-------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(20)
        << " Account Number"
        << "| " << left << setw(12)
        << "Pin Code"
        << "| " << left << setw(35)
        << "Client Name"
        << "| " << left << setw(12)
        << "Phone"
        << "| " << left << setw(20)
        << "Balance"
        << "\n\n-------------------------------------------------------------------------------------------------------\n";
}

// function to add client data to structure
stClientData addClientDataForAddNewClientOption(vector <stClientData>& clientsData)
{
    stClientData clientData;

    cout << "Enter Account Number: ";
    getline(cin >> ws, clientData.accountNumber);

    stClientData isExistAccount = findClientByAccountNumber(clientsData, clientData.accountNumber);

    while (isExistAccount.accountNumber == clientData.accountNumber)
    {
        cout << "Client with [" << clientData.accountNumber << "] already exisit, enter Another Account number: ";
        getline(cin >> ws, clientData.accountNumber);
        isExistAccount = findClientByAccountNumber(clientsData, clientData.accountNumber);

    }

    cout << "Enter Pin Code: ";
    getline(cin, clientData.pinCode);

    cout << "Enter client name: ";
    getline(cin, clientData.clientName);

    cout << "Enter phone Number: ";
    getline(cin, clientData.phone);

    cout << "Enter Account accountBalance: ";
    cin >> clientData.accountBalance;

    return clientData;
}

// function to add client option to structure
stClientData addClientData(string accountNumber, char decision)
{
    stClientData clientData;

    if (decision != 'Y' && decision != 'y')
    {
        cout << "Enter Account Number: ";
        getline(cin >> ws, clientData.accountNumber);

        cout << "Enter Pin Code: ";
        getline(cin, clientData.pinCode);
    }
    else
    {
        clientData.accountNumber = accountNumber;
        cout << "Enter Pin Code: ";
        getline(cin >> ws, clientData.pinCode);
    }

    cout << "Enter client name: ";
    getline(cin, clientData.clientName);

    cout << "Enter phone Number: ";
    getline(cin, clientData.phone);

    cout << "Enter Account accountBalance: ";
    cin >> clientData.accountBalance;

    return clientData;
}

// function to convert client data to string
string convertRecordToString(stClientData clientRecord, string delim = "/##/")
{
    string clientDataString = "";
    clientDataString = clientRecord.accountNumber + delim + clientRecord.pinCode + delim + clientRecord.clientName + delim + clientRecord.phone + delim + to_string(clientRecord.accountBalance);
    return clientDataString;
}

// function to update founded client you looking for by account number in its structure
stClientData updateClientData(vector <stClientData>& clientsData, string accountNumber, char decision = 'N')
{
    stClientData clientData;

    for (int i = 0; i < clientsData.size(); i++)
    {
        if (clientsData[i].accountNumber == accountNumber)
        {
            return clientsData[i] = addClientData(accountNumber, decision);
        }
    }
    return {};
}

// function to print data of selected client 
void printClientData(stClientData clientData, string accountNumber)
{
    if (clientData.accountNumber != "")
    {
        cout << "\nThe folowing are the client data: " << endl;
        cout << "\nAccount Number: " << clientData.accountNumber << endl;
        cout << "Pin Code: " << clientData.pinCode << endl;
        cout << "Client Name: " << clientData.clientName << endl;
        cout << "Phone: " << clientData.phone << endl;
        cout << "Account Balance: " << clientData.accountBalance << endl;
    }
    else
    {
        cout << "\nClient with account Number (" << accountNumber << ") Not Found!" << endl;
    }
}

// function to add clients data to file
void addClientsdataStringToFile(vector <stClientData>& clientsData)
{
    fstream dataFile;
    dataFile.open(fileName, ios::out);

    if (dataFile.is_open())
    {
        for (stClientData client : clientsData)
        {
            dataFile << convertRecordToString(client) << endl;
        }
    }

    dataFile.close();
}

// function to delete the selected client
void updateClientsDataInFile(vector <stClientData>& clientsData, string& accountNumber, char deletionDecision)
{
    stClientData foundedClient = findClientByAccountNumber(clientsData, accountNumber);

    if (toupper(deletionDecision) == 'Y')
    {
        updateClientData(clientsData, accountNumber);
        addClientsdataStringToFile(clientsData);
        cout << "Client Data updated seccesfully";
    }
}

//==============================================

/* start option [1]: show clients list */

// function to show clients list
void showClientsList()
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(33) << "Clients List Screen\n";
    cout << "==================================================\n";

    vector <stClientData> clientsData = getClientsData();

    cout << setw(52) << "Clients List(" << clientsData.size() << ") Client(s)." << endl;

    clientsTableHeader();
    for (stClientData client : clientsData)
    {
        cout << "| " << left << setw(20)
            << client.accountNumber
            << "| " << left << setw(12)
            << client.pinCode
            << "| " << left << setw(35)
            << client.clientName
            << "| " << left << setw(12)
            << client.phone
            << "| " << left << setw(20)
            << client.accountBalance
            << "\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------\n";

}

/* end option [1]: show clients list */

//==============================================

/*start option [2]: add new client */

// function to add new client to file
void addNewClientsToFile(vector <stClientData>& clientsData)
{
    system("cls");
    fstream dataFile;
    dataFile.open(fileName, ios::out | ios::app);
    char addingdecision = 'Y';

    cout << "==================================================\n";
    cout << setw(35) << " Add Client Screen";
    cout << "\n==================================================\n";

    do {
        cout << "Adding New Client:\n\n";

        stClientData newClient = addClientDataForAddNewClientOption(clientsData);


        if (dataFile.is_open())
        {
            dataFile << convertRecordToString(newClient) << endl;
        }
        cout << "Client Added Seccessfully, do you want to add more clients? (Y / N): ";
        cin >> addingdecision;
        cout << "\n";

    } while (toupper(addingdecision) == 'Y');

    dataFile.close();

}

/*end option [2]: add new client */

//==============================================

//==============================================

/*start option [3]: delete client */

// function to delete the selected client
void deletionClientOption(vector <stClientData>& clientsData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(36) << " Delete Client Screen\n";
    cout << "==================================================\n";

    vector <stClientData> newClientsData;
    string accountNumber = enterString("Please Enter Account Number: ");
    stClientData foundedClient = findClientByAccountNumber(clientsData, accountNumber);
    char deletionDecision = 'Y';

    if (foundedClient.accountNumber != "")
    {
        cout << "-----------------------------";
        printClientData(foundedClient, accountNumber);
        cout << "-----------------------------\n";
    }

    cout << "are you sure you want to delete this client? (Y / N): ";
    cin >> deletionDecision;
    cout << "\n";

    if (toupper(deletionDecision) == 'Y')
    {

        for (stClientData& client : clientsData)
        {
            if (foundedClient.accountNumber != client.accountNumber)
            {
                newClientsData.push_back(client);
            }
        }
        clientsData = newClientsData;
        addClientsdataStringToFile(clientsData);
    }

}

/*end option [3]: delete client */

//==============================================


//==============================================

/*start option [4]: update client infos */

void updateClientInfosOption(vector <stClientData>& clientsData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(40) << " update infos Client Screen";
    cout << "\n==================================================\n";

    char upadteDecision = 'Y';
    string accountNumber = enterString("Please Enter Account Number: ");
    stClientData foundedClient = findClientByAccountNumber(clientsData, accountNumber);
    cout << "-----------------------------";
    printClientData(foundedClient, accountNumber);
    cout << "-----------------------------\n";

    if (foundedClient.accountNumber != "")
    {
        cout << "are you sure you want to update infos of this client? (Y / N): ";
        cin >> upadteDecision;
        cout << "\n";

        if (toupper(upadteDecision) == 'Y')
        {
            updateClientData(clientsData, accountNumber, upadteDecision);
            addClientsdataStringToFile(clientsData);
        }
    }
}

/*end option [4]: update client infos */

//==============================================

//==============================================

/*start option [5]: find client */

void findClientOption(vector <stClientData>& clientsData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(40) << " Find Client Screen";
    cout << "\n==================================================\n\n";

    string accountNumber = enterString("Please Enter Account Number: ");
    stClientData foundedClient = findClientByAccountNumber(clientsData, accountNumber);

    cout << "\n-----------------------------";
    printClientData(foundedClient, accountNumber);
    cout << "-----------------------------\n";

}


/*end option [5]: find client */

//==============================================
void showSelectedChoice(vector <stClientData> clientsData, vector <stUserData> usersData, stUserData user);

//==============================================

// function to add main menu screen
void mainMenu()
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(33) << "Main Menu Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] Show Clients List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Infos.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "==================================================\n";
}

// function to select choice
enMainMenuChoices chooseTheChoice()
{
    int chosenChoice = 0;
    cout << "Choose what do you want to do ? [1 to 8] ";
    cin >> chosenChoice;
    return (enMainMenuChoices)chosenChoice;
}

void goBackToMainMenu(vector <stClientData> clientsData, vector <stUserData> usersData, stUserData user)
{
    cout << "press any key to go back to main menu. . .";
    system("pause>0");
    mainMenu();
    showSelectedChoice(clientsData, usersData, user);
}

//function to show selected choice
void showSelectedChoice(vector <stClientData> clientsData, vector <stUserData> usersData, stUserData user)
{
    mainMenu();
    enMainMenuChoices chosenChoice = chooseTheChoice();
    enPermissionChoices permissionChoice;
    switch (chosenChoice)
    {
    case enMainMenuChoices::ShowClientslist:
        if ((user.permission & (short)enPermissionChoices::ShowClientslistPermission) != 0)
        {
            showClientsList();
        }
        else
        {
            cout << "\nAccess Denied, you dont have permission.\n\n";
        }
        goBackToMainMenu(clientsData, usersData, user);
        break;

    case enMainMenuChoices::AddNewClient:
        if ((user.permission & (short)enPermissionChoices::AddNewClientPermission) != 0)
        {
            addNewClientsToFile(clientsData);
        }
        else
        {
            cout << "Access Denied, you dont have permission.\n\n";
        }
        goBackToMainMenu(clientsData, usersData, user);
        break;

    case enMainMenuChoices::DeleteClient:
        if ((user.permission & (short)enPermissionChoices::DeleteClientPermission) != 0)
        {
            deletionClientOption(clientsData);
        }
        else
        {
            cout << "Access Denied, you dont have permission.\n\n";
        }
        goBackToMainMenu(clientsData, usersData, user);
        break;

    case enMainMenuChoices::UpdateClientInfo:
        if ((user.permission & (short)enPermissionChoices::UpdateClientInfoPermission) != 0)
        {
            updateClientInfosOption(clientsData);
        }
        else
        {
            cout << "Access Denied, you dont have permission.\n\n";
        }
        goBackToMainMenu(clientsData, usersData, user);
        break;

    case enMainMenuChoices::FindClient:
        if ((user.permission & (short)enPermissionChoices::FindClientPermission) != 0)
        {
            findClientOption(clientsData);
        }
        else
        {
            cout << "Access Denied, you dont have permission.\n\n";
        }
        goBackToMainMenu(clientsData, usersData, user);
        break;

    case enMainMenuChoices::Trancaction:
        if ((user.permission & (short)enPermissionChoices::TrancactionPermission) != 0)
        {
            showTransactionSelectedChoice(clientsData, usersData, user);
        }
        else
        {
            cout << "Access Denied, you dont have permission.\n\n";
            goBackToMainMenu(clientsData, usersData, user);
        }
        break;

    case enMainMenuChoices::ManageUsers:
        if ((user.permission & (short)enPermissionChoices::ManageUsersPermission) != 0)
        {
            showSelectedChoiceInManageUsersMenu(usersData);
        }
        else
        {
            cout << "Access Denied, you dont have permission.\n\n";
            goBackToMainMenu(clientsData, usersData, user);
        }
        break;

    case enMainMenuChoices::Logout:
        system("cls");
        loginScreen();
        user = loginCheck(usersData);
        showSelectedChoice(clientsData, usersData, user);
        break;

    default:
        break;
    }
}

//==============================================

//==============================================

/* Start option [6]: Transaction */

// function to calculate total balance

double calculateTotlaBalances(vector <stClientData>& clientsData)
{
    double totalBalances = 0;
    for (stClientData& client : clientsData)
    {
        totalBalances += client.accountBalance;
    }

    return totalBalances;
}

// function to print balances table header

void clientsBalancesTableHeader()
{
    cout << "-------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(20)
        << " Account Number"
        << "| " << left << setw(45)
        << "Client Name"
        << "| " << left << setw(30)
        << "Balance"
        << "\n\n-------------------------------------------------------------------------------------------------------\n";
}

// function to show clients list
void showClientsBalancesList()
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(33) << "Balances List Screen\n";
    cout << "==================================================\n";

    vector <stClientData> clientsData = getClientsData();

    cout << setw(52) << "Clients List(" << clientsData.size() << ") Client(s)." << endl;

    clientsBalancesTableHeader();
    for (stClientData client : clientsData)
    {
        cout << "| " << left << setw(20)
            << client.accountNumber
            << "| " << left << setw(45)
            << client.clientName
            << "| " << left << setw(30)
            << client.accountBalance
            << "\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------\n";

}

// function to add main menu screen
void TransactionMenu()
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(33) << "Transaction Menu Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdrow.\n";
    cout << "\t[3] Totale Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "==================================================\n";
}

// function to go back to transaction menu

void goBackToTransactionMenu(vector <stClientData> clientsData, vector <stUserData> usersData, stUserData user)
{
    cout << "\nPress any key to go back to Transaction Menu. . .";
    system("pause>0");
    TransactionMenu();
    showTransactionSelectedChoice(clientsData, usersData, user);
}

/* Start option [1] in transaction menu: Deposit function */

void depositToBalance(vector <stClientData>& clientsData, vector <stUserData>& userssData, stUserData user)
{
    system("cls");
    cout << "--------------------------------------------------\n";
    cout << setw(33) << "Deposit Screen\n";
    cout << "--------------------------------------------------\n";

    string accountNumber = enterString("Please Enter Account Number: ");
    stClientData foundedClient = findClientByAccountNumber(clientsData, accountNumber);
    string confirmDeposit = "";
    double depositAmount = 0;

    cout << "\n-----------------------------";
    printClientData(foundedClient, accountNumber);
    cout << "-----------------------------\n";

    cout << "\nPlease enter deposit amount: ";
    cin >> depositAmount;

    cout << "\nAre you sure you want perform this transaction? y/n: ";
    cin >> confirmDeposit;

    if (confirmDeposit == "y" || confirmDeposit == "Y")
    {
        foundedClient.accountBalance += depositAmount;
        for (int i = 0; i < clientsData.size(); i++)
        {
            if (clientsData[i].accountNumber == accountNumber)
            {
                clientsData[i] = foundedClient;
            }
        }

        addClientsdataStringToFile(clientsData);

        cout << "\nDeposit seccesfully, new balance: " << foundedClient.accountBalance;
    }
    else
    {
        goBackToTransactionMenu(clientsData, userssData, user);
    }
}

/* End option [1] in transaction menu: Deposit function */

/* Start option [1] in transaction menu: Deposit function */

void withdrawFromBalance(vector <stClientData>& clientsData, vector <stUserData> usersData, stUserData user)
{
    system("cls");
    cout << "--------------------------------------------------\n";
    cout << setw(33) << "Withdraw Screen\n";
    cout << "--------------------------------------------------\n";

    string accountNumber = enterString("Please Enter Account Number: ");
    stClientData foundedClient = findClientByAccountNumber(clientsData, accountNumber);
    string confirmWithdraw = "";
    double withdrawAmount = 0;

    cout << "\n-----------------------------";
    printClientData(foundedClient, accountNumber);
    cout << "-----------------------------\n";

    do {
        cout << "\nPlease enter Withdraw amount: ";
        cin >> withdrawAmount;
        if (withdrawAmount > foundedClient.accountBalance)
            cout << "Amount Exceeds the balance, you can withdrow up to : " << foundedClient.accountBalance << "\n";
    } while (withdrawAmount > foundedClient.accountBalance);

    cout << "\nAre you sure you want perform this transaction? y/n: ";
    cin >> confirmWithdraw;

    if (confirmWithdraw == "y" || confirmWithdraw == "Y")
    {
        foundedClient.accountBalance -= withdrawAmount;
        for (int i = 0; i < clientsData.size(); i++)
        {
            if (clientsData[i].accountNumber == accountNumber)
            {
                clientsData[i] = foundedClient;
            }
        }

        addClientsdataStringToFile(clientsData);

        cout << "\nWithdraw seccesfully, new balance: " << foundedClient.accountBalance;
    }
    else
    {
        goBackToTransactionMenu(clientsData, usersData, user);
    }
}

/* End option [1] in transaction menu: Deposit function */

/* Start option [3] in transaction menu: Total balances */

void totalBalances(vector <stClientData>& clientsData)
{
    showClientsBalancesList();

    cout << "\n\t\t\t\t\tTotal Balances: " << calculateTotlaBalances(clientsData) << "\n\n";
}

/* End option [3] in transaction menu: Total balances */

// function to select transaction choice
enTransactionMenuChoices chooseTransactionChoice()
{
    int chosenChoice = 0;
    cout << "Choose what do you want to do ? [1 to 4] ";
    cin >> chosenChoice;
    return (enTransactionMenuChoices)chosenChoice;
}

//function to show selected choice
void showTransactionSelectedChoice(vector <stClientData>& clientsData, vector <stUserData> usersData, stUserData user)
{
    TransactionMenu();
    enTransactionMenuChoices transactionChosenChoice = chooseTransactionChoice();

    switch (transactionChosenChoice)
    {
    case enTransactionMenuChoices::Deposit:
        depositToBalance(clientsData, usersData, user);
        goBackToTransactionMenu(clientsData, usersData, user);
        break;

    case enTransactionMenuChoices::Withdraw:
        withdrawFromBalance(clientsData, usersData, user);
        goBackToTransactionMenu(clientsData, usersData, user);
        break;

    case enTransactionMenuChoices::TotalBalances:
        totalBalances(clientsData);
        goBackToTransactionMenu(clientsData, usersData, user);
        break;

    case enTransactionMenuChoices::Menu:
        goBackToMainMenu(clientsData, usersData, user);
        break;

    default:
        break;
    }
}

/* End option [6]: Transaction */

//==============================================

//==============================================

/* Start option [7]: Manage users */

// function to add Manage users main menu screen
void manageUsersMenu()
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(33) << "Manage Users Menu Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] Users List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "==================================================\n";
}

// function to select choice in manage users menu
enManageUsersMenuChoices chooseTheChoiceInManageUsersMenu()
{
    int chosenChoice = 0;
    cout << "Choose what do you want to do ? [1 to 6] ";
    cin >> chosenChoice;
    return (enManageUsersMenuChoices)chosenChoice;
}

// function to convert client data to string
string convertUserRecordToString(stUserData userRecord, string delim = "/##/")
{
    string userDataString = "";
    userDataString = userRecord.userName + delim + to_string(userRecord.password) + delim + to_string(userRecord.permission);
    return userDataString;
}

// function to split user data in string to structure
stUserData splitUserDataFileToRecord(string fileDataString, string delim = "/##/")
{
    stUserData UserDataRecord;
    vector <string> userData;
    int pos = 0;
    string word = "";

    while ((pos = fileDataString.find(delim)) != std::string::npos)
    {
        word = fileDataString.substr(0, pos);
        userData.push_back(word);
        fileDataString.erase(0, pos + delim.length());
    }

    if (fileDataString != "")
    {
        userData.push_back(fileDataString);
    }

    UserDataRecord.userName = userData[0];
    UserDataRecord.password = stoi(userData[1]);
    UserDataRecord.permission = (short)stoi(userData[2]);

    return UserDataRecord;
}

// function to print data of selected client 
void printUserData(stUserData UserData, string username)
{
    if (UserData.userName != "")
    {
        cout << "\nThe folowing are the User data: " << endl;
        cout << "\nUsername: " << UserData.userName << endl;
        cout << "Password: " << UserData.password << endl;
        cout << "Permission: " << UserData.permission << endl;
    }
    else
    {
        cout << "\nuser with username (" << username << ") Not Found!" << endl;
    }
}

// function to find user you looking for by username and password in file
stUserData findUserToLogin(vector <stUserData>& usersData, string username, int password)
{
    stUserData userData;

    for (int i = 0; i < usersData.size(); i++)
    {
        if (usersData[i].userName == username && usersData[i].password == password)
        {
            userData = usersData[i];

            return userData;
        }
    }
    return {};
}

// function to find user you looking for by username in file
stUserData findUser(vector <stUserData>& usersData, string username)
{
    stUserData userData;

    for (int i = 0; i < usersData.size(); i++)
    {
        if (usersData[i].userName == username)
        {
            userData = usersData[i];

            return userData;
        }
    }
    return {};
}

// function to add users data to file
void addUsersdataStringToFile(vector <stUserData>& usersData, bool isDeleteUser = true)
{
    fstream dataFile;
    if (isDeleteUser)
        dataFile.open(UsersfileName, ios::out);
    else
        dataFile.open(UsersfileName, ios::out | ios::app);

    if (dataFile.is_open())
    {
        for (stUserData& user : usersData)
        {
            dataFile << convertUserRecordToString(user) << endl;
        }
    }

    dataFile.close();
}

// function to fill vector with clients data that exist in file
vector <stUserData> getUsersData(string delim)
{
    vector <stUserData> usersData;
    string userDataString = "";
    fstream dataFile;

    dataFile.open(UsersfileName, ios::in);


    if (dataFile.is_open())
    {
        while (getline(dataFile, userDataString))
        {
            usersData.push_back(splitUserDataFileToRecord(userDataString));
        }
    }

    dataFile.close();

    return usersData;
}

// function to find user
void findUserOption(vector <stUserData>& usersData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(40) << " Find User Screen";
    cout << "\n==================================================\n";

    string username = enterString("Please Enter usermane: ");
    stUserData foundedUser = findUser(usersData, username);
    string searchDicision = "";
    while (foundedUser.userName == "")
    {
        cout << "User not found, dou you want to seach again? y/n ";
        cin >> searchDicision;
        if (searchDicision == "y" || searchDicision == "Y")
            username = enterString("Please Enter usermane: ");

        foundedUser = findUser(usersData, username);
    }

    cout << "\n-----------------------------";
    printUserData(foundedUser, username);
    cout << "-----------------------------\n";

}

int userPermissions(string fullAccessPermission)
{
    string accessPermission;
    int accessNumber = 0;
    if (fullAccessPermission == "y" || fullAccessPermission == "Y")
        return accessNumber = -1;

    cout << "Do you want to give access to: \n";
    cout << "Show Clients List (y/n): ";
    getline(cin >> ws, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 1;

    cout << "Add New Client (y/n): ";
    getline(cin, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 2;

    cout << "Delete Client (y/n): ";
    getline(cin, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 4;

    cout << "Update Client (y/n): ";
    getline(cin, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 8;

    cout << "Find Client (y/n): ";
    getline(cin, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 16;

    cout << "Transactions (y/n): ";
    getline(cin, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 32;

    cout << "Manage Users (y/n): ";
    getline(cin, accessPermission);
    if (accessPermission == "y" || accessPermission == "Y")
        accessNumber = accessNumber | 64;

    return accessNumber;
}

// function to add client data to structure
stUserData addUserData(vector <stUserData>& usersData)
{
    stUserData userData;
    string fullAccessPermission = "";

    cout << "Enter Username: ";
    getline(cin >> ws, userData.userName);

    stUserData isExistUser = findUser(usersData, userData.userName);

    while (isExistUser.userName == userData.userName)
    {
        cout << "user with [" << userData.userName << "] already exist, enter Another username: ";
        getline(cin >> ws, userData.userName);
        isExistUser = findUser(usersData, userData.userName);
    }

    cout << "Enter password: ";
    cin >> userData.password;

    cout << "Do you want to give this user full access (y/n): ";
    cin >> fullAccessPermission;

    userData.permission = userPermissions(fullAccessPermission);

    return userData;
}

// function to update founded client you looking for in its structure
vector <stUserData> addUserToVector(vector <stUserData> usersData, stUserData user, string username)
{

    for (int i = 0; i < usersData.size(); i++)
    {
        if (usersData[i].userName == username)
        {
            usersData[i] = user;
            return usersData;
        }
    }
    usersData.push_back(user);
    return usersData;
}

// function to add users option
void addUserOption(vector <stUserData>& usersData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(40) << " Add New User Screen";
    cout << "\n==================================================\n";
    stUserData user = addUserData(usersData);
    addUsersdataStringToFile(usersData);
}

// function to delete user 
void deleteUserFromVector(vector <stUserData>& usersData)
{
    vector <stUserData> newUsersData;
    stUserData userData;
    string deleteDecision = "";

    cout << "Enter Username: ";
    getline(cin >> ws, userData.userName);

    stUserData isExistUser = findUser(usersData, userData.userName);

    if (isExistUser.userName == "Admin")
    {
        cout << "You cant delete Admin User\n\n";
    }
    else
    {
        while (isExistUser.userName != userData.userName)
        {
            cout << "User with [" << userData.userName << "] not exisit, enter Another username: ";
            getline(cin >> ws, userData.userName);
            isExistUser = findUser(usersData, userData.userName);
        }

        cout << "are you sure you want to delete this user? (y/n): ";
        getline(cin >> ws, deleteDecision);
        cout << "\n";

        if (deleteDecision == "y" || deleteDecision == "Y")
        {
            for (stUserData& user : usersData)
            {
                if (isExistUser.userName != user.userName)
                {
                    newUsersData.push_back(user);
                }
            }
        }

        usersData = newUsersData;
    }
}

// function to delete users option
void deleteUserOption(vector <stUserData>& usersData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(40) << " Delete User Screen";
    cout << "\n==================================================\n";

    deleteUserFromVector(usersData);
    addUsersdataStringToFile(usersData);
}

// function to update user data to structure
vector <stUserData> updateUserData(vector <stUserData> usersData)
{
    stUserData userData;
    string username;
    string fullAccessPermission = "";

    cout << "Enter Username: ";
    getline(cin >> ws, username);

    stUserData isExistUser = findUser(usersData, username);

    while (isExistUser.userName != username)
    {
        cout << "user with [" << username << "] does not exist, enter Another Username: ";
        getline(cin >> ws, username);
        isExistUser = findUser(usersData, username);
    }

    cout << "\n-----------------------------";
    printUserData(isExistUser, username);
    cout << "-----------------------------\n";

    cout << "Updating User Data: \n";

    cout << "Enter Username: ";
    getline(cin >> ws, userData.userName);

    cout << "Enter password: ";
    cin >> userData.password;

    cout << "Do you want to give this user full access (y/n): ";
    cin >> fullAccessPermission;

    userData.permission = userPermissions(fullAccessPermission);

    usersData = addUserToVector(usersData, userData, username);

    return usersData;
}

// function to update user data option
void updateUserOption(vector <stUserData> usersData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(40) << " Update User Screen";
    cout << "\n==================================================\n";

    usersData = updateUserData(usersData);
    addUsersdataStringToFile(usersData);
}

// function to go banck to manage users menu
void goBackToManageUsersMenu(vector <stUserData>& usersData)
{
    cout << "press any key to go back to main menu. . .";
    system("pause>0");
    manageUsersMenu();
    showSelectedChoiceInManageUsersMenu(usersData);
}

//function to show selected choice
void showSelectedChoiceInManageUsersMenu(vector <stUserData>& usersData)
{
    manageUsersMenu();
    enManageUsersMenuChoices chosenChoice = chooseTheChoiceInManageUsersMenu();
    switch (chosenChoice)
    {
    case enManageUsersMenuChoices::UsersList:
        usersList(usersData);
        goBackToManageUsersMenu(usersData);
        break;

    case enManageUsersMenuChoices::AddNewUser:
        addUserOption(usersData);
        goBackToManageUsersMenu(usersData);
        break;

    case enManageUsersMenuChoices::DeleteUser:
        deleteUserOption(usersData);
        goBackToManageUsersMenu(usersData);
        break;

    case enManageUsersMenuChoices::UpdateUser:
        updateUserOption(usersData);
        goBackToManageUsersMenu(usersData);
        break;

    case enManageUsersMenuChoices::FindUser:
        findUserOption(usersData);
        goBackToManageUsersMenu(usersData);
        break;

    case enManageUsersMenuChoices::menu:
        mainMenu();
        break;

    default:
        break;
    }
}

// function to add users table header
void UsersTableHeader()
{
    cout << "-------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(20)
        << " Username"
        << "| " << left << setw(12)
        << "Password"
        << "| " << left << setw(35)
        << "Permission"
        << "\n\n-------------------------------------------------------------------------------------------------------\n";
}

// function to show clients list
void usersList(vector <stUserData>& usersData)
{
    system("cls");
    cout << "==================================================\n";
    cout << setw(33) << "Users List Screen\n";
    cout << "==================================================\n";

    cout << setw(52) << "Users List(" << usersData.size() << ") User(s)." << endl;

    UsersTableHeader();

    for (stUserData& user : usersData)
    {
        cout << "| " << left << setw(20)
            << user.userName
            << "| " << left << setw(12)
            << user.password
            << "| " << left << setw(35)
            << user.permission
            << "\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------\n";
}

/* End option [7]: Manage users */

//==============================================

void loginScreen()
{
    system("cls");
    cout << "--------------------------------------------------\n";
    cout << setw(33) << "Login Screen\n";
    cout << "--------------------------------------------------\n";
}

stUserData loginCheck(vector <stUserData>& usersData)
{
    stUserData userData;
    userData.userName = enterString("Enter Username: ");
    userData.password = stoi(enterString("Enter password: "));
    stUserData foundedUser = findUserToLogin(usersData, userData.userName, userData.password);

    while (userData.userName != foundedUser.userName || userData.password != foundedUser.password)
    {
        system("cls");
        loginScreen();
        cout << "invalid username/password\n";
        userData.userName = enterString("Enter Username: ");
        userData.password = stoi(enterString("Enter password: "));
        foundedUser = findUserToLogin(usersData, userData.userName, userData.password);
    }
    return foundedUser;
}

int main()
{
    loginScreen();
    vector <stClientData> ClientsData = getClientsData();
    vector <stUserData> usersData = getUsersData();
    stUserData user = loginCheck(usersData);

    showSelectedChoice(ClientsData, usersData, user);

    return 0;
}