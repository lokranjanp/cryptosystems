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

int choose_matrix_key(){
    int mat_size;
    cout<<"Enter the size for the square matrix : ";
    cin>>mat_size;

    return mat_size;
}

void display_choices(){
    cout<<endl;
    cout<<"1. Ceaser Cipher\n2. Affine Cipher\n3. Auto Key Cipher\n4. Vignere Cipher\n5. Hill Cipher\n6. Playfair Cipher\n7. RSA"<<endl;
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

    for(int row = 0; row<n; row++){
        if(row == p)
            continue;

        vector<int>cofactor_row;
        for(int col = 0; col<n; col++){
            if(col == q)
                continue;

            cofactor_row.push_back(key[row][col]);
        }
        cofactor.push_back(cofactor_row);
    }

    return cofactor;
}

int determinant(vector<vector<int>>&key){
    int n = key.size();
    int det = 0;
    int sign = 1;

    if(n == 1)
        return det = key[0][0];

    if(n == 2)
        return det = (key[0][0] * key[1][1] - key[1][0] * key[0][1]);

    for(int f = 0; f<n; f++){
        vector<vector<int>>cofactor = get_cofactor(0, f, n, key);
        det += sign * key[0][f] * determinant(cofactor);

        sign *= -1;
    }

    return det;
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}


bool check_invert(vector<vector<int>>&key){
    int det = determinant(key);
    if(det!= 0){
        if(gcd(det, NUM) == 1)
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
    int key_size = choose_matrix_key();

    while(plain.length()%key_size!=0)
        plain+='X';

    vector<vector<int>>key(key_size,vector<int>(key_size));
    fill_matrix(key);

    for(int i = 0; i<plain.size(); i+=key_size) {
        vector<int> plain_vec(key_size);
        vector<int> offset(key_size);

        for (int j = 0; j < key_size; j++) {
            char c = plain[i + j];
            if (isupper(c)) {
                plain_vec[j] = c - 'A';
                offset[j] = 'A';
            } else if (islower(c)) {
                plain_vec[j] = c - 'a';
                offset[j] = 'a';
            } else {
                plain_vec[j] = c;
                offset[j] = 0;
            }
        }

        for (int j = 0; j < key_size; j++) {
            int sum = 0;
            for (int k = 0; k < key_size; k++) {
                sum += key[j][k] * plain_vec[k];
            }
            sum %= 26;
            cipher_text += sum + offset[j];
        }
    }
    return cipher_text;
}

