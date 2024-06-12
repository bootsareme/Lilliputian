#include "tokenizer.h"

int main(int argc, char* argv[]) 
{
	if (argc <= 2)
	{
		std::ifstream src(argv[1]);
		Tokenizer::parse(src);
	}
}