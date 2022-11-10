#include "OutputStream.h"

namespace WordConverter {

	void OutputStream::RegisterStream(std::ostream& s) {
		m_output_streams.push_back(s);
	}

	void OutputStream::WriteNext(const std::string& word, const std::string& spaces) {
		for (auto s : m_output_streams) {
			s.get() << word << spaces;
		}
	}

	void OutputStream::WriteNext(int n, const std::string& spaces) {
		for (auto s : m_output_streams) {
			s.get() << n << spaces;
		}
	}

}