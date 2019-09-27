// ArduinoCompat/HardwareSPI.h
// STM32 implementattion of Arduino compatible SPI class

#ifndef _HardwareSPI_h
#define _HardwareSPI_h
#include <mgos.h>
#include <mgos_spi.h>
#include <stdint.h>

extern "C"
{
    struct mgos_spi *mgos_spi_get_global(void);
    bool mgos_spi_run_txn(struct mgos_spi *spi, bool full_duplex, const struct mgos_spi_txn *txn);
}

//Not used on MGOS as SPI config is set in mos.yml
typedef enum SPIFrequency {
    SPI_21_0MHZ      = 0, /**< 21 MHz */
    SPI_10_5MHZ      = 1, /**< 10.5 MHz */
    SPI_5_25MHZ      = 2, /**< 5.25 MHz */
    SPI_2_625MHZ     = 3, /**< 2.625 MHz */
    SPI_1_3125MHZ    = 4, /**< 1.3125 MHz */
    SPI_656_25KHZ    = 5, /**< 656.25 KHz */
    SPI_328_125KHZ   = 6, /**< 328.125 KHz */
} SPIFrequency;

//Not used on MGOS as SPI config is set in mos.yml
#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x03
#define SPI_MODE3 0x02

class HardwareSPI
{
public:
    HardwareSPI(uint32_t spiPortNumber); // Only port SPI1 is currently supported
    void begin(int frequency, uint32_t bitOrder, uint32_t mode);
    void end(void);
    uint8_t reverseBits(uint8_t value);
    uint8_t transfer(uint8_t data);

private:
    uint32_t spiPortNumber; // Not used yet.
    struct mgos_spi_txn txn;
    uint32_t bitOrder;
};
extern HardwareSPI SPI;


#endif
