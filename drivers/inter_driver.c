#include <inter_driver.h>
#include <stdint.h>
#include <MKL25Z4.h>

uint8_t store_read;

interupthtingy{
	store_read = read_i2c();

}

pull_read(){
	return store_read;
}