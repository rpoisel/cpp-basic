set(TARGET_PLATFORM AVR)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=atmega328p -g -Os -Wall -Werror" CACHE STRING "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmcu=atmega328p -g -Os -Wall -Werror -w -fpermissive -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto" CACHE STRING "")
