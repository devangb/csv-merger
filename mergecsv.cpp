#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
//#include <cstring>

void rowmerge(int num_files, std::vector<std::string> infilename, std::string outfilename){
	std::vector< std::vector<std::string> > data(num_files);
	std::vector<std::string> lastline(num_files);
	std::vector<int> rows_count(num_files);
	std::std::vector<size_t> num_values(num_files);
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
		num_values[i] = std::count(lastline[i].begin(), lastline[i].end(), ',');
		rows_count[i] = curr_rows;

	 // 	if(num_rows == 0) {
		//  	num_rows = curr_rows;
		// }
		// else if(num_rows != curr_rows) {
		//  	//TO-DO if no. of rows in some csv is less than the others
		//  	//error or repeating values or empty commas
		// }
		input.close();
	}

	//std::cout << lastline[1];
	num_rows = *std::max_element(rows_count.begin(),rows_count.end());
	//std::cout << num_rows <<"\n"; 
	for (int j = 0; j< rows_count.size(); j++) {
		for(int add_lines = 0; add_lines < num_rows-rows_count[j]; add_lines++ ) {
			data[j].push_back(lastline[j]);
			//std::cout<<j<< num_rows << rows_count[j] << lastline[j] <<"\n";
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
			//output <<filenum << " , " << row<<"\n";
			output << data[filenum][row]<<"\n";
		}
		//output << "\n";
	}

	output.close();
}

int main(int argc, char** argv){
	std::vector<std::string> inputfile;
	std::string outputfile(argv[argc-1]);
	int num_files = argc-2;
	for(int i = 1; i<= num_files; i++) {
		std::string str(argv[i]);
		inputfile.push_back(str);
	}

	rowmerge(num_files,inputfile,outputfile);
	// //int num_files = 2;
	// std::string filename[2];
	// //std::cin>>filename[0];
	// //std::cin>>filename[1];

	// int num_files = argc;
	// std::string 
	// std::vector< std::vector<std::string> > data(num_files);
	// for( int i = 1; i < num_files; i++ ) {
 //    	//std::ifstream input(filename[i].c_str());
 //    	std::cout<< argv[i] << std::endl;
 //    	filename[i-1] = argv[i];
 //    	std::ifstream input( argv[i] );
 //    	std::string line;
 //    	while( getline(input, line) ) data[i].push_back(line);
	// }

	// std::ofstream output("concatenated.csv", std::ofstream::out | std::ofstream::app);
	// int num_rows = data[0].size();
	// for( int row = 0; row < num_rows; row++ ) {
	//     for( int f = 0; f < num_files; f++ ) {
	//         if( f != 0 ) output << ",";
	//         output << data[f][row];
	//     }
	//     output << "\n";
	// }
}