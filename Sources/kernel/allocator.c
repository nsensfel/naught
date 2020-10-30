#include <stdint.h>

#include <naught/config.h>

#include <naught/kernel/mutex.h>

static naught_mutex_t * allocator_mutex;
static void * next_address;

void naught_allocator_init (void)
{
   allocator_mutex = (naught_mutex_t *) NAUGHT_CONFIG_SHARED_DDR_ADDR_START;
   next_address =
      (void *)
      (
         ((char *) allocator_mutex) + sizeof(void *)
      );
}

void * naught_allocator_get (const uint8_t core_id, const uint32_t size)
{
   void * result;

   naught_mutex_lock(core_id, allocator_mutex);

   result = next_address;

   next_address = (void *) (((char *) next_address) + size);

   if (next_address > NAUGHT_CONFIG_SHARED_DDR_ADDR_END)
   {
      next_address = result;
      result = (void *) 0;
   }

   naught_mutex_unlock(core_id, allocator_mutex);

   return result;
}
