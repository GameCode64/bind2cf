//#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <array>
#include <iomanip>
#include <zlib.h>
#include <algorithm>
#include <sys/stat.h>
#include <openssl/aes.h>
#include <typeinfo>
#ifndef _WIN32
#include <unistd.h>
#endif

//Timing
#define SECONDS					1000
#define MINUTES					SECONDS * 60
#define HOURS					MINUTES * 60
#define DAYS					HOURS * 24

//Forecolors
#define E_F_black				30
#define E_F_red					31
#define E_F_green				32
#define E_F_yellow				33
#define E_F_blue				34
#define E_F_magenta				35
#define E_F_cyan				36
#define E_F_white				37

//Backcolors
#define E_B_black				40
#define E_B_red					41
#define E_B_green				42
#define E_B_yellow				43
#define E_B_blue				44
#define E_B_magenta				45
#define E_B_cyan				46

//TextType
#define E_T_reset               0  //  (everything back to normal)
#define E_T_bright              1  //  (often a brighter shade of the same colour)
#define E_T_underline           4  //
#define E_T_inverse             7  //  (swap foreground and background colours)
#define E_T_bright_off          21 //
#define E_T_underline_off       24 //
#define E_T_inverse_off         27 //


using namespace std;
#ifndef QuickHelpers_H
#define QuickHelpers_H


//building the class structure
class QuickHelpers {
public:
	QuickHelpers();
	bool Exists(const std::string& name);
	string B64E(const string& Str);
	string B64D(const string& EncStr);
	string XOR_String(string Input);
	string Encrypt(string plaintext, string key);
	string Decrypt(string ciphertext, string key);
	string CompressString(const string& str);
	string DecompressString(const string& str);
    bool FileExist(string FileName);
	string ReadFile(string Filepath);
	void WriteFile(string FilePath, string Text, bool Append);
	string StrToUpper(string String);
	string StrToLower(string String);
	string BackgroundTag(int BackColor);
	string ForegroundTag(int ForeColor);
	string TextTypeTag(int Type);
	string parseString(int input);
	string parseString(bool input);
	string parseString(float input);
	string parseString(char input);
	string parseString(double input);
	string parseString(long input);
	string parseString(size_t input);
	string parseString(string input);
	string parseString(auto input);
	string sRand(const int len);
	string exec(const char* cmd);
	void Write(std::string Output, int TextType = 0, int ForeColor = 0, int BackColor = 0);
	void WriteLine(std::string Output, int TextType = 0, int ForeColor = 0, int BackColor = 0);
	int iRand();
	int iRand(int Start, int End);
	//~QuickHelpers();
};

#endif //QuickHelpers_H