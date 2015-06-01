#ifndef FILECONTENTS_H
#define FILECONTENTS_H 1

#include <ostream>
#include <string>

/*
	Class to handle easy reading of files for those times when
	you just want to grab the contents of a file as a string.
*/
class FileContents {
	public:
						FileContents			();
		explicit		FileContents			(const FileContents & other);
						~FileContents			();

		FileContents *	copy					(const FileContents & other);
		bool			load					(const char * fname);
		bool			load					(const std::string & fname);
		void			unload					();
		void			setContents				(const char * newContents);
		void			setContents				(const std::string & newContents);
		const char *	getContents				() const;
		bool			save					(const char * fname);
		bool			save					(const std::string & fname);
						operator const char *	() const;
		FileContents *	operator =				(const FileContents & other);
		FileContents *	operator =				(const char * newContents);
		FileContents *	operator =				(const std::string & newContents);

	private:
		std::string		contents;
};

inline std::ostream & operator << (std::ostream & stream, const FileContents & fc) {
	stream << fc.getContents ();
	return stream;
}

inline FileContents * FileContents::copy (const FileContents & other) {
	setContents (other.contents);
	return this;
}

inline FileContents * FileContents::operator = (const FileContents & other) {
	return copy (other);
}

inline FileContents * FileContents::operator = (const char * newContents) {
	setContents (newContents);
	return this;
}

inline FileContents * FileContents::operator = (const std::string & newContents) {
	setContents (newContents);
	return this;
}

inline bool FileContents::load (const std::string & fname) {
	return load (fname.c_str ());
}

inline void FileContents::unload () {
	contents.clear ();
}

inline void FileContents::setContents (const std::string & newContents) {
	contents = newContents;
}

inline void FileContents::setContents (const char * newContents) {
	contents = newContents;
}

inline const char * FileContents::getContents () const {
	return contents.c_str ();
}

inline FileContents::operator const char * () const {
	return getContents ();
}

inline bool FileContents::save (const std::string & fname) {
	return save (fname.c_str ());
}

#endif