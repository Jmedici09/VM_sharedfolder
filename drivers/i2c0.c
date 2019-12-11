	#include <i2c0.h>
	#include <stdbool.h>
	#include <stdint.h>
	#include <MKL25Z4.h>

#include <rgbled.h>


static void i2c0_do_start();
static void i2c0_do_repeat_start();
static void i2c0_do_stop();

static void i2c0_config_tx_mode();
static void i2c0_config_rx_mode();

static _Bool i2c0_is_busy();
static _Bool i2c0_last_transfer_is_complete();
static void i2c0_wait_for_transmission_to_complete();

static void  i2c0_put_byte( uint8_t data );
static uint8_t  i2c0_get_byte();

static void i2c0_nack_after_recieved_byte();

void initialize_i2c0()
{
	//Clock Gating
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[24] =  (PORTE->PCR[24] & ~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(5);
	PORTE->PCR[25] =  (PORTE->PCR[25] & ~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(5);
	
	I2C0->F = I2C_F_ICR(15)  | I2C_F_MULT(0);
	
	I2C0->C2 |= I2C_C2_HDRS_MASK;
	I2C0->C1 |= I2C_C1_IICEN_MASK;
	
	
initialize_rgbled();	
}

uint8_t i2c0_read_byte(uint8_t device, uint8_t reg)
{
	while( i2c0_is_busy() ) // necessary for back to back transmissions
set_led_to( BLACK );
	i2c0_config_tx_mode();
	i2c0_do_start();
	i2c0_put_byte( device );
	i2c0_wait_for_transmission_to_complete(); // Better as non-blocking
set_led_to( BLACK );
	// TODO check for ACK
	// if( !i2c0_ack_recieved() )
	//		goto END
	i2c0_put_byte( reg );
	i2c0_wait_for_transmission_to_complete();// Better as non-blocking
set_led_to( BLACK );
	// TODO check for ACk
	i2c0_do_repeat_start(); // this is a restart
	i2c0_put_byte( device | 0x01 );
	i2c0_wait_for_transmission_to_complete();// Better as non-blocking
set_led_to( BLACK );
	// TODO check for ACk
	i2c0_config_rx_mode();
	i2c0_get_byte();
	i2c0_nack_after_recieved_byte();
	i2c0_wait_for_transmission_to_complete(); // Better as non-blocking
set_led_to( BLACK );
	// TODO check for ACk
	i2c0_config_tx_mode();
	i2c0_do_stop();
	
	return i2c0_get_byte();
	
	//data = i2c0_get_byte();
	//return true;
	/* 
END:  i2c0_config_tx_mode();
	 i2c0_do_stop();
	return false; */
	
}
_Bool i2c0_write_byte(uint8_t device, uint8_t reg, uint8_t data)
{
	while( i2c0_is_busy() ) // necessary for back to back transmissions
set_led_to( BLACK );
	i2c0_config_tx_mode();
	i2c0_do_start();
	i2c0_put_byte( device );
	i2c0_wait_for_transmission_to_complete(); // Better as non-blocking
set_led_to( BLACK );
	// TODO check for ACK
	// if( !i2c0_ack_recieved() )
	//		goto END
	i2c0_put_byte( reg );
	i2c0_wait_for_transmission_to_complete(); // Better as non-blocking
set_led_to( BLACK );
	// TOD check for ACk
	//i2c0_put_byte( device | 0x01 );
	i2c0_put_byte( data );
	i2c0_wait_for_transmission_to_complete();// Better as non-blocking
set_led_to( BLACK );
	// TOD check for ACk
	i2c0_do_stop();
	
	return true;
	/* 
END:  i2c0_config_tx_mode();
	 i2c0_do_stop();
	return false;
	 */
}



static void i2c0_do_start()
{
	I2C0->C1 |= I2C_C1_MST_MASK;
}
static void i2c0_do_repeat_start()
{
	I2C0->C1 |= I2C_C1_RSTA_MASK;
}
static void i2c0_do_stop()
{
	I2C0->C1 &= ~I2C_C1_MST_MASK;
}

static void i2c0_config_tx_mode()
{
	I2C0->C1 |= I2C_C1_TX_MASK;
}
static void i2c0_config_rx_mode()
{
	I2C0->C1 &= ~I2C_C1_TX_MASK;
}

static _Bool i2c0_is_busy()
{
	return I2C0->S & I2C_S_BUSY_MASK;
}
static _Bool i2c0_last_transfer_is_complete()
{
	//return I2C0->S & I2C_S_TCF_MASK;
	return (I2C0->S & I2C_S_IICIF_MASK); // change this
}
static void i2c0_wait_for_transmission_to_complete() // add this
{
	while( !i2c0_last_transfer_is_complete());
	I2C0->S |= I2C_S_IICIF_MASK;
}

static void  i2c0_put_byte( uint8_t data )
{
	I2C0->D = data;
}
static uint8_t  i2c0_get_byte()
{
	return I2C0->D;
}

static void i2c0_nack_after_recieved_byte()
{
	I2C0->C1 |= I2C_C1_TXAK_MASK;
}