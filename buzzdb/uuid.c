#include <uuid/uuid.h>


void
new_uuid (char out[UUID_STR_LEN])
{
  uuid_t b;
  uuid_generate (b);
  uuid_unparse_lower (b, out);
}

