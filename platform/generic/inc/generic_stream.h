#ifndef	__MIMOSA_GENERIC_STREAM_H
#define __MIMOSA_GENERIC_STREAM_H
/* Copyleft(c)2010 HackerFellowship. All lefts reserved.
   
 * NalaGinrut <NalaGinrut@gmail.com>
 
 * May Lord Bless!Happy Hacking!
 
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
 
 * You should have read the GNU General Public License before start "RTFSC".
 
 * If not,se <http://www.gnu.org/licenses/>
 */

#include <types.h>
#include <bits.h>

typedef void* (*gs_alloc_t)(void*);
typedef void (*gs_free_t)(void*);

// GSO status
// FIXME: I need a more flexible logic ruler;
#define GSOS_NORMAL	_B(0) // normal 
#define GSOS_BLOCK	_B(1) // passive stop
#define GSOS_DRY	_B(2) // count is 0;
#define GSOS_STOP	_B(3) // initiative stop
#define GSOS_READY	_B(4) // ready for working
#define GSOS_ERROR	_B(5) // FIXME: more detail err info??

#define GSO_MAX_BUF_LEN		4096
#define GSO_MAX_NAME_LEN	256

#define MAKE_GSO(name ,buffer ,type)		\
  generic_stream_create(name ,buffer ,type,	\
			GSOS_NORMAL ,NULL,	\
			NULL ,NULL)

#define MAKE_CUSTOM_GSO(name ,buffer ,custom ,alloc ,free) \
  generic_stream_create(name ,buffer ,GST_CUSTOM,	   \
			GSOS_NORMAL ,custom,		   \
			alloc ,free)

/* NOTE: AUTO will check type first time, JUST ONCE!
 * 	 ALWAYS_CHECK will check type each time.
 */
typedef enum Generic_Stream_Type
  {
    GST_NORMAL, /* normal stream will free the buffer.
		 * it's for normal procedure.
		 */
    GST_DEVICE, /* device stream won't free the buffer.
		 * any device relative stream must use this
		 * type.
		 */
    GST_CUSTOM,	/* custom stream must handle the memory all by
		 * itself. custom must contain "alloc" and
		 * "free" procedure.
		 */
 // TODO: what are others types??
  }gs_type_t;

typedef struct Generic_Stream_Obj
{
  char *name;
  char *buffer;
  size_t position;
  size_t count; // bytes count need to be handled;
  gs_type_t type;
  u32_t status;

  void *custom;
  // FIXME: I need semaphore in case multi ops.
  gs_alloc_t alloc;
  gs_free_t free;
}gs_obj_t;



gs_obj_t *generic_stream_create(char *name ,char *buffer,
				gs_type_t type ,u32_t status,
				void *custom,
				gs_alloc_t alloc,
				gs_free_t free);
retnum generic_stream_shoot(void const *data ,gs_obj_t *gso ,size_t size);
retnum generic_stream_imbibe(gs_obj_t *gso ,void *data ,size_t size);
retnum generic_stream_dry(gs_obj_t *gso);
#endif // End of __MIMOSA_GENERIC_STREAM_H;
