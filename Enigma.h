#pragma once
#include <string.h>
#include <string>

/*
//                                    ABCDEFGHIJKLMNOPQRSTUVWXYZ
const char ROTOR_CONTACTS_I   [27] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char ROTOR_CONTACTS_II  [27] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char ROTOR_CONTACTS_III [27] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
const char ROTOR_CONTACTS_IV  [27] = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
const char ROTOR_CONTACTS_V   [27] = "VZBRGITYUPSDNHLXAWMJQOFECK";
const char ROTOR_CONTACTS_VI  [27] = "JPGVOUMFYQBENHZRDKASXLICTW";
const char ROTOR_CONTACTS_VII [27] = "NZJHGRCXMYSWBOUFAIVLPEKQDT";
const char ROTOR_CONTACTS_VIII[27] = "FKQHTLXOCBJSPDZRAMEWNIUYGV";

const char ROTOR_WINDOW_I   [] = "Q";
const char ROTOR_WINDOW_II  [] = "E";
const char ROTOR_WINDOW_III [] = "V";
const char ROTOR_WINDOW_IV  [] = "J";
const char ROTOR_WINDOW_V   [] = "Z";
const char ROTOR_WINDOW_VI  [] = "ZM";
const char ROTOR_WINDOW_VII [] = "ZM";
const char ROTOR_WINDOW_VIII[] = "ZM";

const char REFLECTOR_B[27] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
const char REFLECTOR_C[27] = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
*/

#define ROTOR_CONTACTS_I    "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define	ROTOR_CONTACTS_II   "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define	ROTOR_CONTACTS_III  "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define	ROTOR_CONTACTS_IV   "ESOVPZJAYQUIRHXLNFTGKDCMWB"
#define	ROTOR_CONTACTS_V    "VZBRGITYUPSDNHLXAWMJQOFECK"
#define	ROTOR_CONTACTS_VI   "JPGVOUMFYQBENHZRDKASXLICTW"
#define	ROTOR_CONTACTS_VII  "NZJHGRCXMYSWBOUFAIVLPEKQDT"
#define	ROTOR_CONTACTS_VIII "FKQHTLXOCBJSPDZRAMEWNIUYGV"

#define ROTOR_WINDOW_I    "Q"
#define	ROTOR_WINDOW_II   "E"
#define	ROTOR_WINDOW_III  "V"
#define	ROTOR_WINDOW_IV   "J"
#define	ROTOR_WINDOW_V    "Z"
#define	ROTOR_WINDOW_VI   "ZM"
#define	ROTOR_WINDOW_VII  "ZM"
#define	ROTOR_WINDOW_VIII "ZM"

#define REFLECTOR_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define	REFLECTOR_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"


class Rotor {
private:
	Rotor* adv;
	char* contacts;
	char* inverse;
	char* window;
	char offset;
	char position;
	bool rotate;
public:
	char Position();
	char AcPosition();
	bool canAdvance();
	bool hasAdvanced();
	bool Rotate();
	void setRotate();
	Rotor(Rotor* _adv=nullptr);
	~Rotor();
	Rotor(Rotor* _adv, const char* _contacts, const char* _window, char _position, char _offset );
	char get(char car,bool dir);
	void advance();
};

class Enigma {
private:
	Rotor *rotors[3];
	char reflector[27];
	char plugboard[27];
public:
	Enigma();
	Enigma( const char* r_contacts, const char* r_window, char r_position, char r_offset, 
			const char* m_contacts, const char* m_window, char m_position, char m_offset,
			const char* l_contacts, const char* l_window, char l_position, char l_offset, 
			const char refl[27], const char plug[27]);
	~Enigma();
	char get(char car);
	std::string type(std::string s);
};