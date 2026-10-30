// EXRAIL processes this file multiple times; no include guard.
HAL_IGNORE_DEFAULTS
HAL(LCTechX4, 8020)


// Inputs report states; no automatic input-to-relay switching.

SHARED_WRITE_VPINS(8020, 4)
SHARED_SENSOR(8024, 4)
JMRI_SENSOR(8024, 4)