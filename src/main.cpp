#include <iostream>
#include <fstream>

#include "ArgumentParser.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Converter.h"

int main(int argc, char** argv) {
	WordConverter::ArgumentParser parser;
	if (!parser.Parse(argc, argv)) {
		std::cout << "Command line arguments are invalid.\n"
			"Expected arguments: -i <input_file> [-o <output_file>]" << std::endl;
		return 1;
	}

	std::ifstream input_file_stream;
	std::ofstream output_file_stream;
	input_file_stream.open(parser.GetInputFileName(), std::fstream::in);
	if (!input_file_stream) {
		std::cout << "Cannot open the file " << parser.GetInputFileName() << std::endl;
		return 1;
	}
	WordConverter::InputStream input_stream(input_file_stream);

	WordConverter::OutputStream output_stream;
	output_stream.RegisterStream(std::cout);
	if(!parser.GetOutputFileName().empty()) {
		output_file_stream.open(parser.GetOutputFileName(), std::fstream::out);
		if (!output_file_stream) {
			std::cout << "Cannot open the file " << parser.GetOutputFileName() << std::endl;
			return 1;
		}
		output_stream.RegisterStream(output_file_stream);
	}

	WordConverter::Converter converter(input_stream, output_stream);
	converter.Convert();

	return 0;
}