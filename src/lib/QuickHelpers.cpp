#include "QuickHelpers.h"
#include <iostream>

using namespace std;

QuickHelpers::QuickHelpers()
{
    // test constructor
    srand((int)time(0) * (int)time(0));
}

bool QuickHelpers::FileExist(string FileName)
{
    #ifdef _WIN32
    ifstream f(FileName.c_str());
    return f.good();
    #else
    return ( access( FileName.c_str(), F_OK ) != -1 );
    #endif
}

string QuickHelpers::ReadFile(string FilePath)
{
    string TmpLine;
    string Lines;
    ifstream FileStream(FilePath);
    if (FileStream.is_open())
    {
        while (getline(FileStream, TmpLine))
        {
            Lines += TmpLine + "\n";
        }
        FileStream.close();
    }
    else
    {
        this->WriteLine("[ Error ] : Can\'t open or find file \"" + FilePath + "\"!", E_T_reset, E_F_red, E_B_black);
    }
    return Lines;
}

string QuickHelpers::StrToUpper(string Str)
{
    transform(Str.begin(), Str.end(), Str.begin(), ::toupper);
    return Str;
}

string QuickHelpers::StrToLower(string Str)
{
    transform(Str.begin(), Str.end(), Str.begin(), ::tolower);
    return Str;
}

string QuickHelpers::BackgroundTag(int BackColor)
{
    string _BackStartTag;
    switch (BackColor)
    {
    case 40:
        _BackStartTag = "40";
        break;
    case 41:
        _BackStartTag = "41";
        break;
    case 42:
        _BackStartTag = "42";
        break;
    case 43:
        _BackStartTag = "43";
        break;
    case 44:
        _BackStartTag = "44";
        break;
    case 45:
        _BackStartTag = "45";
        break;
    case 46:
        _BackStartTag = "46";
        break;
    case 47:
        _BackStartTag = "47";
        break;
    default:
        _BackStartTag = "40";
        break;
    }
    return _BackStartTag;
}

string QuickHelpers::ForegroundTag(int ForeColor)
{
    string _FrontStartTag;
    switch (ForeColor)
    {
    case 30:
        _FrontStartTag = ";30m";
        break;
    case 31:
        _FrontStartTag = ";31m";
        break;
    case 32:
        _FrontStartTag = ";32m";
        break;
    case 33:
        _FrontStartTag = ";33m";
        break;
    case 34:
        _FrontStartTag = ";34m";
        break;
    case 35:
        _FrontStartTag = ";35m";
        break;
    case 36:
        _FrontStartTag = ";36m";
        break;
    case 37:
        _FrontStartTag = ";37m";
        break;
    default:
        _FrontStartTag = ";37m";
        break;
    }
    return _FrontStartTag;
}

string QuickHelpers::TextTypeTag(int Type)
{
    string _TypeTag;
    switch (Type)
    {
    case 0:
        _TypeTag = "0;"; // reset
        break;
    case 1:
        _TypeTag = "1;"; // bold/bright
        break;
    case 4:
        _TypeTag = "4;"; // underlined
        break;
    case 7:
        _TypeTag = "7;"; // inverse
        break;
    case 21:
        _TypeTag = "21;"; // bold off
        break;
    case 24:
        _TypeTag = "24;"; // underline off
        break;
    case 27:
        _TypeTag = "27;"; // inverse off
        break;
    default:
        _TypeTag = "0;"; // reset
        break;
    }
    return _TypeTag;
}

string QuickHelpers::parseString(int input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(bool input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(float input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(char input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(double input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(long input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(size_t input)
{
    return std::to_string(input);
}

string QuickHelpers::parseString(string input)
{
    return (input);
}

string QuickHelpers::parseString(auto input)
{
    return std::to_string(input);
}

string QuickHelpers::exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
#ifdef _WIN32
    std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
#else // _WIN32
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
#endif
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

string QuickHelpers::sRand(const int len)
{

    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}

void QuickHelpers::Write(std::string Output, int TextType, int ForeColor, int BackColor)
{
    string _Output;
    _Output = "\033[" + TextTypeTag(TextType) + BackgroundTag(BackColor) + ForegroundTag(ForeColor) + Output + "\033[0m";
    cout << _Output;
}

void QuickHelpers::WriteLine(std::string Output, int TextType, int ForeColor, int BackColor)
{
    string _Output;
    _Output = "\033[" + TextTypeTag(TextType) + BackgroundTag(BackColor) + ForegroundTag(ForeColor) + Output + "\033[0m";
    cout << _Output << endl;
}

int QuickHelpers::iRand()
{
    return rand() % 1000;
}

int QuickHelpers::iRand(int Start, int End)
{
    return rand() % (End - Start) + Start;
}

/*QuickHelpers::~QuickHelpers()
{
    //test deconstructor
}
*/