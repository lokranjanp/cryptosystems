#ifndef CRYPTSYSTEMS_ALGORITHMS_H
#define CRYPTSYSTEMS_ALGORITHMS_H

#include "stdc++.h"
using namespace std;

void display_choices();
string ceaser_cipher(string &plain_text);
string auto_key_cipher(string &plain);
string affine_cipher(string &plain);
string hill_cipher(string &plain);
string vignere_cipher(string &plain);

#endif //CRYPTSYSTEMS_ALGORITHMS_H
// Created by Lokranjan P on 25/05/24.