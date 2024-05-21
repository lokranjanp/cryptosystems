#include<bits/stdc++.h>
using namespace std;

int choose_key()
{
    char choice;
    cout<<"Do you want a random key ?(Y/N)"<<endl;
    cin>>choice;
    if(choice == 'y' || choice == 'Y')
    {
        return rand()%26;
    }
    else
    {
        int input = 0;
        cout << "Enter key of choice : ";
        cin >> input;
        return input;
    }
}

void display_choices()
{
    cout<<endl;
    cout<<"1. Ceaser Cipher\n2. Affine Cipher\n3. Auto Key Cipher\n4. Vignere Cipher\n5. Hill Cipher\n"<<endl;
}

string ceaser_cipher(string &plain)
{
    int key = choose_key();
    cout<<"Key is : "<<key<<endl;
    if(key == -1)
    {
        return "ERROR";
    }

    string res;
    for(auto c : plain)
    {
        if(isalpha(c))
        {
            char offset = isupper(c) ? 'A' : 'a';
            res += (c - offset + key)%26 + offset;
        }
        else
            res += c;
    }

    return res;
}

int main()
{
    cout<<"Welcome to Crypto - systems"<<endl;
    cout<<"Enter plain text : "<<" ";
    string plain_text;
    string cipher_text;
    cin>>plain_text;

    cout<<endl;

    int choice = 0;
    cout<<"Enter your choice of encryption : ";
    display_choices();
    cin>>choice;
    switch(choice) {
        case 1:
            cipher_text = ceaser_cipher(plain_text);
            cout<<endl<<"Cipher text for plain text : "<<plain_text<<" is "<<cipher_text<<endl;
            break;

        case 2:
            //cipher_text = affine_cipher(plain_text);
            cout<<endl<<"Cipher text for plain text : "<<plain_text<<" is "<<cipher_text<<endl;
            break;

        case 3:
            //cipher_text = auto_key_cipher(plain_text);
            cout<<endl<<"Cipher text for plain text : "<<plain_text<<" is "<<cipher_text<<endl;
            break;

        case 4:
            //cipher_text = vignere_cipher(plain_text);
            cout<<endl<<"Cipher text for plain text : "<<plain_text<<" is "<<cipher_text<<endl;
            break;

        case 5:
            //cipher_text = playfair_cipher(plain_text);
            cout<<endl<<"Cipher text for plain text : "<<plain_text<<" is "<<cipher_text<<endl;
            break;

        default:
            cout<<"Enter a valid choice!!"<<endl;
            cin>>choice;

    }

}