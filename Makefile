# Makefile
# Properties
DESTINATION = firmware
DEVICE      = atmega328p
PROGRAMMER  = usbasp-clone
# Utilities
AVRDUDE     = avrdude -c $(PROGRAMMER) -p $(DEVICE)
AVRGCC      = avr-gcc -mmcu=$(DEVICE) -Os -Wall -DF_CPU=18432000UL
AVROBJCOPY  = avr-objcopy --input-target elf32-avr --output-target ihex --verbose
AVROBJDUMP  = avr-objdump --disassemble
AVRSIZE     = avr-size --format=AVR --mcu=$(DEVICE)

default: build

build: clean
	@mkdir target
	@$(AVRGCC) -c ./src/drivers/gpio.c -o ./target/gpio.o
	@$(AVRGCC) -c ./src/drivers/uart328p.c -o ./target/uart328p.o
	@$(AVRGCC) -c ./src/drivers/lcd1602.c -o ./target/lcd1602.o
	@$(AVRGCC) -c ./src/drivers/buzzer.c -o ./target/buzzer.o
	@$(AVRGCC) -c ./src/drivers/led.c -o ./target/led.o
	@$(AVRGCC) -c ./src/drivers/button.c -o ./target/button.o
	@$(AVRGCC) -c ./src/main.c -o ./target/main.o 
	@$(AVRGCC) -o ./target/$(DESTINATION).elf ./target/main.o ./target/gpio.o ./target/lcd1602.o ./target/buzzer.o ./target/led.o ./target/button.o ./target/uart328p.o
	@$(AVROBJCOPY) ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

disasm: ./target/$(DESTINATION).elf
	@$(AVROBJDUMP) ./target/$(DESTINATION).elf

size: ./target/$(DESTINATION).elf
	@$(AVRSIZE) ./target/$(DESTINATION).elf

check:
	@$(AVRDUDE)

erease:
	@$(AVRDUDE) -e

upload:
	@$(AVRDUDE) -U flash:w:./target/$(DESTINATION).hex:i
