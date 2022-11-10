#pragma once

#include <vector>
#include <ostream>

namespace WordConverter {
	
	// Wrapper for output stream
	class OutputStream {
	private:
		std::vector<std::reference_wrapper<std::ostream>> m_output_streams;

	public:
		void RegisterStream(std::ostream& s);

		void WriteNext(const std::string&, const std::string&);
		void WriteNext(int, const std::string&);
	};

}