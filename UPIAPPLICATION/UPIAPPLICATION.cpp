#include<iostream>
#include<sstream>
#include<map>
#include<iterator>
#include<fstream>
#include<windows.h>
using namespace std;
class UPI {
public:
    string Upi;
    string Name;
    string Password;
    int Amount;
    string Mobile;
    string Bank;
    string Notification;
};
UPI* Records = new UPI[1001];
int index = 0;
map<string, int>UPIDATA;
void openfile();
void savefile();
void create();
void login();
void mainmenu();
int main() {
    system("color a");
    openfile();
    while (1) {
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\t||\t          MAIN MENU                 \t||" << endl;
        cout << "\t\t\t\t||\t     Press 1--> Sign Up             \t||" << endl;
        cout << "\t\t\t\t||\t     Press 2--> Login               \t||" << endl;
        cout << "\t\t\t\t||\t     Press 3--> Delete all data     \t||" << endl;
        cout << "\t\t\t\t||\t     Press 4--> Exit                \t||" << endl;
        cout << "\t\t\t\t==================================================" << endl;
        cout << "Option>>";
        int choice,des;
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            create();
            mainmenu();
            break;
        case 2:
            system("cls");
            login();
            mainmenu();
            break;
        case 3:
            system("cls");
            cout << endl << "[ Total UPI Data Found ]: " << index << endl;
            cout << "[ Confirm to Delete all Records ]? (1,0) " << endl;
            cout << "Option>>";
            cin >> des;
            if (!des) { mainmenu(); break; }
            index = 0;
            savefile();
            cout << "\t\t\t\t\t...[ Datas Deleted Successfully ]..." << endl;
            mainmenu();
            break;
        case 4:
            for (int i = 0; i < 8; i++) {
                system("cls");
                for (int j = 0; j <i+ 3; j++) {
                    cout << endl;
                }
                cout << "\t\t\t\t...[ Thank you for using this application ]..." << endl;
                Sleep(600);
            }
            system("cls");
            return 0;
        default:
            cout << "\t\t\t\t         ...[ Enter Valid Option ]..." << endl;
        }
    }
}
void Processmenu() {
repeat:
    cout << endl;
    int choice;
    cout << "[Go to Process Menu Press 1]" << endl << "Option>>";
    cin >> choice;
    if (choice == 1) {
        system("cls");
        return;
    }
    else {
        goto repeat;
    }
}
void mainmenu() {
repeat:
    cout << endl;
    int choice;
    cout << "[Go to Main Menu Press 1]" << endl << "Option>>";
    cin >> choice;
    if (choice == 1) {
        system("cls");
        return;
    }
    else {
        goto repeat;
    }
}
void openfile() {
    string line;
    ifstream myFile("UpiData.txt");
    if (myFile.is_open()) {
        string data[8];
        while (getline(myFile, line)) {
            string s;
            stringstream x(line);
            int ind = 0;
            while (getline(x, s, ',')) {
                data[ind++] = s;
            }
            if (ind != 1) {
                int indexval = 0, Amountval = 0;
                stringstream intval(data[0]);
                stringstream amountval(data[3]);
                intval >> indexval;
                amountval >> Amountval;
                index = indexval;
                Records[index].Name = data[1];
                Records[index].Password = data[2];
                Records[index].Amount = Amountval;
                Records[index].Mobile = data[4];
                Records[index].Bank = data[5];
                Records[index].Upi = data[6];
                Records[index].Notification = data[7];
                UPIDATA.insert(pair<string, int>(Records[index].Upi, index));
                index++;
            }
        }
    }
}
void savefile() {
    ofstream SavemyFile("UpiData.txt");
    for (int ind = 0; ind < index; ind++) {
        SavemyFile << ind << "," << Records[ind].Name << "," << Records[ind].Password << "," << Records[ind].Amount << "," << Records[ind].Mobile << "," << Records[ind].Bank << "," << Records[ind].Upi << "," << Records[ind].Notification << endl;
    }
}
void Transfer(int ind) {
    map<string, int>::iterator iter;
    string upi, msg, str;
    int amount = 0, receiverind = 0;
    cout << endl;
    cout << "[ Enter Receiver UPI Id ]: ";
    cin >> upi;
    if (Records[ind].Upi == upi) {
        cout << "\t\t\t\t...[ Sender and Receiver UPI must be Different ]..." << endl;
        return;
    }
    iter = UPIDATA.find(upi);
    if (iter == UPIDATA.end()) {
        cout << "\t\t\t\t!!![ UPI ID Not Found ]!!!" << endl;
        return;
    }
    receiverind = iter->second;
repeat:
    cout << "[ Enter Amount to Transfer ]: ";
    cin >> amount;
    ostringstream x;
    x << amount;
    str = x.str();
    if (Records[ind].Amount <= amount) {
        cout << "\t\t\t\t...[ Insufficient Balance ]..." << endl<<"\t\t\t\t [ Try Again ]"<<endl;
        Sleep(900);
        goto repeat;
    }
    Records[ind].Amount -= amount;
    Records[receiverind].Amount += amount;
    msg = "[You have Received Rs." + str + " from " + Records[ind].Name + "]. ";
    Records[receiverind].Notification.append(msg);
    savefile();
    cout << "\t\t\t\t...[ Transaction Successfully ]..." << endl;
}
void Request(int ind) {
    map<string, int>::iterator iter;
    string upi, amount, msg;
    int receiverind = 0;
    cout << endl;
    cout << "[ Enter Receiver UPI Id ]: ";
    cin >> upi;
    if (Records[ind].Upi == upi) {
        cout << "\t\t\t\t...[ Sender and Receiver UPI must be Different ]..." << endl;
        return;
    }
    iter = UPIDATA.find(upi);
    if (iter == UPIDATA.end()) {
        cout << "\t\t\t\t!!![ UPI ID Not Found ]!!!" << endl;
        return;
    }
    receiverind = iter->second;
repeat:
    cout << "[ Enter Amount to Request ]: ";
    cin >> amount;
    msg = "[You have Requested Rs." + amount + " from " + Records[ind].Name + "]. ";
    Records[receiverind].Notification.append(msg);
    savefile();
    cout << "\t\t\t\t...[ Amount Requested Successfully ]..." << endl;
}
void process(int ind) {
repeat:
    cout << "\t\t\t\t==================================" << endl;
    cout << "\t\t\t\t||     Press 1--> Transfer      ||" << endl;
    cout << "\t\t\t\t||     Press 2--> Request       ||" << endl;
    cout << "\t\t\t\t||     Press 3--> Check Balance ||" << endl;
    cout << "\t\t\t\t||     Press 4--> Logout        ||" << endl;
    cout << "\t\t\t\t==================================" << endl;
    cout << "Option>>";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        Transfer(ind);
        Processmenu();
        goto repeat;
    case 2:
        system("cls");
        Request(ind);
        Processmenu();
        goto repeat;
    case 3:
        system("cls");
        cout << "\t\t\t\t[ Available Balance ]: Rs." << Records[ind].Amount << "/-" << endl;
        Processmenu();
        goto repeat;
    case 4:
        system("cls");
        cout << "\n\n\n\t\t\t\t\t...[ Logout Successfull ]..." << endl;
        return;
    default:
        cout << "\t\t\t\t...[ Enter Valid Option ]..." << endl;
        Processmenu();
        goto repeat;
    }
}
void create() {
    map<string, int>::iterator iter;
    cin.ignore();
    cout << endl;
    cout << "\t\t\t\t\t[ Create Account ]" << endl;
    cout << "[ Enter Name ]: ";
    getline(cin, Records[index].Name);
    cout << "[ Enter Mobile Number ]: ";
    cin >> Records[index].Mobile;
    cout << "[ Create Password ]: ";
    cin >> Records[index].Password;
    cout << "[ Enter Bank ]: ";
    cin >> Records[index].Bank;
    Records[index].Upi = Records[index].Mobile + "@" + Records[index].Bank;
    iter = UPIDATA.find(Records[index].Upi);
    if (iter == UPIDATA.end()) {
        cout << "[ Enter Initial Deposit Amount ]: ";
        cin >> Records[index].Amount;
        Records[index].Notification = " ";
        cout << "\t\t\t\t  ...[ Your UPI ID is " << Records[index].Upi << " ]..." << endl;
        UPIDATA.insert(pair<string, int>(Records[index].Upi, index));
        index++;
        savefile();
        cout << "\t\t\t\t  ...[ Account Created Successfully ]..." << endl;
    }
    else {
        cout << "\t\t\t\t...[ You have already created with this mobile and bank ]..." << endl;
    }
}
void login() {
    string upi, pass;
    map<string, int>::iterator iter;
    cout << endl;
    cout << "\t\t\t\t\t\t [ Login ]" << endl;
    cout << "[ Enter UPI ID ]: ";
    cin >> upi;
    cout << "[ Enter Password ]: ";
    cin >> pass;
    iter = UPIDATA.find(upi);
    if (iter == UPIDATA.end()) {
        cout << "\t\t\t\t\t !!![ UPI ID Not Found ]!!!" << endl;
        return;
    }
    int upiindex = iter->second;
    if (pass != Records[upiindex].Password) {
        cout << "\t\t\t\t\t  ![ Password is incorrect ]!" << endl;
        return;
    }
    system("cls");
    cout << endl;
    cout << "\t\t\t\t\t\t[ Notifications ]" << endl << Records[upiindex].Notification << endl;
    cout << endl << endl;
    cout << "\t\t\t\t===================================================" << endl;
    cout << "\t\t\t\t       [ Bank ]   : " << Records[upiindex].Bank << endl;
    cout << "\t\t\t\t       [ Name ]   : " << Records[upiindex].Name << endl;
    cout << "\t\t\t\t       [ Mobile ] : " << Records[upiindex].Mobile << endl;
    cout << "\t\t\t\t       [ Balance ]: Rs." << Records[upiindex].Amount << "/-" << endl;
    cout << "\t\t\t\t===================================================" << endl;
    Records[upiindex].Notification = " ";
    savefile();
    Processmenu();
    process(upiindex);
    return;
}
