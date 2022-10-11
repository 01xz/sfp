#ifndef __SFP_TYPES_HH
#define __SFP_TYPES_HH

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define SFP_UTYPE uint16_t
#define SFP_STYPE int16_t
#define SFP_WIDTH 16
#define SFP_ZERO  ((SFP_UTYPE)0x0000)
#define SFP_MAX   ((SFP_UTYPE)0x7FFF)
#define SFP_MIN   ((SFP_UTYPE)0x0001)
#define SFP_MSB   ((SFP_UTYPE)0x8000)
#define SFP_MASK  ((SFP_UTYPE)0xFFFF)

#ifdef __cplusplus
}
#endif

#endif
