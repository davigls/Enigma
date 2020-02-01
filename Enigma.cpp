#define _CRT_SECURE_NO_WARNINGS 1
#define DEBUG 0
#include "Enigma.h"
#if DEBUG
	#include <iostream>
#endif // DEBUG



char Rotor::Position()
{
	return (26 + position + offset ) % 26;
}

char Rotor::AcPosition()
{
	return position+'A';
}

bool Rotor::canAdvance()
{
	bool ret = false;
	for (int i = 0; window[i] != 0; i++) {
		if (position + 'A' == window[i]) {
			ret = true;
		}
	}
	return ret;
}

bool Rotor::hasAdvanced()
{
	bool ret = false;
	for (int i = 0; window[i] != 0; i++) {
		if ((26+position-1)%26 + 'A' == window[i]) {
			ret = true;
		}
	}
	return ret;
}

bool Rotor::Rotate()
{
	return rotate;
}

void Rotor::setRotate()
{
	rotate = true;
}

Rotor::Rotor(Rotor* _adv)
{
	adv = _adv;
	contacts = new char[27];
	inverse = new char[27];
	window = new char[strlen(ROTOR_WINDOW_I)+1];
	strcpy(contacts,ROTOR_CONTACTS_I);
	strcpy(window, ROTOR_WINDOW_I);

	for (int i = 0; i < 26; i++) {
		inverse[contacts[i] - 'A'] = i + 'A';
	}
	inverse[26] = 0;
	offset = 0;
	position = 0;
	rotate = false;
}

Rotor::~Rotor()
{
	delete window;
	delete contacts;
	delete inverse;
}

Rotor::Rotor(Rotor* _adv, const char* _contacts, const char* _window, char _position, char _offset)
{
	adv = _adv;
	contacts = new char[27];
	inverse = new char[27];
	window = new char[strlen(_window)+1];
	strcpy(contacts, _contacts);
	strcpy(window, _window);
	for (int i = 0; i < 26; i++) {
		inverse[contacts[i] - 'A'] = i + 'A';
	}
	inverse[26] = 0;
	offset = _offset;
	position = (26 + _position - offset ) % 26;
	rotate = false;
}

char Rotor::get(char car,bool dir)
{
	char ret;
	char* alpha;
	
	if (dir) {
		alpha = contacts;
	}
	else {
		alpha = inverse;
	}

	ret = (position + car - 'A') % 26;
		
	return ((26+alpha[ret] -'A' - position) % 26)+'A';

}

void Rotor::advance()
{
	char pos = Position();
	position++;
	
	if (adv != nullptr) {
		for (int i = 0; window[i] != 0; i++) {
			if (pos +'A' == window[i]) {
				adv->advance();
			}
		}
	}
	rotate = false;
	position = position % 26;
	
}

Enigma::Enigma()
{
	rotors[0] = new Rotor(nullptr  , ROTOR_CONTACTS_IV , ROTOR_WINDOW_IV , 'M' - 'A', 'F' - 'A');
	rotors[1] = new Rotor(rotors[0], ROTOR_CONTACTS_II , ROTOR_WINDOW_II , 'F' - 'A', 'V' - 'A');
	rotors[2] = new Rotor(rotors[1], ROTOR_CONTACTS_III, ROTOR_WINDOW_III, 'J' - 'A', 'K' - 'A');
	strcpy(reflector, REFLECTOR_B);
	strcpy(plugboard, "GKXFODAIHJBLMNEPQRSTUYWCVZ");
}

Enigma::Enigma(const char* r_contacts, const char* r_window, char r_position, char r_offset, const char* m_contacts, const char* m_window, char m_position, char m_offset, const char* l_contacts, const char* l_window, char l_position, char l_offset, const char refl[27], const char plug[27])
{
	rotors[0] = new Rotor(nullptr  , l_contacts, l_window, l_position - 'A', l_offset - 'A');
	rotors[1] = new Rotor(rotors[0], m_contacts, m_window, r_position - 'A', m_offset - 'A');
	rotors[2] = new Rotor(rotors[1], r_contacts, r_window, r_position - 'A', r_offset - 'A');
	strcpy(reflector, refl);
	strcpy(plugboard, plug);
}

Enigma::~Enigma()
{
	for (int i = 0; i < 3; i++) delete rotors[i];
}

char Enigma::get(char car)
{
	char a=car;
	
	if (car >= 'a' && car <= 'z') car -= 32;

	if (car >= 'A' && car <= 'A') {
		a = car;
		
		rotors[2]->advance();
#if DEBUG
		//std::cout << "Rotor 3 has:" << (rotors[2]->hasAdvanced() ? "true" : "false")<<std::endl;
		//std::cout << "Rotor 2 can:" << (rotors[1]->canAdvance() ? "true" : "false") << std::endl;
#endif //DEBUG
		if(rotors[2]->hasAdvanced() && rotors[1]->canAdvance()){
			rotors[1]->setRotate();
		}
		
#if DEBUG
		char b;
		std::cout << "Posizione rotori: " << (char)(rotors[0]->Position() + 'A') << (char)(rotors[1]->Position() + 'A') << (char)(rotors[2]->Position() + 'A') << std::endl;
		std::cout << "Posizione vera  : " << (char)(rotors[0]->AcPosition()) << (char)(rotors[1]->AcPosition() ) << (char)(rotors[2]->AcPosition() ) << std::endl;
		b = a;
		a = plugboard[b - 'A'];
		std::cout << "Plug " << b << " -> " << a << std::endl;
		b = rotors[2]->get(a, true);
		std::cout << a << " -> " << b << std::endl;
		a = rotors[1]->get(b, true);
		std::cout << b << " -> " << a << std::endl;
		b = rotors[0]->get(a, true);
		std::cout << a << " -> " << b << std::endl;

		a = b;
		b = reflector[a - 'A'];
		std::cout << "Refl " << a << " -> " << b << std::endl;

		a = rotors[0]->get(b, false);
		std::cout << b << " -> " << a << std::endl;
		b = rotors[1]->get(a, false);
		std::cout << a << " -> " << b << std::endl;
		a = rotors[2]->get(b, false);
		std::cout << b << " -> " << a << std::endl;
		b = plugboard[a - 'A'];
		std::cout << "Plug " << a << " -> " << b << std::endl;
		a = b;
#else
		a = plugboard[a - 'A'];
		
		a = rotors[2]->get(a, true);
		a = rotors[1]->get(a, true);
		a = rotors[0]->get(a, true);

		a = reflector[a - 'A'];

		a = rotors[0]->get(a, false);
		a = rotors[1]->get(a, false);
		a = rotors[2]->get(a, false);

		a = plugboard[a - 'A'];
#endif // DEBUG
		if (rotors[1]->Rotate())
			rotors[1]->advance();
		
	}
	
	return a;
}

std::string Enigma::type(std::string s)
{
	std::string str="";
	for (int i = 0; i < s.length(); i++) {
		str += get(s[i]);
	}
	
	return str;
}
