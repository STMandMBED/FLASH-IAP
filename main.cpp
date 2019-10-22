#include <mbed.h>

// создаем объект класса FlashIAP и назовем его flash
FlashIAP flash;

int main()
{
  // 1) открываем память для работы с ней
  flash.init();

  // 2) получаем начальный адрес памяти
  const uint32_t flash_start = flash.get_flash_start();
  // 3) получаем размер памяти
  const uint32_t flash_size = flash.get_flash_size();
  // 4) определяем конечный адрес памяти
  const uint32_t flash_end = flash_start + flash_size;
  // 5) получаем размер сектора
  uint32_t sector_size = flash.get_sector_size(flash_end - 1);

// переменные для записи и чтения данных
  uint8_t data_write[9] = {255, 120, 130, 140, 150, 160, 170, 180, 190};
  uint8_t data_read[9];

  // 6) адрес вычисляем адрес начала страницы
  uint32_t addr = flash_end - sector_size;

  // выводим информацию о flash в serial
  printf("flash_start = 0x%.8x\r\n", flash_start);
  printf("flash_end = 0x%.8x\r\n", flash_end - 1);
  printf("flash_size = %.6d\r\n", flash_size);
  printf("sector_size = %d\r\n", sector_size);
  printf("begin addr = 0x%.8x\r\n", addr);

  // 7) стираем память
  flash.erase(addr, sector_size);
  // 8) сохраняем данные
  flash.program(data_write, addr, 9);
  // 9) считываем данные
  flash.read(data_read, addr, 9);
  // 10) закрываем память
  flash.deinit();

  for (int i = 0; i <= 8; i++)
  {
    // выводим данные в serial
    printf("EEdata_read = %d\r\n", data_read[i]);
  }
}
