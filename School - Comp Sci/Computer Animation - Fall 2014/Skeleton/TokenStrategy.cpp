#include "TokenStrategy.h"

const char TokenStrategy::number_regex[] = R"(-?\d+(\.\d+)?)";
const char TokenStrategy::var_name_regex[] = R"([a-zA-Z_][a-zA -Z_\d]*)";
const char balljointTypeName[] = "balljoint";

TokenStrategy::TokenStrategy(){
	
}

TokenStrategy::~TokenStrategy(){

}