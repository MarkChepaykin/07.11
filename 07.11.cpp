#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Directory {
private:
    string companyName;
    string owner;
    string phone;
    string address;
    string businessType;

public:
    Directory(string compName, string own, string ph, string addr, string busType)
        : companyName(compName), owner(own), phone(ph), address(addr), businessType(busType) {}

    // Методы для доступа к полям класса
    string getCompanyName() const { return companyName; }
    string getOwner() const { return owner; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getBusinessType() const { return businessType; }

    // Статический метод для поиска в векторе записей
    static vector<Directory> search(const vector<Directory>& directories, const string& query, int field) {
        vector<Directory> results;
        for (const auto& entry : directories) {
            switch (field) {
            case 1:
                if (entry.getCompanyName() == query) results.push_back(entry);
                break;
            case 2:
                if (entry.getOwner() == query) results.push_back(entry);
                break;
            case 3:
                if (entry.getPhone() == query) results.push_back(entry);
                break;
            case 4:
                if (entry.getBusinessType() == query) results.push_back(entry);
                break;
            default:
                break;
            }
        }
        return results;
    }

    // Метод для отображения данных
    void display() const {
        cout << "Company Name: " << companyName
            << ", Owner: " << owner
            << ", Phone: " << phone
            << ", Address: " << address
            << ", Business Type: " << businessType << endl;
    }

    // Функция для чтения данных из файла
    static vector<Directory> readFromFile(const string& filename) {
        vector<Directory> directories;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string compName, own, ph, addr, busType;
            getline(ss, compName, ',');
            getline(ss, own, ',');
            getline(ss, ph, ',');
            getline(ss, addr, ',');
            getline(ss, busType, ',');
            directories.emplace_back(compName, own, ph, addr, busType);
        }
        file.close();
        return directories;
    }

    // Функция для записи данных в файл
    static void writeToFile(const string& filename, const Directory& directory) {
        ofstream file(filename, ios::app); // Открываем файл для дозаписи
        file << directory.getCompanyName() << ","
            << directory.getOwner() << ","
            << directory.getPhone() << ","
            << directory.getAddress() << ","
            << directory.getBusinessType() << endl;
        file.close();
    }


};




int showMenu() {
    int choice;
    cout << "\n*** Directory ***\n";
    cout << "1. Search by company name\n";
    cout << "2. Search by owner\n";
    cout << "3. Search by phone number\n";
    cout << "4. Search by type of business\n";
    cout << "5. Show all entries\n";
    cout << "6. Add entry\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void addDirectoryEntry(const string& filename) {
    string compName, owner, phone, address, businessType;
    cout << "Enter company name: ";
    getline(cin, compName);
    cout << "Enter owner's name: ";
    getline(cin, owner);
    cout << "Enter phone number: ";
    getline(cin, phone);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter type of business: ";
    getline(cin, businessType);
    Directory newEntry(compName, owner, phone, address, businessType);
    Directory::writeToFile(filename, newEntry);
    cout << "Entry added.\n";
}


int main() {
    string filename = "directory.txt";
    vector<Directory> directories = Directory::readFromFile(filename);

    int choice;
    do {
        choice = showMenu();
        string query;
        vector<Directory> searchResults;

        switch (choice) {
        case 1:
        case 2:
        case 3:
        case 4:
            cout << "Enter search query: ";
            getline(cin, query);
            searchResults = Directory::search(directories, query, choice);
            if (searchResults.empty()) {
                cout << "No entries found.\n";
            }
            else {
                for (const auto& entry : searchResults) {
                    entry.display();
                }
            }
            break;
        case 5:
            for (const auto& entry : directories) {
                entry.display();
            }
            break;
        case 6:
            addDirectoryEntry(filename);
            // Refresh the list after adding a new entry
            directories = Directory::readFromFile(filename);
            break;
        case 7:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}