#ifndef CRYPTSYSTEMS_RSA_H
#define CRYPTSYSTEMS_RSA_H

#include "stdc++.h"
using namespace std;

void generate_keys(long long &n, long long &e, long long &d);
vector<long long> string_to_numeric(const string &message);
long long encrypt_rsa(long long plain_text, long long e, int n);
long long decrypt_rsa(long long cipher_text, long long d, int n);
string numeric_to_string(const vector<long long> &numeric_message);
#endif

//CRYPTSYSTEMS_RSA_H
// Created by Lokranjan P on 25/05/24.