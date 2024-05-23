#include "stdc++.h"
using namespace std;
const int NUM = 26;

vector<int> invZ26 = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

int alpha_num(char c){
    if(isalpha(c))
        return int(c);

    return -1;
}

int choose_key(bool inv){
    srand(time(nullptr));

    char choice;
    cout<<"Do you want a random key ?(Y/N)"<<endl;
    cin>>choice;
    if(choice == 'y' || choice == 'Y'){
        if(inv)
            return invZ26[rand() % invZ26.size()];

        return rand()%26;
    }
    else if(choice == 'n' || choice == 'N'){
        int input = 0;
        cout << "Enter key of choice : ";
        cin >> input;
        return input;
    }
    else
        return -1;
}

string choose_string_key(int key_size){
    string key;
    cout<<"Enter input string key lesser than size "<<key_size<<": ";
    cin>>key;

    return key;
}

int choose_matrix_key(int plain_size){
    int mat_size;
    cout<<"Enter the size for the square matrix : ";
    cin>>mat_size;
    if(plain_size%mat_size!=0){
        cout<<"Choose different size, should divide plain text equally"<<endl;
        return choose_matrix_key(plain_size);
    }

    return mat_size;
}

void display_choices(){
    cout<<endl;
    cout<<"1. Ceaser Cipher\n2. Affine Cipher\n3. Auto Key Cipher\n4. Vignere Cipher\n5. Hill Cipher\n"<<endl;
}

string ceaser_cipher(string &plain){
    int key = choose_key(false);
    cout<<"Key is : "<<key<<endl;
    if(key == -1){
        return "ERROR";
    }

    string res;
    for(auto c : plain){
        if(isalpha(c)){
            char offset = isupper(c) ? 'A' : 'a';
            res += (std::to_string((c - offset + key)%26 + offset));
        }
        else
            res += c;
    }
    return res;
}

string affine_cipher(string &plain){
    int addit_key = choose_key(false);
    bool inv_exists = true;
    int mult_key = choose_key(inv_exists);

    string res;
    for(auto c : plain){
        if(isalpha(c)){
            char offset = isupper(c) ? 'A' : 'a';

            res += (mult_key * (c - offset) + addit_key)%26 + offset;
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
        string res;
        for (auto c: plain) {
            if (isalpha(c)) {
                char offset = isupper(c) ? 'A' : 'a';
                res += (std::to_string((c - offset + key) % 26 + offset));
                key = c - offset;
            } else
                res += c;
        }
        return res;
}

string vignere_cipher(string &plain){
    string res;
    string key = choose_string_key(plain.size());
    int j = 0;

    for(int i = 0; i<plain.size(); i++){
        char c = plain[i];
        char k = key[j];
        if(isalpha(c))
        {
            char offset_char =  isupper(c) ? 'A' : 'a';
            char offset_key = isupper(k) ? 'A' : 'a';
            res += std::to_string(((c - offset_char) + (k - offset_key))%26 + offset_char);
        }
        else
            res += c;
        j++;
        if(j==key.size())
            j = 0;

    }
    return res;
}

vector<vector<int>> get_cofactor(int p, int q, int n, vector<vector<int>>&key){
    vector<vector<int>>cofactor;
    int i = 0, j = 0;

    for(int row = 0; row<n; row++){
        for(int col = 0; col<n; col++){
            if(row != p && col!= q){
                if(j == 0)
                    cofactor.push_back(vector<int>());
                j++;
                cofactor[i].push_back(key[row][col]);
                if(j == n-1){
                    i++;
                    j = 0;
                }
            }
        }
    }
    return cofactor;
}

int determinant(vector<vector<int>>&key){
    int n = key.size();
    if(n == 1)
        return key[0][0];

    if(n == 2)
        return key[0][0] * key[1][1] - key[1][0] * key[0][1];

    int det = 0;
    int sign = 1;

    for(int f = 0; f<n; f++){
        vector<vector<int>>cofactor = get_cofactor(0, f, n, key);
        det += sign * key[0][f] * determinant(cofactor);

        sign *= -1;
    }

    return det;
}

bool check_gcd(int a, int b){
    while (a > 0 && b > 0){
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    if (a == 0)
        return b==1;
    return a==1;
}

bool check_invert(vector<vector<int>>&key){
    int det = determinant(key);
    if(det!= 0){
        if(check_gcd(det, NUM) == 1)
            return true;
    }
    return false;
}

void fill_matrix(vector<vector<int>>&key){
    cout<<endl<<"Enter values for the key matrix : "<<endl;
    int n = key.size();
    for(int i = 0; i <n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            cout<<endl<<"Value for "<<i<<"th row and "<<j<<"th column : ";
            cin>>key[i][j];
        }
    }

    if(!check_invert(key)){
        cout<<"Entered values make key matrix non-invertible. Try Again"<<endl;
        fill_matrix(key);
    }
}

string hill_cipher(string &plain){
    string cipher_text;
    int plain_size = plain.length();
    int key_size = choose_matrix_key(plain_size);

    vector<vector<int>>key(key_size,vector<int>(key_size));
    fill_matrix(key);

    return cipher_text;
}


int main() {
    cout << "Welcome to Crypto - systems" << endl;
    int choice = 0;
    do{
        string plain_text;
        string cipher_text;
        display_choices();

        cout << "Enter your choice of encryption : ";
        cin >> choice;

        if(choice<=6){
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
                cipher_text = vignere_cipher(plain_text);
                cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

            case 5:
                cipher_text = hill_cipher(plain_text);
                cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

            case 6:
                //cipher_text = playfair_cipher(plain_text);
                cout << endl << "Cipher text for plain text : " << plain_text << " is " << cipher_text << endl;
                break;

            default:
                cout << "*************Exiting***********" << endl;
                //  cin >> choice;
        }
    }while(choice!=7);

}