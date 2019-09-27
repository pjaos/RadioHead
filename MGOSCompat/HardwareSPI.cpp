// ArduinoCompat/HardwareSPI.cpp
//
// Interface between Arduino-like SPI interface and STM32F4 Discovery and similar
// using STM32F4xx_DSP_StdPeriph_Lib_V1.3.0

#include <RadioHead.h>
#if (RH_PLATFORM == RH_PLATFORM_MONGOOSE_OS)

#include <mgos.h>
#include <mgos_spi.h>
#include <HardwareSPI.h>

HardwareSPI::HardwareSPI(uint32_t spiPortNumber) : spiPortNumber(spiPortNumber)
{
}

void HardwareSPI::begin(int frequency, uint32_t bitOrder, uint32_t mode)
{
    /*
    //The following SPI params should be setup in the Mongoose OS mos.yml
    struct mgos_config_spi bus_cfg = {
        .unit_no = 3,
        .miso_gpio = 19,
        .mosi_gpio = 23,
        .sclk_gpio = 18,
        .cs0_gpio = 5,
        .debug = true,
    };
    */

    this->txn.cs = 0; /* Use CS0 line as configured by cs0_gpio */
    this->txn.mode = mode;
    this->txn.freq=frequency;
    this->bitOrder=bitOrder;
}

void HardwareSPI::end(void)
{
    struct mgos_spi *spi = mgos_spi_get_global();
    mgos_spi_close(spi);
}

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

uint8_t HardwareSPI::reverseBits(uint8_t value)
{
    value = (value & 0xF0) >> 4 | (value & 0x0F) << 4;
    value = (value & 0xCC) >> 2 | (value & 0x33) << 2;
    value = (value & 0xAA) >> 1 | (value & 0x55) << 1;
    return value;
}

uint8_t HardwareSPI::transfer(uint8_t data)
{
    bool full_duplex=true;

    if( this->bitOrder == LSBFIRST ) {
        data = reverseBits(data);
    }

    return (uint8_t) mgos_spi_run_txn( mgos_spi_get_global(), full_duplex, &this->txn);
}

#endif
