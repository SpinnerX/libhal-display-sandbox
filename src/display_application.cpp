#include <libhal-exceptions/control.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/error.hpp>

#include <resource_list.hpp>

#include <libhal-arm-mcu/lpc40/i2c.hpp>

void application(resource_list& p_resources)
{
  using namespace std::chrono_literals;

  // Calling `value()` on the optional resources will perform a check and if the
  // resource is not set, it will throw a std::bad_optional_access exception.
  // If it is set, dereference it and store the address in the references below.
  // When std::optional<T&> is in the standard, we will change to use that.
  auto& led = *p_resources.status_led.value();
  auto& clock = *p_resources.clock.value();
  auto& console = *p_resources.console.value();

  hal::print(console, "Starting Application!\n");
  hal::print(console, "Will reset after ~10 seconds\n");



  p_resources.reset();
}
