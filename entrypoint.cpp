#include "tokenizer.h"

int main(int argc, char* argv[]) 
{
	if (argc < 2)
		return -1;

	if (std::string(argv[1]) == "-r") 
	{
		std::ifstream src(argv[2]);
		Tokenizer::parse(src);
	}
	else if (std::string(argv[1]) == "-h") 
	{
		std::cout << "Lilliputain v1.2\nFor more information, please go to: https://github.com/bootsareme/Lilliputain\n\n";
		std::cout << "| Opcode | Description |\n";
		std::cout << "| SET X = Y | Creates a new variable called X and assigns it to Y. |\n";
		std::cout << "| MOV X -> Y | Moves the value of X into Y. |\n";
		std::cout << "| ARITH X + Y | Performs arithmetic on X and Y and saves the results to Y. (+, -, * /) |\n";
		std::cout << "| STR X = Y, Z | Creates a STR X and joins the ASCII values of Y and Z. |\n";
		std::cout << "| PRINT X -> Y | Prints STR X into filename Y. |\n";
		std::cout << "| CHECK 123 X=Y | If condition is met, run the next 123 lines and return back to main thread. Otherwise skip the next 123 lines. |\n";
		std::cout << "| JMP 123/X | Jumps to line number 123/(value @ X). CAUTION: If left unhandled, it may cause infinite loops. |\n";
		std::cout << "| DEL X | Deletes the variable X from scope entirely. |\n";
		std::cout << "| INT 1234 | Pauses the thread for 1234 ms (milliseconds). |";
	}
}