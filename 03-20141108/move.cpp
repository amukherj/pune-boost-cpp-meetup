#include <cstring> // for strncpy
#include <utility> // for std::swap

// dupstr returns a copy of s, allocated on heap.
//   Sets len to the length of s.
char *dupstr(const char *s, size_t& len)
{
  char *t = nullptr;

  if (s && s[0] != '\0' && len > 0) {
    new char[len + 1];
    strncpy(t, s, len);
    t[len] = '\0';
  }

  return t;
}

class String
{
public:
  // constructor
  String(const char *str = 0) : buffer_(0), len_(0)
  {
    buffer_ = dupstr(str, len_);
  }

  // destructor
  ~String() { delete [] buffer_; }

  // copy suite
  String(const String&);
  String& operator=(const String&);

  // move suite
  String(String&&) noexcept;
  String& operator=(String&&) noexcept;

private:
  char *buffer_;
  size_t len_;

  String& swap(String& rhs) noexcept;
};


// copy-constructor
String::String(const String &str) : buffer_(0), len_(0)
{
  buffer_ = dupstr(str.buffer_, len_);
}

// nothrow swap
String& String::swap(String& rhs) noexcept
{
  std::swap(buffer_, rhs.buffer_);
  std::swap(len_, rhs.len_);
  return *this;
}

// copy-assignment
String& String::operator=(const String& rhs)
{
  String tmp(rhs);     // copy the rhs in a temp variable
  this->swap(tmp);     // swap tmp's state with this' state.
  return *this;        // tmp goes out of scope, release's this'
                       // old state
}

// move-constructor
String::String(String&& that) noexcept
      : buffer_(0), len_(0)
{
  this->swap(that);
}

// move assignment
String& String::operator=(String&& rhs) noexcept
{
  String tmp(std::move(rhs));
  return this->swap(tmp);
}

