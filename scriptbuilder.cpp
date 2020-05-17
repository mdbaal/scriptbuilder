#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <locale>
#include <vector>


void makeFiles(std::string filename,
				 std::string extendsFrom,
				  std::string filenameUppper,
				   std::string filenameUpperAll,
				    std::string extendInclude,
				     std::vector<std::string> includeList,
				     std::vector<std::string> functions,
				     std::vector<std::string> types,
				     int publics ) {
	//source file
	//make the file
	std::ofstream source;
	source.open(filename + ".cpp");
	source << "#include \"" << filename << ".h\"\n\n" << filenameUppper << "::" << filenameUppper << "(){\n\n}\n\n" << filenameUppper << "::~" << filenameUppper << "(){\n\n\n}\n";
	//add functions
	int i = 0;
	for(i < functions.size();i++;){
		source << types[i] << " " << filenameUppper << "::" << functions[i] << "{\n\n}\n\n";
	}

	source.close();

	//header file
	//make the file
	std::ofstream header;
	header.open(filename + ".h");
	//add ifndef
	header << "#ifndef " << filenameUpperAll << "_H\n" << "#define " << filenameUpperAll << "_H\n\n";
	//add all includes

	if (extendsFrom != "") header << "#include <" << extendInclude << ">\n";

	for (int j = 0; j < includeList.size(); j++) {
		std::string temp = includeList[j];
		if (temp[temp.size() - 1] == 'h') {
			header << "#include \"" << includeList[j] << "\"" << std::endl;
		}
		else {
			header << "#include <" << includeList[j] << ">" << std::endl;
		}
	}
	header << std::endl;

	if (extendsFrom == "") { header << "class " << filenameUppper << "{\n"; }
	else { header << "class " << filenameUppper << " : public " << extendsFrom << "{\n"; }
	//public functions
	header << "public:\n	" << filenameUppper << "();\n	" << "virtual ~" << filenameUppper << "();\n" ;
	i = 0;

	for (i < publics; i++;) {
		header << "   " << types[i] << " " << functions[i] << ";" << std::endl;
	}

	//private functions
	header << "private:\n";

	for (i < functions.size() + publics; i++;) {
		header << "   " << types[i] << " " << functions[i] << ";" << std::endl;
	}
	header  << "}; \n\n#endif //" << filenameUpperAll << "_H";
	header.close();

	std::cout << "done" << std::endl;
}

void getInput() {
	std::string filename = "";

	std::string extendsFrom = "";

	std::string extendsFromInclude = "";

	std::string s = "";

	std::string filenameUpper = "";

	std::string filenameUpperAll = "";

	std::vector<std::string> includeList = std::vector<std::string>();

	std::vector<std::string> functions = std::vector<std::string>();
	std::vector<std::string> types = std::vector<std::string>();

	int publics = 0;

	std::locale loc;
	//input
	//file name
	std::cout << "file name:" << std::endl;
	std::cin >> filename;
	//extend
	std::cout << "extends: (n if not)" << std::endl;
	std::cin >> extendsFrom;
	if (extendsFrom == "n") {
		extendsFrom = "";
	}
	else {
		std::cout << "extend include:" << std::endl;
		std::cin >> extendsFromInclude;
	}
	s = "";
	//include
	std::string include = "";
	std::cout << "includes:  (n if not or there are no more includes)" << std::endl;
	std::cin >> include;
	while (include != "n") {
		includeList.push_back(include);
		std::cin >> include;
	}

	//functions
	std::string func = "";
	std::string rtn = "";

	std::cout << "Public Functions: example - myFunc(std::string s)  (n if not or there are no more public functions" << std::endl;
	std::cout << "Give return type, press enter, then enter fucntion and press enter again" << std::endl;
	std::cin >> rtn;
	std::cin  >> func;
	while(func != "n" && rtn != "n"){
		functions.push_back(func);
		types.push_back(rtn);
		std::cin >> rtn;
		if(rtn == "n") break;
		std::cin >> func;

		publics ++;
	}

	func = "";
	rtn = "";

	std::cout << "Private Functions: example - myFunc(std::string s)  (n if not or there are no more private functions" << std::endl;
	std::cout << "Give return type, press enter, then enter function and press enter again" << std::endl;
	std::cin >> rtn;
	std::cin  >> func;
	while(func != "n" && rtn != "n"){
		functions.push_back(func);
		types.push_back(rtn);
		std::cin >> rtn;
		if(rtn == "n") break;
		std::cin >> func;
	}

	//first letter capitalized
	filenameUpper = std::toupper(filename[0], loc);
	for (int i = 1; i < filename.size(); i++) {
		filenameUpper += filename[i];
	}
	//whole string capitalized
	for (int i = 0; i < filename.size(); i++) {
		filenameUpperAll += std::toupper(filename[i], loc);
	}
	//first letter capitalized
	std::string tempExtend = "";
	if (extendsFrom != "") {

		tempExtend = std::toupper(extendsFrom[0], loc);
		for (int i = 1; i < extendsFrom.size(); i++) {
			tempExtend += extendsFrom[i];
		}
	}

	//create the files
	makeFiles(filename, tempExtend, filenameUpper, filenameUpperAll, extendsFromInclude, includeList,functions,types,publics);
}



int main(void) {
	std::string s = "";
	do {
		getInput();
		std::cout << "more? (y/n)" << std::endl;

		std::cin >> s;
	} while (s == "y");

	std::cout << "goodbye" << std::endl;

	return 0;
}
