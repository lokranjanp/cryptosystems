#include "stdc++.h"
using namespace std;
    vector<int> invZ26 = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

//    int alpha_num(char c) {
//        if (isalpha(c))
//            return int(c);
//
//        return -1;
//    }

    int choose_key(bool inv) {
        srand(time(0));

        char choice;
        cout << "Do you want a random key ?(Y/N)" << endl;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            if (inv)
                return invZ26[rand() % invZ26.size()];

            return rand() % 26;
        } else if (choice == 'n' || choice == 'N') {
            int input = 0;
            cout << "Enter key of choice : ";
            cin >> input;
            return input;
        } else
            return -1;
    }

    void display_choices() {
        cout << endl;
        cout << "1. Ceaser Cipher\n2. Affine Cipher\n3. Auto Key Cipher\n4. Vignere Cipher\n5. Hill Cipher\n6. Exit\n" << endl;
    }

    string ceaser_cipher(string &plain) {
        int key = choose_key(false);
        cout << "Key is : " << key << endl;
        if (key == -1) {
            return "ERROR";
        }

        string res;
        for (auto c: plain) {
            if (isalpha(c)) {
                char offset = isupper(c) ? 'A' : 'a';
                res += ((c - offset + key) % 26 + offset);
            } else
                res += c;
        }
        return res;
    }

    string affine_cipher(string &plain) {
        int addit_key = choose_key(false);
        bool inv_exists = true;
        int mult_key = choose_key(inv_exists);

        string res;
        for (auto c: plain) {
            if (isalpha(c)) {
                char offset = isupper(c) ? 'A' : 'a';

                res += (mult_key * (c - offset) + addit_key) % 26 + offset;
            }
        }
        return res;
    }

    string auto_key_cipher(string &plain) {
        int key = choose_key(false);
        cout << "Key is : " << key << endl;
        if (key == -1) {
            return "ERROR";
        }
        string res = "";
        for (auto c: plain) {
            if (isalpha(c)) {
                char offset = isupper(c) ? 'A' : 'a';
                res += ((c - offset + key) % 26 + offset);
                key = c - offset;
            } else
                res += c;
        }
        return res;
    }


    int main() {

        cout << "Welcome to Crypto - systems" << endl;
        int choice = 0;
        do{

            string plain_text;
            string cipher_text;


        cout << endl;



            display_choices();
            cout << "Enter your choice of encryption : ";
            cin >> choice;
            if(choice-6){
            cout << "Enter plain text : " << " ";
            cin >> plain_text;
            }

            switch (choice) {
                case 1:
                    cipher_text = ceaser_cipher(plain_text);
                    cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;
                case 2:
                    cipher_text = affine_cipher(plain_text);
                    cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

                case 3:
                    cipher_text = auto_key_cipher(plain_text);
                    cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

                case 4:
                    //cipher_text = vignere_cipher(plain_text);
                    cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

                case 5:
                    //cipher_text = playfair_cipher(plain_text);
                    cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

                default:
                    cout << "*************Exiting***********" << endl;
            //  cin >> choice;
            }
        }while(choice!=6);

    }