#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string plaintextMessage;
string repeatedKey;

// Manual validation of input
bool isValidMessage(const string& msg) 
{
    for (char c : msg)
    {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// Function to get message and key from the user
void initializeMessageAndKey() 
{
    string message, key;

    // Input message
    cout << "\nEnter your message (letters only): ";
    getline(cin, message);
    while (!isValidMessage(message)) 
    {
        cout << "\nInvalid message, use letters only. Try again: ";
        getline(cin, message);
    }

    // Input key
    cout << "\nEnter your key (letters only): ";
    getline(cin, key);
    while (!isValidMessage(key) || key.empty()) 
    {
        cout << "\nInvalid key, it must be letters only and not empty. Try again: ";
        getline(cin, key);
    }

    // Uppercase transformation (manual loop for better clarity)
    for (char& c : message) c = toupper(c);
    for (char& c : key) c = toupper(c);

    // Key mapping to match the message length
    repeatedKey = "";
    int keyIndex = 0;
    for (char c : message) 
    {
        if (c == ' ')
        {
            repeatedKey += ' ';
        }
        else 
        {
            repeatedKey += key[keyIndex % key.length()];
            keyIndex++;
        }
    }

    plaintextMessage = message;
}

// Encrypt message using Vigenere cipher
void performEncryption() 
{
    string encryptedMessage = "";
    for (int i = 0; i < plaintextMessage.length(); ++i) 
    {
        if (plaintextMessage[i] == ' ')
        {
            encryptedMessage += ' ';
        }
        else 
        {
            int row = plaintextMessage[i] - 'A';
            int col = repeatedKey[i] - 'A';
            encryptedMessage += 'A' + (row + col) % 26;
        }
    }
    cout << "\nEncrypted Message: " << encryptedMessage << endl << endl;
}

// Decrypt message using Vigenere cipher
void performDecryption() 
{
    string decryptedMessage = "";
    for (int i = 0; i < plaintextMessage.length(); ++i) 
    {
        if (plaintextMessage[i] == ' ') 
        {
            decryptedMessage += ' ';
        }
        else 
        {
            int row = plaintextMessage[i] - 'A';
            int col = repeatedKey[i] - 'A';
            decryptedMessage += 'A' + (row - col + 26) % 26;
        }
    }
    cout << "\nDecrypted Message: " << decryptedMessage << endl << endl;
}

int main()
{
    int choice;
    while (true) 
    {
        cout << "1. Encrypt\n2. Decrypt\n3. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore(); // Clear newline left by cin

        if (choice == 1) 
        {
            initializeMessageAndKey();
            performEncryption();
        }
        else if (choice == 2)
        {
            initializeMessageAndKey();
            performDecryption();
        }
        else if (choice == 3) 
        {
            cout << "\nGoodbye!" << endl;
            break;
        }
        else 
        {
            cout << "\nInvalid choice. Try again.\n\n";
        }
    }

    return 0;
}
