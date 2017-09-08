#include "lang_token.h"

#include <string.h>

namespace Lang
{

Token::Token(Token const& other)
{
  this->text = other.text;
  this->len = other.len;
  this->type = other.type;
}

Token& Token::operator=(Token&& other)
{
  this->text = other.text;
  this->len = other.len;
  this->type = other.type;

  return *this;
}

Token& Token::operator=(Token const& other)
{
  this->text = other.text;
  this->len = other.len;
  this->type = other.type;

  return *this;
}

bool Token::operator==(Token const& rhs) const
    {
  return this->text == rhs.text && this->len == rhs.len && this->type == rhs.type;
}

void Token::getNullTerminatedText(char* buf, size_t buflen) const
    {
  auto numBytesToCopy = buflen - 1 < this->len ? buflen - 1 : this->len;
  strncpy(buf, this->text, numBytesToCopy);
  buf[numBytesToCopy] = '\0';
}

}
