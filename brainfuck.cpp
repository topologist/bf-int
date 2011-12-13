#include "brainfuck.h"
#include <memory>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
		std::cout << "Usage: " << argv[0] << " <input file name>\n";
		return 0;
	}

	FILE *fh;
	fopen_s(&fh, argv[1], "r");
	
	if (fh != NULL)
	{
		memset(bf, 0, ARRAY_SIZE);
		doBF(fh);
		fclose(fh);
		return 0;
	}

	std::cout << "File '" << argv[1] << "' doesn't exist.\n";
	return 0;
}

void doBF(FILE *fh)
{
	while (true)
	{
		c = fgetc(fh);
		if (interpretBF(fh, c) == 1) return;
		// std::cout << "\t\t(" << ftell(fh) << ")\n";
	}
}

int interpretBF(FILE *fh, char c)
{
	std::cout << c;
	switch (c)
	{
	case EOF:
		return 1;
	case '>':
		if (p + 1 - bf < ARRAY_SIZE)
			++p;
		// std::cout << "> [" << (long)(p-bf) << "," << static_cast<int>(*p) << "]\n";
		break;
	case '<':
		if (p > bf)
			--p;
		// std::cout << "< [" << (long)(p-bf) << "," << static_cast<int>(*p) << "]\n";
		break;
	case '+':
		++(*p);
		// std::cout << "+ [" << static_cast<int>(*p) << "]\n";
		break;
	case '-':
		--(*p);
		// std::cout << "- [" << static_cast<int>(*p) << "]\n";
		break;
	case '.':
		std::cout << *p;
		break;
	case ',':
		std::cin.get(*p);
		break;
	case '[':
		pos[nestl++] = ftell(fh);
		break;
	case ']':
		if (*p != 0)
			fseek(fh, pos[nestl-1], SEEK_SET);
		else
			nestl--;
		break;
	//default:
		// std::cout << "error: If you tried a nested loop, those don't work yet. (" << c << ")\n";
	}
	return 0;
}