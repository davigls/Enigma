#include <iostream>
#include "Enigma.h"

int main() {
	Enigma rot(
		ROTOR_CONTACTS_IV, ROTOR_WINDOW_IV  , 'M', 'F',
		ROTOR_CONTACTS_II, ROTOR_WINDOW_II  , 'F', 'V',
		ROTOR_CONTACTS_III, ROTOR_WINDOW_III, 'J', 'K',
		REFLECTOR_B,"GKXFODAIHJBLMNEPQRSTUYWCVZ"
	);
	for (int i = 0; i < 2000; i++) {
		std::cout << rot.type("AAAAAAAAAA") ;
	}
	//std::cout << rot.type("AAAAA");
	std::cout << std::endl;
	return 0;
}