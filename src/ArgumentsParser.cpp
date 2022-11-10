#include "ArgumentParser.h"

namespace WordConverter {

	bool ArgumentParser::Parse(int argc, char** argv) {
		if (argc < 3) {
			return false;
		}
		const std::string i_option = "-i";
		const std::string o_option = "-o";
		if (argv[1] != i_option && argv[1] != o_option) {
			return false;
		}
		// The case when -i is the first argument
		if (argv[1] == i_option) {
			m_input_file_name = argv[2];
			if (argc != 3) {
				if (argc < 5) {
					return false;
				}
				if (argv[3] != o_option) {
					return false;
				}
				m_output_file_name = argv[4];
			}
		}
		// The case when -o is the first argument
		else {
			if (argc < 5) {
				return false;
			}
			m_output_file_name = argv[2];
			if (argv[3] != i_option) {
				return false;
			}
			m_input_file_name = argv[4];
		}
		return true;
	}

}