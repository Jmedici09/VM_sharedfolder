#include <slider.h>
#include <stdint.h>
#include <stdbool.h>
#include <MKL25Z4.h>

void initialize_slider()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
	TSI0->GENCS = 
		TSI_GENCS_CURSW(0) // current sources not swapped
	  | TSI_GENCS_STM(0) // SW trigger
	  | TSI_GENCS_STPE(0) //do not enable in stop mode
	  | TSI_GENCS_TSIIEN(0) // interrupts not enabled
	  | TSI_GENCS_NSCN(1) // 1 scan per electrode
	  | TSI_GENCS_PS(4) //prescale div-by-16
	  | TSI_GENCS_EXTCHRG(0) //500nA charge
	  | TSI_GENCS_DVOLT(0)
	  | TSI_GENCS_REFCHRG(4) //4
	  | TSI_GENCS_MODE(0); //no noise detection
	TSI0->GENCS |= TSI_GENCS_TSIEN(1); //TSI enabled
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK | TSI_GENCS_OUTRGF_MASK; // clear status		
}

_Bool slider_scan_has_completed()
{
	return TSI0->GENCS & TSI_GENCS_EOSF_MASK;
}
_Bool slider_scan_is_in_progress()
{
	return TSI0->GENCS & TSI_GENCS_SCNIP_MASK;	
}
uint16_t touch_scan()
{
	TSI0->DATA = TSI_DATA_TSICH(9) | TSI_DATA_SWTS_MASK;
	while( slider_scan_is_in_progress() ); // polling
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
	return TSI0->DATA & TSI_DATA_TSICNT_MASK;
}
