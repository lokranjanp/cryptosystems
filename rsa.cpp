//
// Created by Lokranjan P on 24/05/24.
//

#include "stdc++.h"
using namespace std;

bool is_prime(long long n){
    if(n <= 1)
        return false;

    if(n%2 == 0 || n%3 == 0)
        return false;

    if(n <= 3)
        return true;

    for(long long i = 5; i*i <= n; i+=6){
        if(n%i == 0 || n%(i+2) == 0)
            return false;
    }

    return true;
}

long long generate_primes(){
    bool got_prime = false;
    long long n = 0;

    while(!got_prime){
        n = rand()%1000 + 1000;

        if(is_prime(n))
            got_prime = true;
    }

    return n;
}

long long mod_exp(long long base, long long exp, int mod){
    long long result = 1;

    while(exp>0){
        if(exp%2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp/2;
    }

    return result;
}

long long encrypt_rsa(long long plain_text, long long e, int n){
    return mod_exp(plain_text, e, n);
}

long long decrypt_rsa(long long cipher_text, long long d, int n){
    return mod_exp(cipher_text, d, n);
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long mod_inv(long long e, long long phi){
    long long m0 = phi, t, q;
    long long x0 = 0, x1 = 1;

    if(phi == 1)
        return 0;

    while(e > 1){
        q = e/phi;
        t = phi;

        phi = e % phi;
        e = t;

        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}

void generate_keys(long long &n, long long &e, long long &d) {
    srand(time(0));

    long long p = generate_primes();
    long long q = generate_primes();

    while (p == q)
        q = generate_primes();

    n = p * q;
    long long phi = (p - 1) * (q - 1);

    do {
        e = rand() % phi + 1;
    } while (gcd(e, phi) != 1);

    d = mod_inv(e, phi);
}

string numeric_to_string(const vector<long long> &numeric_message) {
    string message;
    for (long long num : numeric_message) {
        if (num >= 1 && num <= 26)
            message += static_cast<char>(num - 1 + 'a');
        else
            throw invalid_argument("Numeric message contains invalid values.");
    }
    return message;
}

vector<long long> string_to_numeric(const string &message) {
    vector<long long> numeric_message;
    for (char c : message) {
        if (c >= 'a' && c <= 'z')
            numeric_message.push_back(c - 'a' + 1);
        else if (c >= 'A' && c <= 'Z')
            numeric_message.push_back(c - 'A' + 1);
        else
            throw invalid_argument("Unsupported character in message. Only alphabetic characters are allowed.");
    }
    return numeric_message;
}


int main() {
    long long n, e, d;
    generate_keys(n, e, d);

    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;

    string message;
    cout << "Enter the message (alphabetic characters only): ";
    cin >> message;

    vector<long long> numeric_message = string_to_numeric(message);

vector<long long> encrypted_message;
    for (long long num : numeric_message) {
        encrypted_message.push_back(encrypt_rsa(num, e, n));
    }

    cout << "Encrypted message: ";
    for (long long num : encrypted_message) {
        cout << num << " ";
    }
    cout << endl;

    vector<long long> decrypted_message;
    for (long long num : encrypted_message) {
        decrypted_message.push_back(decrypt_rsa(num, d, n));
    }

    string decrypted_text = numeric_to_string(decrypted_message);
    cout << "Decrypted message: " << decrypted_text << endl;

    return 0;
}