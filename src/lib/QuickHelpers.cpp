#include "QuickHelpers.h"
using namespace std;


QuickHelpers::QuickHelpers()
{
	//test constructor
	srand((int)time(0));
}

bool QuickHelpers::Exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

//Base 64 Encode
string QuickHelpers::B64E(const string& Str) {
	const char* BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string Out;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	for (unsigned char c : Str) {
		char_array_3[i++] = c;
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;
			for (i = 0; i < 4; i++) {
				Out += BASE64_CHARS[char_array_4[i]];
			}
			i = 0;
		}
	}
	if (i) {
		for (j = i; j < 3; j++) {
			char_array_3[j] = '\0';
		}
		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;
		for (j = 0; j < i + 1; j++) {
			Out += BASE64_CHARS[char_array_4[j]];
		}
		while ((i++ < 3)) {
			Out += '=';
		}
	}

	return Out;
}

//Base 64 Decode
string QuickHelpers::B64D(const string& EncStr) {
	const char* BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string Out;
	int i = 0, j = 0;
	unsigned char char_array_4[4], char_array_3[3];
	for (const auto& c : EncStr) {
		if (c == '=')
			break;
		char_array_4[i++] = c;
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				char_array_4[i] = strchr(BASE64_CHARS, char_array_4[i]) - BASE64_CHARS;
			}
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
			for (i = 0; i < 3; i++) {
				Out += char_array_3[i];
			}
			i = 0;
		}
	}
	if (i) {
		for (j = i; j < 4; j++) {
			char_array_4[j] = 0;
		}
		for (j = 0; j < 4; j++) {
			char_array_4[j] = strchr(BASE64_CHARS, char_array_4[j]) - BASE64_CHARS;
		}
		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
		for (j = 0; j < i - 1; j++) {
			Out += char_array_3[j];
		}
	}
	return Out;
}


string QuickHelpers::XOR_String(string a) {
	string c = "";
	int b = a.length();
	for (int i = 0; i < b; ++i) {
		c += char(int(a[i]) ^ ((205 + ((b + i) + 2)) % 205));
	}
	return c;
}


string QuickHelpers::Encrypt(string plaintext, string key) {
	// Convert key to AES key format
	unsigned char aes_key[16];
	memset(aes_key, 0, 16);
	for (int i = 0; i < min((int)key.length(), 16); i++) {
		aes_key[i] = key[i];
	}

	// Create AES context
	AES_KEY aes;
	AES_set_encrypt_key(aes_key, 128, &aes);

	// Encrypt plaintext using AES
	string ciphertext = "";
	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0, AES_BLOCK_SIZE);
	int len = plaintext.length();
	int remaining = len % AES_BLOCK_SIZE;
	if (remaining != 0) {
		plaintext += string(AES_BLOCK_SIZE - remaining, ' ');
	}
	for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
		unsigned char indata[AES_BLOCK_SIZE];
		memset(indata, 0, AES_BLOCK_SIZE);
		for (int j = 0; j < AES_BLOCK_SIZE; j++) {
			if (i + j < len) {
				indata[j] = plaintext[i + j];
			}
		}
		unsigned char outdata[AES_BLOCK_SIZE];
		memset(outdata, 0, AES_BLOCK_SIZE);
		AES_cbc_encrypt(indata, outdata, AES_BLOCK_SIZE, &aes, iv, AES_ENCRYPT);
		ciphertext += string((char*)outdata, AES_BLOCK_SIZE);
	}

	return ciphertext;
}

string QuickHelpers::Decrypt(string ciphertext, string key) {
	// Convert key to AES key format
	unsigned char aes_key[16];
	memset(aes_key, 0, 16);
	for (int i = 0; i < min((int)key.length(), 16); i++) {
		aes_key[i] = key[i];
	}

	// Create AES context
	AES_KEY aes;
	AES_set_decrypt_key(aes_key, 128, &aes);

	// Decrypt ciphertext using AES
	string plaintext = "";
	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0, AES_BLOCK_SIZE);
	int len = ciphertext.length();
	for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
		unsigned char indata[AES_BLOCK_SIZE];
		memset(indata, 0, AES_BLOCK_SIZE);
		for (int j = 0; j < AES_BLOCK_SIZE; j++) {
			if (i + j < len) {
				indata[j] = ciphertext[i + j];
			}
		}
		unsigned char outdata[AES_BLOCK_SIZE];
		memset(outdata, 0, AES_BLOCK_SIZE);
		AES_cbc_encrypt(indata, outdata, AES_BLOCK_SIZE, &aes, iv, AES_DECRYPT);
		plaintext += string((char*)outdata, AES_BLOCK_SIZE);
	}

	// Remove padding from plaintext
	int padlen = plaintext[plaintext.length() - 1];
	if (padlen < 1 || padlen > AES_BLOCK_SIZE) {
		padlen = 0;
	}
	plaintext = plaintext.substr(0, plaintext.length() - padlen);

	return plaintext;
}

string QuickHelpers::CompressString(const string& Str) {
	stringstream compressed;
	z_stream deflate_stream;
	deflate_stream.zalloc = Z_NULL;
	deflate_stream.zfree = Z_NULL;
	deflate_stream.opaque = Z_NULL;
	deflate_stream.avail_in = Str.size();
	deflate_stream.next_in = (Bytef*)(Str.c_str());
	deflate_stream.avail_out = 32768;
	deflate_stream.next_out = (Bytef*)(&compressed.str()[0]);
	if (deflateInit(&deflate_stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
		return "";
	}
	int ret;
	char outbuffer[32768];
	do {
		deflate_stream.avail_out = 32768;
		deflate_stream.next_out = (Bytef*)(outbuffer);
		ret = deflate(&deflate_stream, Z_FINISH);
		compressed.write(outbuffer, 32768 - deflate_stream.avail_out);
	} while (deflate_stream.avail_out == 0);
	deflateEnd(&deflate_stream);
	return compressed.str();
}

string QuickHelpers::DecompressString(const string& Str) {
	stringstream decompressed;
	z_stream inflate_stream;
	inflate_stream.zalloc = Z_NULL;
	inflate_stream.zfree = Z_NULL;
	inflate_stream.opaque = Z_NULL;
	inflate_stream.avail_in = Str.size();
	inflate_stream.next_in = (Bytef*)(Str.c_str());
	inflate_stream.avail_out = 32768;
	inflate_stream.next_out = (Bytef*)(&decompressed.str()[0]);
	if (inflateInit(&inflate_stream) != Z_OK) {
		return "";
	}
	int ret;
	char outbuffer[32768];
	do {
		inflate_stream.avail_out = 32768;
		inflate_stream.next_out = (Bytef*)(outbuffer);
		ret = inflate(&inflate_stream, 0);
		if (ret != Z_OK && ret != Z_STREAM_END) {
			inflateEnd(&inflate_stream);
			return "";
		}
		decompressed.write(outbuffer, 32768 - inflate_stream.avail_out);
	} while (inflate_stream.avail_out == 0);
	inflateEnd(&inflate_stream);
	return decompressed.str();
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
		while ( getline(FileStream, TmpLine) )
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

void QuickHelpers::WriteFile(string FilePath, string Text, bool Append = false)
{
	ofstream Output(FilePath, Append ? ios::app : ios::out);
	Output << Text << endl;
	Output.close();
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

string QuickHelpers::exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
#ifdef _WIN32
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
#else// _WIN32
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
#endif
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
			result += buffer.data();
	}
	return result;
}

string QuickHelpers::sRand(const int len) {

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

int QuickHelpers::iRand() {
	return rand() % 1000;
}

int QuickHelpers::iRand(int Start, int End) {
	return rand() % (End - Start) + Start;
}





/*QuickHelpers::~QuickHelpers()
{
	//test deconstructor
}
*/