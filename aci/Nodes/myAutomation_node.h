// EXRAIL processes this file multiple times; no include guard.
HAL_IGNORE_DEFAULTS
HAL(LCTechX8, 300)


// Inputs report states; no automatic input-to-relay switching.

SHARED_WRITE_VPINS(300, 8)
SHARED_SENSOR(300, 8, 8300)

REMOTE_SENSOR(308,8)
