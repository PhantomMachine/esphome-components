import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,

    DEVICE_CLASS_DISTANCE,
)
from esphome import pins

DEPENDENCIES = ['uart']

CONF_ENABLE_RX_PIN="enable_rx_pin"

pmod_maxsonar_ns = cg.esphome_ns.namespace('pmod_maxsonar')
PmodMaxSonar = pmod_maxsonar_ns.class_('PmodMaxSonar', cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        PmodMaxSonar,
        unit_of_measurement="in",
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_DISTANCE,
    )
    .extend(
        {
            cv.Required(CONF_ENABLE_RX_PIN): pins.gpio_output_pin_schema
        }
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(PmodMaxSonar),
        }
    )
    .extend(cv.polling_component_schema('60s'))
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await uart.register_uart_device(var, config)
    enable_rx_pin = await cg.gpio_pin_expression(config[CONF_ENABLE_RX_PIN])
    cg.add(var.set_enable_rx_pin(enable_rx_pin))
