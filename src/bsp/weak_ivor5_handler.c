/**
 * @file       weak_ivor5_handler.c
 * @headerfile bsp_prv.h
 * @author     sstasiak
 * @brief      weak ivor5 handler
 * @attention  { not for use in safety critical systems       }
 * @attention  { not for use in pollution controlled vehicles }
 *
 * (c) Copyright 2012, Sean Stasiak <sstasiak at gmail dot com>
 *
 */

#include <stdint.h>
#include "bsp.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/**
 * @brief default ivor5 handler, override as desired
 * @note Alignment interrupt (SPR 405)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor5_handler( void )
{
  default_ivor_handler();
}
#pragma pop
/* --| PUBLIC   |--------------------------------------------------------- */