import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, DEVICE_CLASS_DISTANCE

random_uart_sensor_ns = cg.esphome_ns.namespace('random_uart_sensor')
RandomSensor = random_uart_sensor_ns.class_('RandomSensor', cg.PollingComponent)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        RandomSensor,
        unit_of_measurement="in",
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_DISTANCE,
    )
    .extend({
        cv.GenerateID(): cv.declare_id(RandomSensor),
    })
    .extend(cv.polling_component_schema('60s'))
)
def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
    