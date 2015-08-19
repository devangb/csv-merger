#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>

int count_comma(std::string s) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
    if (s[i] == ',') count++;

  return count;
}

void rowmerge(int num_files, std::vector<std::string> infilename, std::string outfilename){
	std::vector< std::vector<std::string> > data(num_files);
	std::vector<std::string> lastline(num_files);
	std::vector<std::string> emptyline(num_files);
	std::vector<int> rows_count(num_files);
	std::vector<int> num_values;
	int repeat;
	int num_rows=0, curr_rows, max_row_filenum;
	//TO_DO max_row_filenum usage
	for(int i = 0; i< infilename.size(); i++){
		std::ifstream input(infilename[i].c_str());
		std::string line;
		curr_rows = 0;
		while(getline(input,line)) { 
			data[i].push_back(line);
			curr_rows++;
			lastline[i] = line;
		}
		num_values.push_back(count_comma(lastline[i]));
		rows_count[i] = curr_rows;

		std::vector<char> commastring;
		for (int comma = 0; comma < num_values[i]; comma++){
			commastring.push_back(',');
		}
		std::string str(commastring.begin(),commastring.end());
		emptyline[i] = str;

	 // 	if(num_rows == 0) {
		//   	num_rows = curr_rows;
		// }
		// else if(num_rows != curr_rows) {
		// //TO-DO if no. of rows in some csv is less than the others
		// //error or repeating values or empty commas
		// 	std::cout << "Number of rows in all files are not same. Enter: \n 
		// 		1)Repeat last values in all empty rows of that file \n
		// 		2)Leave the rows empty \n
		// 		Waiting for your input...\n";
		// 	std::cin >> repeat;
		// }
		input.close();
	}

	std::cout << "What would you like to do to equalize the number of rows in all CSVs:\n";
	std::cout << " 1) Repeat last values \n 2) Keep them empty\n";
	std::cin >> repeat;

	num_rows = *std::max_element(rows_count.begin(),rows_count.end()); 
	for (int j = 0; j< rows_count.size(); j++) {
		for(int add_lines = 0; add_lines < num_rows-rows_count[j]; add_lines++ ) {
			if(repeat == 1)
				data[j].push_back(lastline[j]);
			else
				data[j].push_back(emptyline[j]);
		}
	}

	std::ofstream output(outfilename.c_str(), std::ofstream::out | std::ofstream::app);
	for (int row = 0; row < num_rows; row++ ) {
		for (int filenum = 0; filenum < num_files; filenum++) {
			if (filenum != 0) output << ",";
			output << data[filenum][row];
		}
		output << "\n";
	}

	//TO-DO close filestreams-done
	output.close();
}


void colmerge(int num_files, std::vector<std::string> infilename, std::string outfilename){
	std::vector< std::vector<std::string> > data(num_files);
	int curr_rows;
	for(int i = 0; i< infilename.size(); i++){
		std::ifstream input(infilename[i].c_str());
		std::string line;
		curr_rows = 0;
		while(getline(input,line)) {
			// TO-DO matching the columns and number of columns in two CSVs

			// if(curr_rows == 0) {

			// } 
			data[i].push_back(line);
			curr_rows++;
		}
		input.close();
	}

	std::ofstream output(outfilename.c_str(), std::ofstream::out | std::ofstream::app);
	for(int filenum = 0; filenum < num_files; filenum++) {
		for(int row = 0; row < data[filenum].size(); row++) {
			output << data[filenum][row]<<"\n";
		}
	}

	output.close();
}

int main(int argc, char** argv){
	std::vector<std::string> inputfile;
	int num_files = 0;
	std::string outputfile;

	if (argc > 1){
		outputfile = argv[argc-1];
		num_files = argc-2;
		for(int i = 1; i<= num_files; i++) {
			std::string str(argv[i]);
			inputfile.push_back(str);
		}
	}
	else{
		std::string inputstr;
		std::cout << "Enter the name of output CSV (Ex:- merged.csv):\n";
		std::cin >> outputfile;
		std::cout << "Enter the name of input CSV (Ex:- input.csv):\n";
		std::cin >> inputstr;
		inputfile.push_back(inputstr);
		while(inputstr != "Quit" && inputstr != "quit"){
			num_files++;
			std::cout << "Enter name of next input CSV (Ex:- newinput.csv) or enter quit:\n";
			std::cin >> inputstr;
			inputfile.push_back(inputstr);
		}
	}

	int option;
	std::cout << "Merge type: \n 1)Column wise\n 2)Row wise\n";
	std::cin >> option;
	if(option == 1)
		colmerge(num_files,inputfile,outputfile);
	else if(option == 2)
		rowmerge(num_files,inputfile,outputfile);
	//TO-DO User Interface
	return 0;
}
