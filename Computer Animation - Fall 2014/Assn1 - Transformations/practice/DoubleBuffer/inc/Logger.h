#ifndef LOGGER_H
#define LOGGER_H 1

#include <string>

class Logger {
	public:
		struct ColorCode {
			const char * tag;
			const char * code;
			const char * name;
		};

	public:
						Logger				(unsigned int indSize = 1, bool colorOn = true);
						~Logger				();

		Logger *		log					(const char * fmt, ...);
		Logger *		log					(const std::string & fmt, ...);
		Logger *		indent				(const int i);
		Logger *		resetIndent			();
		Logger *		setIndent			(const int i);
		Logger *		setIndentSize		(const int i);
		Logger *		enableColor			(bool);
		std::string		getIndentStr		();
		std::string		colorize			(const std::string & str);
		void			showColorCodes		();

	protected:
		static const	unsigned int		numColors = 9;
		static const	ColorCode			colors [numColors];
						unsigned int		ind;
						unsigned int		indSize;
						bool				colorEnabled;
};

	#ifdef LOGGING_ENABLED
		inline Logger * Logger::indent (const int i) {
			ind += i;
			if (ind < 0) { ind = 0; }
			return this;
		}

		inline Logger * Logger::resetIndent () {
			ind = 0;
			return this;
		}

		inline Logger * Logger::setIndent (const int i) {
			if (i < 0) { ind = 0; }
			else { ind = i; }
			return this;
		}

		inline Logger * Logger::setIndentSize (const int i) {
			if (i < 0) { indSize = 0; }
			else { indSize = i; }
			return this;
		}

		inline Logger * Logger::enableColor (bool b) {
			#ifdef WIN32
				// ANSI escape sequences don't work on winblows :(
				colorEnabled = false;
			#else
				colorEnabled = b;
			#endif
			return this;
		}
	
	#else
		inline Logger * Logger::indent (const int i) {
			return this;
		}

		inline Logger * Logger::resetIndent () {
			return this;
		}

		inline Logger * Logger::setIndent (const int i) {
			return this;
		}

		inline Logger * Logger::setIndentSize (const int i) {
			return this;
		}

		inline Logger * Logger::enableColor (bool b) {
			return this;
		}

		inline Logger::Logger (unsigned int indentSize, bool colorOn) {
		}

		inline Logger::~Logger () {
		}

		inline Logger * Logger::log (const char * fmt, ...) {
			return this;
		}

		inline Logger * Logger::log (const std::string & fmt, ...) {
			return this;
		}

		inline std::string Logger::getIndentStr () {
			std::string rtrn;
			return rtrn;
		}

		inline std::string Logger::colorize (const std::string & str) {
			std::string rtrn;
			return rtrn;
		}

		inline void Logger::showColorCodes () {
		}

	#endif

#endif

