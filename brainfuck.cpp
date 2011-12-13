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
		char n = *p;
		switch(c)
		{
		case EOF:
			return;
		case '[':
			pos = ftell(fh);
			while (n != 0)
			{
				c = fgetc(fh);
				if (c != ']')
				{
					interpretBF(c);
				} else {
					n = *p;
					if (n == 0) {
						break;
					} else {
						fseek(fh, pos, SEEK_SET);
					}
				}
			}
		default:
			interpretBF(c);
			// std::cout << "\t\t(" << ftell(fh) << ")\n";
		}
	}
}

void interpretBF(char c)
{
	switch (c)
	{
	case EOF:
		return;
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
	case '\n': case '\r': case ']':
		return;
	default:
		std::cout << "error: If you tried a nested loop, those don't work yet. (" << c << ")\n";
	}
}