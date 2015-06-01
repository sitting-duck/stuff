#include "Attribute.h"

Attribute::Attribute() : numTrue(0), numFalse(0), numTrueTrue(0), numFalseFalse(0), numTrueFalse(0), numFalseTrue(0), name(""){}

Attribute::Attribute(string _name): numTrue(0), numFalse(0), numTrueTrue(0), numFalseFalse(0), numTrueFalse(0), numFalseTrue(0){
	name = _name;
}