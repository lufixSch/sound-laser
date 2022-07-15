from gpiozero import Servo
from sound_laser.hal import HAL


class ServoHAL(HAL):
    """Hardware interface to control a servo

    Attributes:
        pin: number of the GPIO pin used to control the servo
    """

    def __init__(self, pin: int, inverted: bool):
        """Initialize servo

        Args:
            pin(int): Pin to which the signal wire of the servo is connected (12, 13, 18, 19 for hardware PWM)
            inverted (bool): defines if the rotation of the servo should be inverted
        """

        self.pin = pin
        self.inverted = -1 if inverted else 1

        self.pwm = Servo(pin, initial_value=0, min_pulse_width=0.615 /
                         1000, max_pulse_width=2.495 / 1000)

    def set_position(self, pos: int):
        """Set the position of the servo

        Args:
            pos: Servoposition in degree between -90 and 90
        """
        self.pwm.value = self.inverted * pos / 90

    def close(self):
        """
            Release servo
        """
        self.pwm.value = None
