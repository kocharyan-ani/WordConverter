#pragma once

#include "InputStream.h"
#include "OutputStream.h"

namespace WordConverter {

	class Converter {
	private:
		InputStream m_input_stream;
		OutputStream m_output_streams;

	public:
		Converter(const InputStream& is, const OutputStream& os)
			: m_input_stream(is)
			, m_output_streams(os)
			, m_ended(false)
			, m_read_again(false)
		{}

		void Convert();

	private:
		bool ParseZero();
		bool ParseNonZero();
		int ParseThreeDigits();
		int ParseTwoDigits();

	private:
		void ReadNext();

	private:
		const std::string& GetSpaces() const;

	private:
		std::string m_original_word;
		std::string m_word;
		std::string m_spaces;
		std::string m_previous_spaces;
		bool m_ended;
		bool m_read_again;
	};

}