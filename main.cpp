#include "stdc++.h"
#include "algorithms.h"
#include "rsa.h"

using namespace std;

int main() {
    cout << "Welcome to Crypto - Systems" << endl;
    int choice = 0;

    do {
        string plain_text;
        string cipher_text;

        display_choices();

        cout << "Enter your choice of encryption: ";
        cin >> choice;

        if (choice <= 8 && choice > 0) {
            cout << endl << "Enter plain text: ";
            cin.ignore();  // clearing the newline character left in the buffer
            getline(cin, plain_text);
            cout << endl;
        }

        switch (choice) {
            case 1:
                cipher_text = ceaser_cipher(plain_text);
                cout << endl << "Cipher text for plain text: " << plain_text << " is " << cipher_text << endl;
                break;

            case 2:
                cipher_text = affine_cipher(plain_text);
                cout << endl << "Cipher text for plain text: " << plain_text << " is " << cipher_text << endl;
                break;

            case 3:
                cipher_text = auto_key_cipher(plain_text);
                cout << endl << "Cipher text for plain text: " << plain_text << " is " << cipher_text << endl;
                break;

            case 4:
                cipher_text = vignere_cipher(plain_text);
                cout << endl << "Cipher text for plain text: " << plain_text << " is " << cipher_text << endl;
                break;

            case 5:
                cipher_text = hill_cipher(plain_text);
                cout << endl << "Cipher text for plain text: " << plain_text << " is " << cipher_text << endl;
                break;

            case 6:
                // cipher_text = playfair_cipher(plain_text);
                cout << endl << "Cipher text for plain text: " << plain_text << " is " << cipher_text << endl;
                break;

            case 7: {
                long long n = 0, e = 0, d = 0;
                generate_keys(n, e, d);

                vector<long long> numeric_message = string_to_numeric(plain_text);

                vector<long long> encrypted_message;
                for (long long num: numeric_message) {
                    if (num == 27) // Ignore spaces or other special handling if required
                        continue;
                    encrypted_message.push_back(encrypt_rsa(num, e, n));
                }

                cout << "Encrypted message: ";
                for (long long num: encrypted_message) {
                    cout << num << " ";
                }
                cout << endl;
                break;
            }

            case 8:
                cout << "*************Exiting***********" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

// Created by Lokranjan P on 25/05/24.
