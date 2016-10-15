#include <stdio.h>
const char* format_error_message(int err)
{
    const static char a = (char)err;

    // printf(error_message, "Error %#x occurred", err);
    return &a;
}


int main(int argc, char const *argv[]) {
  int a = 'a';
  int b = 'b';

  if (a != 0 && b != 0)
  {
      printf(
          "do_something failed (%c) AND do_something_else failed (%c)\n",
          *format_error_message((int)a), *format_error_message((int)b));
  }
  return 0;
}
